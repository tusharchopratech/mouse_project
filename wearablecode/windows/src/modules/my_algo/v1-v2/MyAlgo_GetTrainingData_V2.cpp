#ifndef MyAlgo_GetTrainingData_V2_CPP
#define MyAlgo_GetTrainingData_V2_CPP
#include "MyAlgo.hpp"

void MyAlgo::computeFeatures(std::vector<std::vector<double>> signal)
{
    int trainingWindowStartPointForFeatureExtraction = (int)(GB_CLICK_DETECTION_INTERVAL_STARTING * GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD);

    std::vector<double> tmp;

    bool readFeatureExtractionWindow = true;

    //Looping through Each Click
    for (int c = 0; c < d_clicks.at(0).size(); c++)
    {
        readFeatureExtractionWindow = true;
        //Looping through Each Sample
        for (int i = 0; i < d_clicks.size(); i++)
        {
            if (readFeatureExtractionWindow)
            {
                if (d_clicks.at(i).at(c) == 1)
                {
                    readFeatureExtractionWindow = false;

                    if (i - trainingWindowStartPointForFeatureExtraction > 0)
                    {
                        std::vector<double> ch1_values_greater_than_noise, ch2_values_greater_than_noise, ch3_values_greater_than_noise, ch4_values_greater_than_noise;

                        //Feature Extraction Window
                        for (int j = i - trainingWindowStartPointForFeatureExtraction; j < i; j++)
                        {
                            //Selecting values greater than Noise
                            if (abs(signal.at(j).at(0)) > globalChannelNoise[0])
                            {
                                ch1_values_greater_than_noise.push_back(abs(signal.at(j).at(0)));
                            }

                            if (abs(signal.at(j).at(1)) > globalChannelNoise[1])
                            {
                                ch2_values_greater_than_noise.push_back(abs(signal.at(j).at(1)));
                            }

                            if (abs(signal.at(j).at(2)) > globalChannelNoise[2])
                            {
                                ch3_values_greater_than_noise.push_back(abs(signal.at(j).at(2)));
                            }

                            if (abs(signal.at(j).at(3)) > globalChannelNoise[3])
                            {
                                ch4_values_greater_than_noise.push_back(abs(signal.at(j).at(3)));
                            }
                        }

                        std::vector<double> ch1_values_sorted;
                        if (ch1_values_greater_than_noise.size() > 0)
                        {
                            ch1_values_sorted = ch1_values_greater_than_noise;
                        }
                        else
                        {
                            for (int j = i - trainingWindowStartPointForFeatureExtraction; j < i; j++)
                            {
                                ch1_values_sorted.push_back(abs(signal.at(j).at(0)));
                            }
                        }
                        std::sort(ch1_values_sorted.begin(), ch1_values_sorted.end());
                        int index_ch_1 = int(GB_TRAINING_SAMPLE_TAKEN_FROM_CLASSIFICATION * ch1_values_sorted.size());
                        if (ch1_values_sorted.size() % 2 == 0)
                        {
                            index_ch_1--;
                        }
                        double v1 = ch1_values_sorted.at(index_ch_1);

                        std::vector<double> ch2_values_sorted;
                        if (ch2_values_greater_than_noise.size() > 0)
                        {
                            ch2_values_sorted = ch2_values_greater_than_noise;
                        }
                        else
                        {
                            for (int j = i - trainingWindowStartPointForFeatureExtraction; j < i; j++)
                            {
                                ch2_values_sorted.push_back(abs(signal.at(j).at(1)));
                            }
                        }
                        std::sort(ch2_values_sorted.begin(), ch2_values_sorted.end());
                        int index_ch_2 = int(GB_TRAINING_SAMPLE_TAKEN_FROM_CLASSIFICATION * ch2_values_sorted.size());
                        if (ch2_values_sorted.size() % 2 == 0)
                        {
                            index_ch_2--;
                        }
                        double v2 = ch2_values_sorted.at(index_ch_2);

                        std::vector<double> ch3_values_sorted;
                        if (ch3_values_greater_than_noise.size() > 0)
                        {
                            ch3_values_sorted = ch3_values_greater_than_noise;
                        }
                        else
                        {
                            for (int j = i - trainingWindowStartPointForFeatureExtraction; j < i; j++)
                            {
                                ch3_values_sorted.push_back(abs(signal.at(j).at(2)));
                            }
                        }
                        std::sort(ch3_values_sorted.begin(), ch3_values_sorted.end());
                        int index_ch_3 = int(GB_TRAINING_SAMPLE_TAKEN_FROM_CLASSIFICATION * ch3_values_sorted.size());
                        if (ch3_values_sorted.size() % 2 == 0)
                        {
                            index_ch_3--;
                        }
                        double v3 = ch3_values_sorted.at(index_ch_3);

                        std::vector<double> ch4_values_sorted;
                        if (ch4_values_greater_than_noise.size() > 0)
                        {
                            ch4_values_sorted = ch4_values_greater_than_noise;
                        }
                        else
                        {
                            for (int j = i - trainingWindowStartPointForFeatureExtraction; j < i; j++)
                            {
                                ch4_values_sorted.push_back(abs(signal.at(j).at(3)));
                            }
                        }
                        std::sort(ch4_values_sorted.begin(), ch4_values_sorted.end());
                        int index_ch_4 = int(GB_TRAINING_SAMPLE_TAKEN_FROM_CLASSIFICATION * ch4_values_sorted.size());
                        if (ch4_values_sorted.size() % 2 == 0)
                        {
                            index_ch_4--;
                        }
                        double v4 = ch4_values_sorted.at(index_ch_4);

                        tmp.push_back(v1);
                        tmp.push_back(v2);
                        tmp.push_back(v3);
                        tmp.push_back(v4);
                        tmp.push_back(c + 1);
                        d_training_data.push_back(tmp);
                        tmp.clear();
                    }
                }
            }
            else if (readFeatureExtractionWindow == false && d_clicks.at(i).at(c) == 0)
            {
                readFeatureExtractionWindow = true;
            }
        }
    }
}


#endif