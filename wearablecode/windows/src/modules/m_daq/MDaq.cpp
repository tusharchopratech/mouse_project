#ifndef MDaq_CPP
#define MDaq_CPP

#include "MDaq.hpp"


void MDaq::getVoltageFromChannel()
{
    while (1)
    {
        cbAInScan(BoardNum, LowChan, HighChan, Count, &Rate, Gain, ADData, Options);
        for (int I = 0; I < totalNumberOfSamplesForChannels; I++)
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

    LowChan = 11;
    HighChan = 14;
    Count = (HighChan - LowChan + 1) * totalNumberOfSamplesForChannels;
    ADData = new double[(HighChan - LowChan + 1) * totalNumberOfSamplesForChannels];
    Rate = 2000;
    DataValue = 0;
    DataValue32 = 0;

    RevLevel = (float)CURRENTREVNUM;
    HighResAD = FALSE;
    Options = SCALEDATA;

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