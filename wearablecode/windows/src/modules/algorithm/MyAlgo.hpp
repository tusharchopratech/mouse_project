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
using namespace std;
#include <vector>

class MyAlgo
{
private:
    FilterTools filterTools;

    int trainingWindowStartPointForNoise = (int)(2.2 * GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD);
    int trainingWindowEndPointForNoise = (int)(1.8 * GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD);
    int trainingWindowStartPointForFeatureConstruction = (int)(1 * GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD);
    int totalNumberOfTrainingDataSamples;

    // Reading Data From file
    vector<double> trainingDataChannel1, trainingDataChannel2, trainingDataChannel3, trainingDataChannel4;
    vector<int> trainingDataLeftClick, trainingDataRightClick, trainingDataThumbClick;

    // Trying differeny signal types
    vector<double> ch1_raw, ch1_tkeo, ch1_p3_tkeo, ch1_f_tkeo, ch1_p3_f_tkeo;
    vector<double> ch2_raw, ch2_tkeo, ch2_p3_tkeo, ch2_f_tkeo, ch2_p3_f_tkeo;
    vector<double> ch3_raw, ch3_tkeo, ch3_p3_tkeo, ch3_f_tkeo, ch3_p3_f_tkeo;
    vector<double> ch4_raw, ch4_tkeo, ch4_p3_tkeo, ch4_f_tkeo, ch4_p3_f_tkeo;
    vector<int> l_c, r_c, t_c;

    // Calculating global noise
    double globalChannelNoise[4] = {5.0, 5.0, 5.0, 5.0};

    // Calculating Mean and Covariance
    vector<vector<double>> covMatrixRightClick;
    vector<vector<double>> covMatrixLeftClick;
    vector<vector<double>> covMatrixThumbClick;
    vector<double> meanLeftClick;
    vector<double> meanRightClick;
    vector<double> meanThumbClick;

public:
    MyAlgo()
    {
        readData();
        processData();
        computeGlobalNoice();
        computeFeatures();
        getDistanceFromClickType(ch4_tkeo);
    }
    void readData();
    void processData();
    double getTkeoValue(double v1, double v2, double v3);

    void computeGlobalNoice();
    void getEachChannelMaxValueForClickType(int *clickArray, int algoMode, int signFlag, double (&eachChannelMaxSample)[4]);
    double minOfThree(double x, double y, double z);

    void computeFeatures();
    void getFeaturesForClickType(int *clickArray, int algoMode, int signFlag, vector<vector<double>> &featureVector);

    void MyAlgo::getDistanceFromClickType(vector<double> aSampleOf4Channels);
};

#endif // !MyAlgo_HPP
