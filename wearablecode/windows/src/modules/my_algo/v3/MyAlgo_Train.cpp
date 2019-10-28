#ifndef MyAlgo_Train_HPP
#define MyAlgo_Train_HPP

#include "MyAlgo.hpp"

std::vector<double> MyAlgo::fnTrain(std::vector<std::vector<std::vector<double>>> featData, std::vector<std::vector<int>> channelID, std::vector<int> clickAssemble, int clickType)
{
    std::vector<double> thresholdAssemble;
    // get the threshold of each feature from the designated channel
    for (int i = 0; i < featData.size(); i++) // feature type
    {
        int channelTemp = channelID.at(clickType - 1).at(i) - 1;
        double thresholdTemp = featData.at(i).at(1).at(channelTemp);

        for (int j = 0; j < featData.at(i).size(); j++)
        {
            // Get the maximum except the period 100 ms before the click and within click
            if (clickAssemble.at(j) != 4 && clickAssemble.at(j) != clickType)
            {
                if (thresholdTemp < featData.at(i).at(j).at(channelTemp))
                    thresholdTemp = featData.at(i).at(j).at(channelTemp);
            }
        }
        thresholdAssemble.push_back(thresholdTemp);
        // how about if the threshold is bigger than that of 0-100 ms?
    }

    return thresholdAssemble;
}

std::vector<double> MyAlgo::fnTrainBothClicks(std::vector<std::vector<std::vector<double>>> featData, std::vector<int> clickAssemble, std::vector<int> channelId, int clickType)
{
    std::vector<double> thresholdAssemble;
    // get the threshold of each feature from the designated channel
    for (int i = 0; i < featData.size(); i++) // feature type
    {
        int channelTemp = channelId.at(i) - 1;
        double thresholdTemp = featData.at(i).at(1).at(channelTemp);

        for (int j = 0; j < featData.at(i).size(); j++)
        {
            // Get the maximum except the period 100 ms before the left click and within left click
            if (clickAssemble.at(j) != 4 && clickAssemble.at(j) != clickType)
            {
                if (thresholdTemp < featData.at(i).at(j).at(channelTemp))
                    thresholdTemp = featData.at(i).at(j).at(channelTemp);
            }
        }
        thresholdAssemble.push_back(thresholdTemp);
        // how about if the threshold is bigger than that of 0-100 ms?
    }


    return thresholdAssemble;
}

void MyAlgo::setThresholdValues(double thresholdPercentageLeft, double thresholdPercentageRight)
{
    for (int i = 0; i < thresholdValuesLeftClick.size(); i++)
    {
        thresholdValuesLeftClick.at(i) = ((2 * backupThresholdValuesLeftClick.at(i)) * thresholdPercentageLeft) / 100;
    }
    for (int i = 0; i < thresholdValuesRightClick.size(); i++)
    {
        thresholdValuesRightClick.at(i) = ((2 * backupThresholdValuesRightClick.at(i)) * thresholdPercentageRight) / 100;
    }
}

#endif