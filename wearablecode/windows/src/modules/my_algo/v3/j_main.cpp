#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

void readData(string file); // import data

std::vector<int> lableClickType(std::vector<std::vector<int>> clicks, int t1, int t2); // relabel the click sequence

double getTkeoValue(double v1, double v2, double v3); // return TKO for [v1 v2 v3]
std::vector<std::vector<double>> tkoTime(int p);      // return TKO Time Feature
std::vector<std::vector<double>> tkoSpatial(int p);   // return TKO Spatial Feature

std::vector<double> fnTrain(std::vector<std::vector<std::vector<double>>> featData, std::vector<std::vector<int>> channelID, std::vector<int> clicks, int clickType);

std::vector<double> fnEvaluate(std::vector<std::vector<std::vector<double>>> featData, std::vector<std::vector<int>> channelID, std::vector<double> thresholdValues, std::vector<int> clickAssemble, int clickType, int sampRate, double refractoryTime, int N);

int fnRealTime(std::vector<double> sample);

std::vector<std::vector<double>> d_emg; // raw data
std::vector<std::vector<int>> d_clicks; // click timing

int main()
{
    // set parameters
    int clickType = 1;                        // only two values: 1 is for left and 2 is for right
    std::vector<int> channelIDRight{3, 3, 3}; // feature sequence: tko, p3tko, stko
    std::vector<int> channelIDLeft{1, 1, 4};
    std::vector<vector<int>> channelID;
    channelID.push_back(channelIDLeft);
    channelID.push_back(channelIDRight);

    std::vector<double> thresholdValue;
    std::vector<std::vector<double>> d_feat;
    std::vector<std::vector<std::vector<double>>> featData;

    // import data
    readData("data_Erik14_C4.txt");

    // Get Feature
    d_feat.clear();
    d_feat = tkoTime(1); // TKO feature extraction
    featData.push_back(d_feat);

    d_feat.clear();
    d_feat = tkoTime(3);
    featData.push_back(d_feat);

    d_feat.clear();
    d_feat = tkoSpatial(1);
    featData.push_back(d_feat);

    // Label the click of the timing
    int sampRate = 2048;
    //  int rangeBeforeClick = -0.1;
    int captureRangeBefore = round(0.1 * sampRate);
    int captureRangeAfter = round(0.05 * sampRate);
    vector<int> clickLabel;
    clickLabel = lableClickType(d_clicks, captureRangeBefore, captureRangeAfter); // 0: rest, 1,2,3 before right, left and thumb click, 4 within click

    // Training
    vector<double> thresholdValues;
    thresholdValues = fnTrain(featData, channelID, clickLabel, clickType);

    // Testing on the training data
    double refractoryTime = 0.1;
    int numV = 1;
    vector<double> results = fnEvaluate(featData, channelID, thresholdValues, clickLabel, clickType, sampRate, refractoryTime, numV);

    // **************RealTime Test************************
    // if it is not within click and not in the refractory time (refractoryTime after the last detected click), start detection
    // input is the rawdata with only three samples
    // bool clickDetected = fnRealTime(d_rawdata, channelID.at(clickType-1), thresholdValues, numV);
    // return if the click is deteced or not
    //**********************

    std::cout << "\n Results" << endl;
    for (int i = 0; i < results.size(); i++)
    {
        std::cout << results.at(i) << endl;
    }

    return 0;
}

// performance evaluation
vector<double> fnEvaluate(vector<vector<vector<double>>> featData, vector<vector<int>> channelID, vector<double> thresholdValues, vector<int> clickAssemble, int clickType, int sampRate, double refractoryTime, int numV)
{
    int numFeat = featData.size(); // # of features
    vector<int> votCount;
    int numSample = 0; // # of samples
    for (int i = 0; i < numFeat; i++)
    {
        if (numSample < featData.at(i).size())
            numSample = featData.at(i).size();

        votCount.push_back(0);
    }

    double numTP = 0;
    double numFP = 0;
    vector<double> timeLead;

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

    vector<double> varReturn;
    varReturn.push_back(numTP / clickTimes);
    varReturn.push_back(numFP / clickTimes);
    varReturn.push_back(aveTimeLead);

    return varReturn;
}

vector<double> fnTrain(vector<vector<vector<double>>> featData, vector<vector<int>> channelID, vector<int> clickAssemble, int clickType)
{
    vector<double> thresholdAssemble;
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

bool fnRealTime(vector<double> rawdata, vector<int> channel, vector<double> thresholdValues, int vots)
{
    // feature extraction
    vector<vector<double>> d_feat;
    d_feat.clear();
    d_feat = tkoTime(1); // TKO feature extraction
    int f1 = 0;
    if (d_feat.at(0).at(channel.at(0)) > thresholdValues.at(0))
        f1 = 1;

    d_feat.clear();
    d_feat = tkoTime(3);
    int f2 = 0;
    if (d_feat.at(0).at(channel.at(1)) > thresholdValues.at(1))
        f2 = 1;

    d_feat.clear();
    d_feat = tkoSpatial(1);
    int f3 = 0;
    if (d_feat.at(0).at(channel.at(2)) > thresholdValues.at(2))
        f3 = 1;

    // majority vote
    if (f1 + f2 + f3 > vots)
        return true;
    else
    {
        return false;
    }
}

vector<int> lableClickType(vector<vector<int>> clicks, int t1, int t2)
{
    vector<int> clickAssemble;
    int n = clicks.at(0).size(); // # of click types

    // initialization
    for (int i = 0; i < clicks.size(); i++)
    {
        clickAssemble.push_back(0);
    }

    int i = 0;
    while (i < clicks.size())
    {
        int temp = 0;
        int j = 0;

        for (; j < n; j++)
        {
            temp = clicks.at(i).at(j);
            if (temp > 0)
                break;
        }
        if (temp > 0)
        {
            // change the previous to the click type id
            for (int k = 1; k <= t1 && i - k >= 0 && clickAssemble.at(i - k) == 0; k++)
            {
                clickAssemble.at(i - k) = j + 1;
            }
            // change the following to 4
            do
            {

                clickAssemble.at(i) = 4;
                i++;
            } while (i < clicks.size() && clicks.at(i).at(j) == temp);
            // change the after to 4

            for (int k = 0; k <= t2; k++)
            {
                if (i + k < clickAssemble.size())
                {
                    clickAssemble.at(i + k) = 4;
                }
            }
            i = i + t2;
        }
        else
        {
            i++;
        }
    }

    return clickAssemble;
}

void readData(string file)
{
    std::string line;
    std::ifstream infile(file);
    if (infile.fail())
    {
        std::cout << "Unable to open file : " << file << endl;
    }
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        std::string s = line;
        std::string delimiter = " ";
        size_t pos = 0;
        std::string token;
        int i = 0;

        std::vector<double> tmp;
        std::vector<int> tmp2;

        while ((pos = s.find(delimiter)) != std::string::npos)
        {
            token = s.substr(0, pos);
            // std::cout << token << std::endl;
            s.erase(0, pos + delimiter.length());
            if (i == 0)
            {
                tmp.push_back(std::stod(token));
            }
            else if (i == 1)
            {
                tmp.push_back(std::stod(token));
            }
            else if (i == 2)
            {
                tmp.push_back(std::stod(token));
            }
            else if (i == 3)
            {
                tmp.push_back(std::stod(token));
                d_emg.push_back(tmp);
                tmp.clear();
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

vector<vector<double>> tkoSpatial(int p)
{
    std::vector<std::vector<double>> datafeat;
    std::vector<double> tmp;
    for (int i = 0; i < d_emg.size(); i++)
    {
        //For Channel 1, then 2, then 3 then 4
        tmp.push_back(getTkeoValue(pow(d_emg.at(i).at(0), p), pow(d_emg.at(i).at(1), p), pow(d_emg.at(i).at(2), p)));
        tmp.push_back(getTkeoValue(pow(d_emg.at(i).at(1), p), pow(d_emg.at(i).at(2), p), pow(d_emg.at(i).at(3), p)));
        tmp.push_back(getTkeoValue(pow(d_emg.at(i).at(2), p), pow(d_emg.at(i).at(3), p), pow(d_emg.at(i).at(0), p)));
        tmp.push_back(getTkeoValue(pow(d_emg.at(i).at(3), p), pow(d_emg.at(i).at(0), p), pow(d_emg.at(i).at(1), p)));

        datafeat.push_back(tmp);
        tmp.clear();
    }

    return datafeat;
}

vector<vector<double>> tkoTime(int p)
{
    std::vector<std::vector<double>> datafeat;
    std::vector<double> tmp;
    for (int i = 0; i < d_emg.size() - 2; i++)
    {
        //For Channel 1, then 2, then 3 then 4
        tmp.push_back(getTkeoValue(pow(d_emg.at(i).at(0), p), pow(d_emg.at(i + 1).at(0), p), pow(d_emg.at(i + 2).at(0), p)));
        tmp.push_back(getTkeoValue(pow(d_emg.at(i).at(1), p), pow(d_emg.at(i + 1).at(1), p), pow(d_emg.at(i + 2).at(1), p)));
        tmp.push_back(getTkeoValue(pow(d_emg.at(i).at(2), p), pow(d_emg.at(i + 1).at(2), p), pow(d_emg.at(i + 2).at(2), p)));
        tmp.push_back(getTkeoValue(pow(d_emg.at(i).at(3), p), pow(d_emg.at(i + 1).at(3), p), pow(d_emg.at(i + 2).at(3), p)));

        datafeat.push_back(tmp);
        tmp.clear();
    }

    return datafeat;
}

double getTkeoValue(double v1, double v2, double v3)
{
    return v2 * v2 - v1 * v3;
}
