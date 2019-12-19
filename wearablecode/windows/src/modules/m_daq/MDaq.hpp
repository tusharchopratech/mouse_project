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

    double *ADData;
    double *channelVoltage1, *channelVoltage2, *channelVoltage3, *channelVoltage4;

    Iir::RBJ::IIRNotch f_n[8];
    Iir::Butterworth::BandStop<GB_FILTER_ORDER> f_bs;
    Iir::Butterworth::BandPass<6> f_bp;

public:
    MDaq()
    {
    }
    void getVoltageFromChannel();
    void setupDaqCard();
    double getChannelOneVoltage(int samplePosition);
    double getChannelTwoVoltage(int samplePosition);
    double getChannelThreeVoltage(int samplePosition);
    double getChannelFourVoltage(int samplePosition);
};

#endif