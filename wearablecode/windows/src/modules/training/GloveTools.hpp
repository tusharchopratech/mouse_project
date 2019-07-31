#ifndef GloveTools_HPP
#define GloveTools_HPP

#include <iostream>
// #include <vector>
#include <list> 
#include "..\filter\FilterTools.cpp"
#include "..\m_daq\MDaq.cpp"
#include "..\edata\Global.cpp"
#include "..\mouse\MouseFunctions.cpp"

using namespace std;

class GloveTools
{
private:
    list<double> trainingDataChannel1, trainingDataChannel2, trainingDataChannel3, trainingDataChannel4;
    list<int> trainingDataLeftClick, trainingDataRightClick, trainingDataThumbClick;

    bool isTrainingRunning = false;

    double *chV1, *chV2, *chV3, *chV4;
    int *lC, *rC, *tC;
    FilterTools filterTools;
    MDaq mDaq;

public:
    GloveTools();
    int startTraining();
    void startTrainingRecording();
    void stopTraining();
    // string getResults();

    string getRealTimeDebuggingData();
    string getRealTimeRawData();
    double getTkeoValue(double sample1, double sample2, double sample3, int channelNumber);
};

#endif // ! GloveTools_HPP