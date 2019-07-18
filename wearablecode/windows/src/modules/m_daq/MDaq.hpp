#ifndef MDaq_H
#define MDaq_H

#include <iostream>
#include <stdio.h>
#include "..\lib\daq\cbw.h"
#include "..\edata\Global.cpp"

// #define MAX_STR_LENGTH 64
// #define MAX_DEV_COUNT 100

class MDaq
{

private:
    int BoardNum;
    int Gain;
    long Count;
    long Rate;
    int LowChan;
    int HighChan;
    WORD DataValue;
    DWORD DataValue32;

    float RevLevel;
    BOOL HighResAD;
    int ADRes;
    int Options;
    int totalNumberOfSamplesForChannels;

    double *ADData;
    double *channelVoltage1, *channelVoltage2, *channelVoltage3, *channelVoltage4;

public:
    MDaq()
    {
        setupDaqCard();
    }
    void getVoltageFromChannel();
    void setupDaqCard();
    double getChannelOneVoltage(int samplePosition);
    double getChannelTwoVoltage(int samplePosition);
    double getChannelThreeVoltage(int samplePosition);
    double getChannelFourVoltage(int samplePosition);
};

#endif