#ifndef GloveTools_HPP
#define GloveTools_HPP

#include <iostream>
#include <vector>
#include "..\filter\FilterTools.cpp"
#include "..\m_daq\MDaq.cpp"
#include "..\edata\Global.cpp"
#include "..\mouse\MouseFunctions.cpp"

using namespace std;

class GloveTools
{
private:
    // vector<int> channel1, channel2, channel3;
    // int yo = 10;

    double *chV1, *chV2, *chV3, *chV4;
    int *lC, *rC;
    FilterTools filterTools;
    MDaq mDaq; 
	
public:
    GloveTools()
    {
        std::thread newThread(&MDaq::getVoltageFromChannel, mDaq);
       
        setupGloveTools();
    }
    // int startTraining();
    // int stopTraining();
    // string getResults();

    void setupGloveTools();
    string getSocketData();
    double getTkeoValue(double sample1, double sample2, double sample3, int channelNumber);
};

#endif // ! GloveTools_HPP