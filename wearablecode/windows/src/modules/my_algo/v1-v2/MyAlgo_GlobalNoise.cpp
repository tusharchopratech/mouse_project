#ifndef MyAlgo_GlobalNoise_CPP
#define MyAlgo_GlobalNoise_CPP
#include "MyAlgo.hpp"

void MyAlgo::computeGlobalNoice(std::vector<std::vector<double>> signal)
{
    int trainingWindowStartPointForNoise = (int)(GB_TRAINING_WINDOW_INTERVAL_STARTING * GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD);
    int trainingWindowEndPointForNoise = (int)(GB_TRAINING_WINDOW_INTERVAL_ENDING * GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD);

    double leftClickEachChannelMaxValue[] = {-5.0, -5.0, -5.0, -5.0};
    double rightClickEachChannelMaxValue[] = {-5.0, -5.0, -5.0, -5.0};
    double thumbClickEachChannelMaxValue[] = {-5.0, -5.0, -5.0, -5.0};

    bool readNoiseWindow = true;

    //Looping through Each Click
    for (int c = 0; c < d_clicks.at(0).size(); c++)
    {
        readNoiseWindow = true;
        //Looping through Each Sample
        for (int i = 0; i < d_clicks.size(); i++)
        {
            if (readNoiseWindow)
            {
                if (d_clicks.at(i).at(c) == 1)
                {
                    // cout<<i<<" - "<<d_clicks.at(i).at(0)<<" "<<d_clicks.at(i).at(1)<<" "<<d_clicks.at(i).at(2)<<endl;
                    readNoiseWindow = false;
                    // std::vector<std::vector<double>> window;
                    if (i - trainingWindowStartPointForNoise > 0)
                    {
                        std::vector<double> ch1_values_noise_window, ch2_values_noise_window, ch3_values_noise_window, ch4_values_noise_window;

                        for (int j = i - trainingWindowStartPointForNoise; j < i - trainingWindowEndPointForNoise; j++)
                        {
                            ch1_values_noise_window.push_back(abs(d_tkeo.at(j).at(0)));
                            ch2_values_noise_window.push_back(abs(d_tkeo.at(j).at(1)));
                            ch3_values_noise_window.push_back(abs(d_tkeo.at(j).at(2)));
                            ch4_values_noise_window.push_back(abs(d_tkeo.at(j).at(3)));

                            if (c == 0)
                            {
                                if (abs(signal.at(j).at(0)) > leftClickEachChannelMaxValue[0])
                                {
                                    leftClickEachChannelMaxValue[0] = abs(signal.at(j).at(0));
                                }
                                if (abs(signal.at(j).at(1)) > leftClickEachChannelMaxValue[1])
                                {
                                    leftClickEachChannelMaxValue[1] = abs(signal.at(j).at(1));
                                }
                                if (abs(signal.at(j).at(2)) > leftClickEachChannelMaxValue[2])
                                {
                                    leftClickEachChannelMaxValue[2] = abs(signal.at(j).at(2));
                                }
                                if (abs(signal.at(j).at(3)) > leftClickEachChannelMaxValue[3])
                                {
                                    leftClickEachChannelMaxValue[3] = abs(signal.at(j).at(3));
                                }
                            }
                            else if (c == 1)
                            {
                                if (abs(signal.at(j).at(0)) > rightClickEachChannelMaxValue[0])
                                {
                                    rightClickEachChannelMaxValue[0] = abs(signal.at(j).at(0));
                                }
                                if (abs(signal.at(j).at(1)) > rightClickEachChannelMaxValue[1])
                                {
                                    rightClickEachChannelMaxValue[1] = abs(signal.at(j).at(1));
                                }
                                if (abs(signal.at(j).at(2)) > rightClickEachChannelMaxValue[2])
                                {
                                    rightClickEachChannelMaxValue[2] = abs(signal.at(j).at(2));
                                }
                                if (abs(signal.at(j).at(3)) > rightClickEachChannelMaxValue[3])
                                {
                                    rightClickEachChannelMaxValue[3] = abs(signal.at(j).at(3));
                                }
                            }
                            else if (c == 2)
                            {
                                if (abs(signal.at(j).at(0)) > thumbClickEachChannelMaxValue[0])
                                {
                                    thumbClickEachChannelMaxValue[0] = abs(signal.at(j).at(0));
                                }
                                if (abs(signal.at(j).at(1)) > thumbClickEachChannelMaxValue[1])
                                {
                                    thumbClickEachChannelMaxValue[1] = abs(signal.at(j).at(1));
                                }
                                if (abs(signal.at(j).at(2)) > thumbClickEachChannelMaxValue[2])
                                {
                                    thumbClickEachChannelMaxValue[2] = abs(signal.at(j).at(2));
                                }
                                if (abs(signal.at(j).at(3)) > thumbClickEachChannelMaxValue[3])
                                {
                                    thumbClickEachChannelMaxValue[3] = abs(signal.at(j).at(3));
                                }
                            }
                        }

                        std::sort(ch1_values_noise_window.begin(), ch1_values_noise_window.end());
                        int index_ch_1 = int(GB_TRAINING_SAMPLE_TAKEN_FROM_CLASSIFICATION * ch1_values_noise_window.size());
                        if (ch1_values_noise_window.size() % 2 == 0)
                        {
                            index_ch_1--;
                        }
                        double v1 = ch1_values_noise_window.at(index_ch_1);

                        std::sort(ch2_values_noise_window.begin(), ch2_values_noise_window.end());
                        int index_ch_2 = int(GB_TRAINING_SAMPLE_TAKEN_FROM_CLASSIFICATION * ch2_values_noise_window.size());
                        if (ch2_values_noise_window.size() % 2 == 0)
                        {
                            index_ch_2--;
                        }
                        double v2 = ch2_values_noise_window.at(index_ch_2);

                        std::sort(ch3_values_noise_window.begin(), ch3_values_noise_window.end());
                        int index_ch_3 = int(GB_TRAINING_SAMPLE_TAKEN_FROM_CLASSIFICATION * ch3_values_noise_window.size());
                        if (ch3_values_noise_window.size() % 2 == 0)
                        {
                            index_ch_3--;
                        }
                        double v3 = ch3_values_noise_window.at(index_ch_3);

                        std::sort(ch4_values_noise_window.begin(), ch4_values_noise_window.end());
                        int index_ch_4 = int(GB_TRAINING_SAMPLE_TAKEN_FROM_CLASSIFICATION * ch4_values_noise_window.size());
                        if (ch4_values_noise_window.size() % 2 == 0)
                        {
                            index_ch_4--;
                        }
                        double v4 = ch4_values_noise_window.at(index_ch_4);

                        std::vector<double> tmp;
                        tmp.push_back(v1);
                        tmp.push_back(v2);
                        tmp.push_back(v3);
                        tmp.push_back(v4);
                        tmp.push_back(0);
                        d_training_data.push_back(tmp);
                        tmp.clear();
                    }
                }
            }
            else if (readNoiseWindow == false && d_clicks.at(i).at(c) == 0)
            {
                readNoiseWindow = true;
            }
        }
    }

    for (int i = 0; i < 4; i++)
    {
        globalChannelNoise[i] = gb_minOfThree(leftClickEachChannelMaxValue[i], rightClickEachChannelMaxValue[i], thumbClickEachChannelMaxValue[i]);
    }
}


#endif