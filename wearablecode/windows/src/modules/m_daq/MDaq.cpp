#ifndef MDaq_CPP
#define MDaq_CPP

#include "MDaq.hpp"
#include <exception>
#include <windows.h>
#include <exception>

void MDaq::getVoltageFromChannel()
{
    while (1)
    {
        cbAInScan(BoardNum, LowChan, HighChan, Count, &Rate, Gain, ADData, Options);
        for (int I = 0; I < GB_TOTAL_NUMBER_OF_SAMPLES; I++)
        {
            channelVoltage1[I] = ADData[I * 4 + 0];
            channelVoltage2[I] = ADData[I * 4 + 1];
            channelVoltage3[I] = ADData[I * 4 + 2];
            channelVoltage4[I] = ADData[I * 4 + 3];
        }
    }
}

void MDaq::setupDaqCard()
{
    channelVoltage1 = new double[GB_TOTAL_NUMBER_OF_SAMPLES];
    channelVoltage2 = new double[GB_TOTAL_NUMBER_OF_SAMPLES];
    channelVoltage3 = new double[GB_TOTAL_NUMBER_OF_SAMPLES];
    channelVoltage4 = new double[GB_TOTAL_NUMBER_OF_SAMPLES];

    BoardNum = 0;
    Gain = BIP5VOLTS;

    LowChan = GB_DAQ_LOWER_CHANNEL_NUMBER;
    HighChan = GB_DAQ_HIGHER_CHANNEL_NUMBER;
    Count = (HighChan - LowChan + 1) * GB_TOTAL_NUMBER_OF_SAMPLES;
    ADData = new double[(HighChan - LowChan + 1) * GB_TOTAL_NUMBER_OF_SAMPLES];
    Rate = GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD;
    DataValue = 0;
    DataValue32 = 0;

    RevLevel = (float)CURRENTREVNUM;
    HighResAD = FALSE;
    Options = SCALEDATA;

    for (int i = 0; i < 8; i++)
    {
        f_n[i].setup(GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD, (double)(60.0 * (i + 1)), 15.0);
    }
    double lf = 50;
    double hf = 70;
    f_bs.setup(GB_FILTER_ORDER, GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD, (lf + hf) / 2, (hf - lf));

    lf = 20;
    hf = 500;
    f_bp.setup(6, GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD, (lf + hf) / 2, (hf - lf));

    cbDeclareRevision(&RevLevel);
    cbErrHandling(PRINTALL, DONTSTOP);
    cbGetConfig(BOARDINFO, BoardNum, 0, BIADRES, &ADRes);
    // CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)getVoltageFromChannel, NULL, NULL, NULL);
}

double MDaq::getChannelOneVoltage(int samplePosition)
{
    return channelVoltage1[samplePosition];
}

double MDaq::getChannelTwoVoltage(int samplePosition)
{
    // double tmp = channelVoltage2[samplePosition];
    // double tmp = f_bp.filter(channelVoltage2[samplePosition]);
    // for (int i = 0; i < 8; i++)
    // {
    //     tmp = f_n[i].filter(tmp);
    // }
    // // tmp = f_bp.filter(tmp);
    // return tmp;
    return channelVoltage2[samplePosition];
}

double MDaq::getChannelThreeVoltage(int samplePosition)
{
    return channelVoltage3[samplePosition];
}

double MDaq::getChannelFourVoltage(int samplePosition)
{
    return channelVoltage4[samplePosition];
}

#endif