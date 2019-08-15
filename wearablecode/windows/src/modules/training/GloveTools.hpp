#ifndef GloveTools_HPP
#define GloveTools_HPP

#include <iostream>
#include <list>
#include "..\filter\FilterTools.cpp"
#include "..\m_daq\MDaq.cpp"
#include "..\edata\Global.cpp"
#include "..\mouse\MouseFunctions.cpp"
#include "..\algorithm\MyAlgo.cpp"

using namespace std;

class GloveTools
{
private:
    list<double> trainingDataChannel1, trainingDataChannel2, trainingDataChannel3, trainingDataChannel4;
    list<int> trainingDataLeftClick, trainingDataRightClick, trainingDataThumbClick;

    std::vector<double> demoTrainingDataChannel1, demoTrainingDataChannel2, demoTrainingDataChannel3, demoTrainingDataChannel4;
    std::vector<int> demoTrainingDataLeftClick, demoTrainingDataRightClick, demoTrainingDataThumbClick;
    int demoDataIndex = 0;
    int start = 0;
    int last = 0;
    double tmpCh1, tmpCh2, tmpCh3, tmpCh4;
    double tmpLC1, tmpRC1, tmpTC1;

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

    string getRealTimeDataWithTkeo();
    string getRealTimeRawDemoData();
    string getRealTimeRawData();
    void readDemoData();
    double getTkeoValue(double sample1, double sample2, double sample3, int channelNumber);
};

#endif // ! GloveTools_HPP