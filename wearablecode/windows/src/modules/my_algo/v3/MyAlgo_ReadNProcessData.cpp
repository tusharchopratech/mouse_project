#ifndef MyAlgo_ReadNProcessData_CPP
#define MyAlgo_ReadNProcessData_CPP
#include "MyAlgo.hpp"

void MyAlgo::readData()
{
    d_clicks.clear();
    d_emg.clear();

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
                tmp1.push_back(std::stod(token));
            }
            else if (i == 1)
            {
                tmp1.push_back(std::stod(token));
            }
            else if (i == 2)
            {
                tmp1.push_back(std::stod(token));
            }
            else if (i == 3)
            {
                tmp1.push_back(std::stod(token));
                d_emg.push_back(tmp1);
                tmp1.clear();
            }
            else if (i == 4)
            {
                tmp2.push_back(std::stoi(token));
            }
            else if (i == 5)
            {
                tmp2.push_back(std::stoi(token));
            }
            i++;
        }

        tmp2.push_back(std::stoi(s));
        d_clicks.push_back(tmp2);
        tmp2.clear();
    }
}

void MyAlgo::processData()
{

    std::vector<std::vector<double>> d_emg_filtered;
    std::vector<double> tmp;
    d_tkeo.clear();
    d_p3_tkeo.clear();
    d_f_tkeo.clear();
    d_f_p3_tkeo.clear();
    
    filterTools.resetFilters();
    for (int i = 0; i < d_emg.size(); i++)
    {
        tmp.push_back(filterTools.getFilteredValue(1, d_emg.at(i).at(0)));
        tmp.push_back(filterTools.getFilteredValue(2, d_emg.at(i).at(1)));
        tmp.push_back(filterTools.getFilteredValue(3, d_emg.at(i).at(2)));
        tmp.push_back(filterTools.getFilteredValue(4, d_emg.at(i).at(3)));
        d_emg_filtered.push_back(tmp);
        tmp.clear();
    }
    filterTools.resetFilters();

    //New Processing with vectors
    for (int i = 0; i < d_emg.size(); i++)
    {

        if (i < 2)
        {
            /**
             * TKEO
             * For Channel 1, then 2, then 3 then 4
            */
            tmp.push_back(getTkeoValue(d_emg.at(i).at(0), d_emg.at(i + 1).at(0), d_emg.at(i + 2).at(0)));
            tmp.push_back(getTkeoValue(d_emg.at(i).at(1), d_emg.at(i + 1).at(1), d_emg.at(i + 2).at(1)));
            tmp.push_back(getTkeoValue(d_emg.at(i).at(2), d_emg.at(i + 1).at(2), d_emg.at(i + 2).at(2)));
            tmp.push_back(getTkeoValue(d_emg.at(i).at(3), d_emg.at(i + 1).at(3), d_emg.at(i + 2).at(3)));
            d_tkeo.push_back(tmp);
            tmp.clear();

            /**
             * P3-TKEO
             * For Channel 1, then 2, then 3 then 4
            */
            tmp.push_back(getTkeoValue(pow(d_emg.at(i).at(0), 3), pow(d_emg.at(i + 1).at(0), 3), pow(d_emg.at(i + 2).at(0), 3)));
            tmp.push_back(getTkeoValue(pow(d_emg.at(i).at(1), 3), pow(d_emg.at(i + 1).at(1), 3), pow(d_emg.at(i + 2).at(1), 3)));
            tmp.push_back(getTkeoValue(pow(d_emg.at(i).at(2), 3), pow(d_emg.at(i + 1).at(2), 3), pow(d_emg.at(i + 2).at(2), 3)));
            tmp.push_back(getTkeoValue(pow(d_emg.at(i).at(3), 3), pow(d_emg.at(i + 1).at(3), 3), pow(d_emg.at(i + 2).at(3), 3)));
            d_p3_tkeo.push_back(tmp);
            tmp.clear();

            /**
             * F-TKEO
             * For Channel 1, then 2, then 3 then 4
            */
            tmp.push_back(getTkeoValue(d_emg_filtered.at(i).at(0), d_emg_filtered.at(i + 1).at(0), d_emg_filtered.at(i + 2).at(0)));
            tmp.push_back(getTkeoValue(d_emg_filtered.at(i).at(1), d_emg_filtered.at(i + 1).at(1), d_emg_filtered.at(i + 2).at(1)));
            tmp.push_back(getTkeoValue(d_emg_filtered.at(i).at(2), d_emg_filtered.at(i + 1).at(2), d_emg_filtered.at(i + 2).at(2)));
            tmp.push_back(getTkeoValue(d_emg_filtered.at(i).at(3), d_emg_filtered.at(i + 1).at(3), d_emg_filtered.at(i + 2).at(3)));
            d_f_tkeo.push_back(tmp);
            tmp.clear();

            /**
             * F-P3-TKEO
             * For Channel 1, then 2, then 3 then 4
            */
            tmp.push_back(getTkeoValue(pow(d_emg_filtered.at(i).at(0), 3), pow(d_emg_filtered.at(i + 1).at(0), 3), pow(d_emg_filtered.at(i + 2).at(0), 3)));
            tmp.push_back(getTkeoValue(pow(d_emg_filtered.at(i).at(1), 3), pow(d_emg_filtered.at(i + 1).at(1), 3), pow(d_emg_filtered.at(i + 2).at(1), 3)));
            tmp.push_back(getTkeoValue(pow(d_emg_filtered.at(i).at(2), 3), pow(d_emg_filtered.at(i + 1).at(2), 3), pow(d_emg_filtered.at(i + 2).at(2), 3)));
            tmp.push_back(getTkeoValue(pow(d_emg_filtered.at(i).at(3), 3), pow(d_emg_filtered.at(i + 1).at(3), 3), pow(d_emg_filtered.at(i + 2).at(3), 3)));
            d_f_p3_tkeo.push_back(tmp);
            tmp.clear();
        }
        else
        {
            /**
             * TKEO
             * For Channel 1, then 2, then 3 then 4
            */
            tmp.push_back(getTkeoValue(d_emg.at(i - 2).at(0), d_emg.at(i - 1).at(0), d_emg.at(i).at(0)));
            tmp.push_back(getTkeoValue(d_emg.at(i - 2).at(1), d_emg.at(i - 1).at(1), d_emg.at(i).at(1)));
            tmp.push_back(getTkeoValue(d_emg.at(i - 2).at(2), d_emg.at(i - 1).at(2), d_emg.at(i).at(2)));
            tmp.push_back(getTkeoValue(d_emg.at(i - 2).at(3), d_emg.at(i - 1).at(3), d_emg.at(i).at(3)));
            d_tkeo.push_back(tmp);
            tmp.clear();

            /**
             * P3-TKEO
             * For Channel 1, then 2, then 3 then 4
            */
            tmp.push_back(getTkeoValue(pow(d_emg.at(i - 2).at(0), 3), pow(d_emg.at(i - 1).at(0), 3), pow(d_emg.at(i).at(0), 3)));
            tmp.push_back(getTkeoValue(pow(d_emg.at(i - 2).at(1), 3), pow(d_emg.at(i - 1).at(1), 3), pow(d_emg.at(i).at(1), 3)));
            tmp.push_back(getTkeoValue(pow(d_emg.at(i - 2).at(2), 3), pow(d_emg.at(i - 1).at(2), 3), pow(d_emg.at(i).at(2), 3)));
            tmp.push_back(getTkeoValue(pow(d_emg.at(i - 2).at(3), 3), pow(d_emg.at(i - 1).at(3), 3), pow(d_emg.at(i).at(3), 3)));
            d_p3_tkeo.push_back(tmp);
            tmp.clear();

            /**
             * F-TKEO
             * For Channel 1, then 2, then 3 then 4
            */
            tmp.push_back(getTkeoValue(d_emg_filtered.at(i - 2).at(0), d_emg_filtered.at(i - 1).at(0), d_emg_filtered.at(i).at(0)));
            tmp.push_back(getTkeoValue(d_emg_filtered.at(i - 2).at(1), d_emg_filtered.at(i - 1).at(1), d_emg_filtered.at(i).at(1)));
            tmp.push_back(getTkeoValue(d_emg_filtered.at(i - 2).at(2), d_emg_filtered.at(i - 1).at(2), d_emg_filtered.at(i).at(2)));
            tmp.push_back(getTkeoValue(d_emg_filtered.at(i - 2).at(3), d_emg_filtered.at(i - 1).at(3), d_emg_filtered.at(i).at(3)));
            d_f_tkeo.push_back(tmp);
            tmp.clear();

            /**
             * F-P3-TKEO
             * For Channel 1, then 2, then 3 then 4
            */
            tmp.push_back(getTkeoValue(pow(d_emg_filtered.at(i - 2).at(0), 3), pow(d_emg_filtered.at(i - 1).at(0), 3), pow(d_emg_filtered.at(i).at(0), 3)));
            tmp.push_back(getTkeoValue(pow(d_emg_filtered.at(i - 2).at(1), 3), pow(d_emg_filtered.at(i - 1).at(1), 3), pow(d_emg_filtered.at(i).at(1), 3)));
            tmp.push_back(getTkeoValue(pow(d_emg_filtered.at(i - 2).at(2), 3), pow(d_emg_filtered.at(i - 1).at(2), 3), pow(d_emg_filtered.at(i).at(2), 3)));
            tmp.push_back(getTkeoValue(pow(d_emg_filtered.at(i - 2).at(3), 3), pow(d_emg_filtered.at(i - 1).at(3), 3), pow(d_emg_filtered.at(i).at(3), 3)));
            d_f_p3_tkeo.push_back(tmp);
            tmp.clear();
        }
    }
}

#endif