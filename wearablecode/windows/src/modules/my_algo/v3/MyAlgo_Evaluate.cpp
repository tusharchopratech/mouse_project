#ifndef MyAlgo_Evaluate_HPP
#define MyAlgo_Evaluate_HPP

#include "MyAlgo.hpp"

// performance evaluation
std::vector<double> MyAlgo::fnEvaluate(std::vector<std::vector<std::vector<double>>> featData, std::vector<std::vector<int>> channelID, std::vector<double> thresholdValues, std::vector<int> clickAssemble, int clickType, int sampRate, double refractoryTime, int numV)
{
    int numFeat = featData.size(); // # of features
    std::vector<int> votCount;
    int numSample = 0; // # of samples
    for (int i = 0; i < numFeat; i++)
    {
        if (numSample < featData.at(i).size())
            numSample = featData.at(i).size();

        votCount.push_back(0);
    }

    double numTP = 0;
    double numFP = 0;
    std::vector<double> timeLead;

    int i = 0;
    while (i < numSample)
    {

        if (clickAssemble.at(i) == 4)
        {
            i = i + 1;
            continue;
        }

        for (int j = 0; j < numFeat; j++)
        {
            int tempChannel = channelID.at(clickType - 1).at(j) - 1;
            if (featData.at(j).at(i).at(tempChannel) > thresholdValues.at(j))
                votCount.at(j) = 1;
            else
            {
                votCount.at(j) = 0;
            }
        }
        cout << "4.1" << endl;
        int count = 0;
        for (int j = 0; j < numFeat; j++)
            count = count + votCount.at(j);

        if (count < numV)
            i = i + 1;
        else
        {

            if (clickAssemble.at(i) == clickType) // detect is true
            {
                numTP++;

                int iTemp = i + 1;
                while (clickAssemble.at(iTemp) == clickAssemble.at(i))
                    iTemp++;

                timeLead.push_back(double(iTemp - i) / sampRate);
            }
            else
            {
                numFP++;
            }

            i = i + round(sampRate * refractoryTime);
        }
    }
    cout << "4.2" << endl;
    double aveTimeLead = 0;
    for (int i = 0; i < timeLead.size(); i++)
    {
        aveTimeLead = aveTimeLead + timeLead.at(i);
    }
    aveTimeLead = aveTimeLead / timeLead.size();

    double clickTimes = 0;
    i = 0;
    while (i < numSample)
    {
        if (clickAssemble.at(i) == clickType)
        {
            clickTimes++;
            while (i < numSample && clickAssemble.at(i) == clickType)
                i++;
        }
        else
        {
            i++;
        }
    }

    std::vector<double> varReturn;
    varReturn.push_back(numTP / clickTimes);
    varReturn.push_back(numFP / clickTimes);
    varReturn.push_back(aveTimeLead);
    return varReturn;
}

std::vector<double> MyAlgo::fnEvaluateBothClicks(std::vector<std::vector<std::vector<double>>> featData, std::vector<int> channelID, std::vector<double> thresholdValues, std::vector<int> clickAssemble, int clickType, int sampRate, double refractoryTime, int numV)
{
    std::vector<double> varReturn;
    int i = 0;
    try
    {

        cout << "E1" << endl;
        int numFeat = featData.size(); // # of features
        std::vector<int> votCount;
        int numSample = 0; // # of samples
        for (int ii = 0; ii < numFeat; ii++)
        {
            if (numSample < featData.at(ii).size())
                numSample = featData.at(ii).size();

            votCount.push_back(0);
        }

        double numTP = 0;
        double numFP = 0;
        std::vector<double> timeLead;

        cout << "E2" << endl;
        while (i < numSample)
        {
            if (clickAssemble.at(i) == 4)
            {
                i = i + 1;
                continue;
            }

            for (int j = 0; j < numFeat; j++)
            {
                int tempChannel = channelID.at(j) - 1;
                if (featData.at(j).at(i).at(tempChannel) > thresholdValues.at(j))
                    votCount.at(j) = 1;
                else
                {
                    votCount.at(j) = 0;
                }
            }
            int count = 0;
            for (int j = 0; j < numFeat; j++)
                count = count + votCount.at(j);

            if (count < numV)
                i = i + 1;
            else
            {

                if (clickAssemble.at(i) == clickType) // detect is true
                {
                    numTP++;

                    int iTemp = i + 1;
                    while (clickAssemble.at(iTemp) == clickAssemble.at(i))
                        iTemp++;

                    timeLead.push_back(double(iTemp - i) / sampRate);
                }
                else
                {
                    numFP++;
                }

                i = i + round(sampRate * refractoryTime);
            }
        }
        cout << "E3" << endl;
        double aveTimeLead = 0;
        for (int i = 0; i < timeLead.size(); i++)
        {
            aveTimeLead = aveTimeLead + timeLead.at(i);
        }
        aveTimeLead = aveTimeLead / timeLead.size();

        double clickTimes = 0;
        i = 0;
        while (i < numSample)
        {
            if (clickAssemble.at(i) == clickType)
            {
                clickTimes++;
                while (i < numSample && clickAssemble.at(i) == clickType)
                    i++;
            }
            else
            {
                i++;
            }
        }
        cout << "E4" << endl;
        varReturn.push_back(numTP / clickTimes);
        varReturn.push_back(numFP / clickTimes);
        varReturn.push_back(aveTimeLead);
    }
    catch (exception &e)
    {
        cout << e.what() << "   **Info**   File : " << __FILE__ << " Function : " << __func__ << " at Line : " << __LINE__ << '\n';
        cout << i << endl;
    }
    return varReturn;
}

#endif