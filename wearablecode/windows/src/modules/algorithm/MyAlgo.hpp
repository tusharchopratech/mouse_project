#ifndef MyAlgo_HPP
#define MyAlgo_HPP

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

    int trainingWindowStartPointForNoise = (int)(GB_TRAINING_WINDOW_INTERVAL_STARTING * GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD);
    int trainingWindowEndPointForNoise = (int)(GB_TRAINING_WINDOW_INTERVAL_ENDING * GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD);
    int trainingWindowStartPointForFeatureConstruction = (int)(GB_CLICK_DETECTION_INTERVAL_STARTING * GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD);
    int totalNumberOfTrainingDataSamples;

    int bestAlgoModeLC, bestAlgoSignFlagLC;
    int bestAlgoModeRC, bestAlgoSignFlagRC;

    std::vector<std::vector<double>> threeSamplesRealTime;
    std::vector<double> prevSampleRealTime, prevPrevSampleRealTime;

    // Reading Data From file
    std::vector<double> trainingDataChannel1, trainingDataChannel2, trainingDataChannel3, trainingDataChannel4;
    std::vector<int> trainingDataLeftClick, trainingDataRightClick, trainingDataThumbClick;

    // Trying different signal types
    std::vector<double> ch1_raw, ch1_tkeo, ch1_p3_tkeo, ch1_f_tkeo, ch1_p3_f_tkeo;
    std::vector<double> ch2_raw, ch2_tkeo, ch2_p3_tkeo, ch2_f_tkeo, ch2_p3_f_tkeo;
    std::vector<double> ch3_raw, ch3_tkeo, ch3_p3_tkeo, ch3_f_tkeo, ch3_p3_f_tkeo;
    std::vector<double> ch4_raw, ch4_tkeo, ch4_p3_tkeo, ch4_f_tkeo, ch4_p3_f_tkeo;
    std::vector<int> l_c, r_c, t_c;

    // Calculating global noise
    double globalChannelNoise[4] = {5.0, 5.0, 5.0, 5.0};

    // Calculating Mean and Covariance
    std::vector<std::vector<double>> covMatrixRightClick;
    std::vector<std::vector<double>> covMatrixLeftClick;
    std::vector<std::vector<double>> covMatrixThumbClick;
    std::vector<double> meanLeftClick;
    std::vector<double> meanRightClick;
    std::vector<double> meanThumbClick;

    string participantName;
    int trialNumber, numberOfChannelesUsedForTraining;

public:
    MyAlgo()
    {
    }

    void readData();
    void processData();
    double getTkeoValue(double v1, double v2, double v3);

    void computeGlobalNoice(int algoMode, int signFlag);
    void getEachChannelMaxValueForClickType(std::vector<int> clickArray, int algoMode, int signFlag, double (&eachChannelMaxSample)[4]);
    double minOfThree(double x, double y, double z);

    void computeFeatures(int algoMode, int signFlag);
    void getFeaturesForClickType(std::vector<int> clickArray, int algoMode, int signFlag, std::vector<std::vector<double>> &featureVector);

    double getDistance(std::vector<double> sample, std::vector<double> mean, std::vector<std::vector<double>> cov);
    string predictCLickTypeFromOneSample(std::vector<double> sample);
    string predictCLickTypeFromThreeSamples(std::vector<std::vector<double>> threeSamples, bool fireClicks);

    string predictAndWriteAlgoSpecificResults(int algoMode, int signFlag, string filePath);
    string predictAndWriteResults();
    int getClickLead(int loc, std::vector<int> clickArray);
    std::vector<int> MyAlgo::getActualClickIndices(std::vector<int> clickData);

    string getAlgoResults(string pName, int noCh, int trialNo);

    void fireImpulseClicks(std::vector<double> ch1, std::vector<double> ch2, std::vector<double> ch3, std::vector<double> ch4);
};

#endif // !MyAlgo_HPP
