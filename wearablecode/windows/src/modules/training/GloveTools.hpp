#ifndef GloveTools_HPP
#define GloveTools_HPP

#include <iostream>
#include <list>
#include "..\filter\FilterTools.cpp"
#include "..\m_daq\MDaq.cpp"
#include "..\edata\Global.cpp"
#include "..\mouse\MouseFunctions.cpp"
#include "..\algorithm\MyAlgo.cpp"
#include <filesystem>
using namespace std;

class GloveTools
{
private:

    std::vector<double> realTimeDataChannel1, realTimeDataChannel2, realTimeDataChannel3, realTimeDataChannel4;

    std::vector<double> trainingDataChannel1, trainingDataChannel2, trainingDataChannel3, trainingDataChannel4;
    std::vector<int> trainingDataLeftClick, trainingDataRightClick, trainingDataThumbClick;

    std::vector<double> demoTrainingDataChannel1, demoTrainingDataChannel2, demoTrainingDataChannel3, demoTrainingDataChannel4;
    std::vector<int> demoTrainingDataLeftClick, demoTrainingDataRightClick, demoTrainingDataThumbClick;
    int demoDataIndex = 0;
    int start = 0;
    int last = 0;
    double tmpCh1, tmpCh2, tmpCh3, tmpCh4;
    double tmpLC1, tmpRC1, tmpTC1;

    bool isTrainingRunning = false;
    bool isRealTimeRunning = false;

    string participantName;
    int trialNumber, numberOfChannelesUsedForTraining;

    double *chV1, *chV2, *chV3, *chV4;
    int *lC, *rC, *tC;
    FilterTools filterTools;
    MDaq mDaq;
    MyAlgo myAlgo;

public:
    GloveTools();

    int startRealTime();
    void startRealTimeSampleCollections();

    int startTraining();
    void startTrainingRecording();
    string stopTraining();

    string getRealTimeDataWithTkeo();
    string getRealTimeRawDemoData();
    string getRealTimeRawData();
    void setTrainingSettings(string pName, int trialNo, int noCh);
    void readDemoData();
    double getTkeoValue(double sample1, double sample2, double sample3, int channelNumber);
};

#endif // ! GloveTools_HPP