#ifndef MyAlgo_ReadNProcessData_CPP
#define MyAlgo_ReadNProcessData_CPP
#include "MyAlgo.hpp"

void MyAlgo::readData()
{
    trainingDataChannel1.clear();
    trainingDataChannel2.clear();
    trainingDataChannel3.clear();
    trainingDataChannel4.clear();
    trainingDataLeftClick.clear();
    trainingDataRightClick.clear();
    trainingDataThumbClick.clear();

    string file = GB_IMPULSE_DIRECTORY + "/data_" + participantName + std::to_string(trialNumber) + "_C" + std::to_string(numberOfChannelesUsedForTraining) + ".txt";

    std::string line;
    std::ifstream infile(file);
    if (infile.fail())
    {
        cout << "Unable to open file : " << file << endl;
    }
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        std::string s = line;
        std::string delimiter = " ";
        size_t pos = 0;
        std::string token;
        int i = 0;

        std::vector<double> tmp1;
        std::vector<int> tmp2;

        while ((pos = s.find(delimiter)) != std::string::npos)
        {
            token = s.substr(0, pos);
            // std::cout << token << std::endl;
            s.erase(0, pos + delimiter.length());
            if (i == 0)
            {
                trainingDataChannel1.push_back(std::stod(token));
                tmp1.push_back(std::stod(token));
            }
            else if (i == 1)
            {
                trainingDataChannel2.push_back(std::stod(token));
                tmp1.push_back(std::stod(token));
            }
            else if (i == 2)
            {
                trainingDataChannel3.push_back(std::stod(token));
                tmp1.push_back(std::stod(token));
            }
            else if (i == 3)
            {
                trainingDataChannel4.push_back(std::stod(token));
                tmp1.push_back(std::stod(token));
                // tmp1.push_back(tmp1.at(0));
                d_emg.push_back(tmp1);
                tmp1.clear();
            }
            else if (i == 4)
            {
                trainingDataLeftClick.push_back(std::stoi(token));
                tmp2.push_back(std::stoi(token));
            }
            else if (i == 5)
            {
                trainingDataRightClick.push_back(std::stoi(token));
                tmp2.push_back(std::stoi(token));
            }
            i++;
        }

        trainingDataThumbClick.push_back(std::stoi(s));
        tmp2.push_back(std::stoi(s));
        d_clicks.push_back(tmp2);
        tmp2.clear();
    }

    // std::vector<double> tmp;
    // tmp = trainingDataChannel3;
    // trainingDataChannel3 = trainingDataChannel4;
    // trainingDataChannel4 = tmp;
}

void MyAlgo::processData()
{
    std::vector<double> tmp1, tmp2, tmp3, tmp4;
    ch1_raw.clear();
    ch2_raw.clear();
    ch3_raw.clear();
    ch4_raw.clear();

    ch1_tkeo.clear();
    ch2_tkeo.clear();
    ch3_tkeo.clear();
    ch4_tkeo.clear();

    ch1_p3_tkeo.clear();
    ch2_p3_tkeo.clear();
    ch3_p3_tkeo.clear();
    ch4_p3_tkeo.clear();

    ch1_p3_f_tkeo.clear();
    ch2_p3_f_tkeo.clear();
    ch3_p3_f_tkeo.clear();
    ch4_p3_f_tkeo.clear();

    ch1_f_tkeo.clear();
    ch2_f_tkeo.clear();
    ch3_f_tkeo.clear();
    ch4_f_tkeo.clear();

    filterTools.resetFilters();
    for (int i = 2; i < trainingDataChannel1.size(); i++)
    {
        ch1_raw.push_back(trainingDataChannel1.at(i));
        ch2_raw.push_back(trainingDataChannel2.at(i));
        ch3_raw.push_back(trainingDataChannel3.at(i));
        ch4_raw.push_back(trainingDataChannel4.at(i));
        l_c.push_back(trainingDataLeftClick.at(i));
        r_c.push_back(trainingDataRightClick.at(i));
        t_c.push_back(trainingDataThumbClick.at(i));
    }

    filterTools.resetFilters();
    for (int i = 2; i < trainingDataChannel1.size(); i++)
    {
        ch1_tkeo.push_back(getTkeoValue(trainingDataChannel1.at(i - 2), trainingDataChannel1.at(i - 1), trainingDataChannel1.at(i)));
        ch2_tkeo.push_back(getTkeoValue(trainingDataChannel2.at(i - 2), trainingDataChannel2.at(i - 1), trainingDataChannel2.at(i)));
        ch3_tkeo.push_back(getTkeoValue(trainingDataChannel3.at(i - 2), trainingDataChannel3.at(i - 1), trainingDataChannel3.at(i)));
        ch4_tkeo.push_back(getTkeoValue(trainingDataChannel4.at(i - 2), trainingDataChannel4.at(i - 1), trainingDataChannel4.at(i)));
    }

    filterTools.resetFilters();
    for (int i = 2; i < trainingDataChannel1.size(); i++)
    {
        ch1_p3_tkeo.push_back(getTkeoValue(pow(trainingDataChannel1.at(i - 2), 3), pow(trainingDataChannel1.at(i - 1), 3), pow(trainingDataChannel1.at(i), 3)));
        ch2_p3_tkeo.push_back(getTkeoValue(pow(trainingDataChannel2.at(i - 2), 3), pow(trainingDataChannel2.at(i - 1), 3), pow(trainingDataChannel2.at(i), 3)));
        ch3_p3_tkeo.push_back(getTkeoValue(pow(trainingDataChannel3.at(i - 2), 3), pow(trainingDataChannel3.at(i - 1), 3), pow(trainingDataChannel3.at(i), 3)));
        ch4_p3_tkeo.push_back(getTkeoValue(pow(trainingDataChannel4.at(i - 2), 3), pow(trainingDataChannel4.at(i - 1), 3), pow(trainingDataChannel4.at(i), 3)));
    }

    filterTools.resetFilters();
    tmp1.clear();
    tmp2.clear();
    tmp3.clear();
    tmp4.clear();
    for (int i = 0; i < trainingDataChannel1.size(); i++)
    {
        tmp1.push_back(pow(filterTools.getFilteredValue(1, trainingDataChannel1.at(i)), 3));
        tmp2.push_back(pow(filterTools.getFilteredValue(2, trainingDataChannel2.at(i)), 3));
        tmp3.push_back(pow(filterTools.getFilteredValue(3, trainingDataChannel3.at(i)), 3));
        tmp4.push_back(pow(filterTools.getFilteredValue(4, trainingDataChannel4.at(i)), 3));
    }
    for (int i = 2; i < tmp1.size(); i++)
    {
        ch1_p3_f_tkeo.push_back(getTkeoValue(tmp1.at(i - 2), tmp1.at(i - 1), tmp1.at(i)));
        ch2_p3_f_tkeo.push_back(getTkeoValue(tmp2.at(i - 2), tmp2.at(i - 1), tmp2.at(i)));
        ch3_p3_f_tkeo.push_back(getTkeoValue(tmp3.at(i - 2), tmp3.at(i - 1), tmp3.at(i)));
        ch4_p3_f_tkeo.push_back(getTkeoValue(tmp4.at(i - 2), tmp4.at(i - 1), tmp4.at(i)));
    }

    filterTools.resetFilters();
    tmp1.clear();
    tmp2.clear();
    tmp3.clear();
    tmp4.clear();
    for (int i = 0; i < trainingDataChannel1.size(); i++)
    {
        tmp1.push_back(filterTools.getFilteredValue(1, trainingDataChannel1.at(i)));
        tmp2.push_back(filterTools.getFilteredValue(2, trainingDataChannel2.at(i)));
        tmp3.push_back(filterTools.getFilteredValue(3, trainingDataChannel3.at(i)));
        tmp4.push_back(filterTools.getFilteredValue(4, trainingDataChannel4.at(i)));
    }
    for (int i = 2; i < tmp1.size(); i++)
    {
        ch1_f_tkeo.push_back(getTkeoValue(tmp1.at(i - 2), tmp1.at(i - 1), tmp1.at(i)));
        ch2_f_tkeo.push_back(getTkeoValue(tmp2.at(i - 2), tmp2.at(i - 1), tmp2.at(i)));
        ch3_f_tkeo.push_back(getTkeoValue(tmp3.at(i - 2), tmp3.at(i - 1), tmp3.at(i)));
        ch4_f_tkeo.push_back(getTkeoValue(tmp4.at(i - 2), tmp4.at(i - 1), tmp4.at(i)));
    }

    //New Processing with vectors
    std::vector<double> tmp;
    for (int i = 0; i < d_emg.size(); i++)
    {
        if (i < 2)
        {
            //For Channel 1, then 2, then 3 then 4
            tmp.push_back(getTkeoValue(d_emg.at(i).at(0), d_emg.at(i + 1).at(0), d_emg.at(i + 2).at(0)));
            tmp.push_back(getTkeoValue(d_emg.at(i).at(1), d_emg.at(i + 1).at(1), d_emg.at(i + 2).at(1)));
            tmp.push_back(getTkeoValue(d_emg.at(i).at(2), d_emg.at(i + 1).at(2), d_emg.at(i + 2).at(2)));
            tmp.push_back(getTkeoValue(d_emg.at(i).at(3), d_emg.at(i + 1).at(3), d_emg.at(i + 2).at(3)));
            d_tkeo.push_back(tmp);
            tmp.clear();

            tmp.push_back(getTkeoValue(pow(d_emg.at(i).at(0), 3), pow(d_emg.at(i + 1).at(0), 3), pow(d_emg.at(i + 2).at(0), 3)));
            tmp.push_back(getTkeoValue(pow(d_emg.at(i).at(1), 3), pow(d_emg.at(i + 1).at(1), 3), pow(d_emg.at(i + 2).at(1), 3)));
            tmp.push_back(getTkeoValue(pow(d_emg.at(i).at(2), 3), pow(d_emg.at(i + 1).at(2), 3), pow(d_emg.at(i + 2).at(2), 3)));
            tmp.push_back(getTkeoValue(pow(d_emg.at(i).at(3), 3), pow(d_emg.at(i + 1).at(3), 3), pow(d_emg.at(i + 2).at(3), 3)));
            d_p3_tkeo.push_back(tmp);
            tmp.clear();
        }
        else
        {
            //For Channel 1, then 2, then 3 then 4
            tmp.push_back(getTkeoValue(d_emg.at(i - 2).at(0), d_emg.at(i - 1).at(0), d_emg.at(i).at(0)));
            tmp.push_back(getTkeoValue(d_emg.at(i - 2).at(1), d_emg.at(i - 1).at(1), d_emg.at(i).at(1)));
            tmp.push_back(getTkeoValue(d_emg.at(i - 2).at(2), d_emg.at(i - 1).at(2), d_emg.at(i).at(2)));
            tmp.push_back(getTkeoValue(d_emg.at(i - 2).at(3), d_emg.at(i - 1).at(3), d_emg.at(i).at(3)));
            d_tkeo.push_back(tmp);
            tmp.clear();

            tmp.push_back(getTkeoValue(pow(d_emg.at(i - 2).at(0), 3), pow(d_emg.at(i - 1).at(0), 3), pow(d_emg.at(i).at(0), 3)));
            tmp.push_back(getTkeoValue(pow(d_emg.at(i - 2).at(1), 3), pow(d_emg.at(i - 1).at(1), 3), pow(d_emg.at(i).at(1), 3)));
            tmp.push_back(getTkeoValue(pow(d_emg.at(i - 2).at(2), 3), pow(d_emg.at(i - 1).at(2), 3), pow(d_emg.at(i).at(2), 3)));
            tmp.push_back(getTkeoValue(pow(d_emg.at(i - 2).at(3), 3), pow(d_emg.at(i - 1).at(3), 3), pow(d_emg.at(i).at(3), 3)));
            d_p3_tkeo.push_back(tmp);
            tmp.clear();
        }
    }
}

#endif