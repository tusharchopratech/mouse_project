#ifndef MyAlgo_V2_HPP
#define MyAlgo_V2_HPP

#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <numeric>

#include "..\edata\Global.cpp"
#include "..\filter\FilterTools.cpp"
#include "..\edata\json\json.hpp"
using Json = nlohmann::json;
using namespace std;
// using namespace dlib;

class MyAlgo
{
private:
    FilterTools filterTools;

    std::vector<std::vector<double>> threeSamplesRealTime;
    std::vector<double> prevSampleRealTime, prevPrevSampleRealTime;

    std::vector<double> thresholdValues;
    std::vector<double> backupThresholdValues;

    std::vector<double> thresholdValuesLeftClick, thresholdValuesRightClick;
    std::vector<double> backupThresholdValuesLeftClick, backupThresholdValuesRightClick;

    std::vector<std::vector<double>> d_emg, d_tkeo, d_p3_tkeo, d_f_tkeo, d_f_p3_tkeo, d_training_data;
    std::vector<std::vector<int>> d_clicks;

    string participantName;
    int trialNumber, numberOfChannelesUsedForTraining;

    int clickType = 1;                        // only two values: 1 is for left and 2 is for right
    std::vector<int> channelIDRight{3, 3, 3}; // feature sequence: tko, p3tko, stko
    std::vector<int> channelIDLeft{1, 1, 4};

    // Testing on the training data
    double refractoryTime = 0.1;
    int numV = 1;

public:
    MyAlgo()
    {
    }

    Json getAlgoResults(string pName, int noCh, int trialNo, int cType);

    void readData();
    void processData();

    std::vector<std::vector<double>> tkoSpatial(std::vector<std::vector<double>> signal, int p);
    std::vector<std::vector<double>> tkoTime(std::vector<std::vector<double>> signal, int p);
    double getTkeoValue(double v1, double v2, double v3);

    Json startAnalysing();

    std::vector<int> labelClickType(std::vector<std::vector<int>> clicks, int t1, int t2);
    std::vector<double> fnTrain(std::vector<std::vector<std::vector<double>>> featData, std::vector<std::vector<int>> channelID, std::vector<int> clickAssemble, int clickType);
    std::vector<double> fnEvaluate(std::vector<std::vector<std::vector<double>>> featData, std::vector<std::vector<int>> channelID, std::vector<double> thresholdValues, std::vector<int> clickAssemble, int clickType, int sampRate, double refractoryTime, int numV);

    std::vector<double> fnTrainBothClicks(std::vector<std::vector<std::vector<double>>> featData, std::vector<int> clickAssemble, std::vector<int> channelId, int clickType);
    std::vector<double> fnEvaluateBothClicks(std::vector<std::vector<std::vector<double>>> featData, std::vector<int> channelID, std::vector<double> thresholdValues, std::vector<int> clickAssemble, int clickType, int sampRate, double refractoryTime, int numV);
    string fnRealTimeBoth(std::vector<std::vector<double>> rawdata3Samples, int vots);

    bool getIfThresholdCalculated();
    void setThresholdValues(double thresholdPercentageLeft, double thresholdPercentageRight);
    bool detectAndFireImpulseClicks(std::vector<std::vector<double>> raw_data_10_samples);
    bool fnRealTime(std::vector<std::vector<double>> rawdata, std::vector<int> channel, std::vector<double> thresholdValues, int vots);
};

#endif // !MyAlgo_HPP
