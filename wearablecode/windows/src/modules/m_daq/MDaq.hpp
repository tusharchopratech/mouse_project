#ifndef MDaq_H
#define MDaq_H

#include <iostream>
#include <stdio.h>
#include "..\lib\daq\cbw.h"

// #define MAX_STR_LENGTH 64
// #define MAX_DEV_COUNT 100

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
float *channelVoltage1, *channelVoltage2, *channelVoltage3, *channelVoltage4;

void getVoltageFromChannel()
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

void setupDaqCard(int totalSamples)
{
    totalNumberOfSamplesForChannels = totalSamples;
    channelVoltage1 = new float[totalNumberOfSamplesForChannels];
    channelVoltage2 = new float[totalNumberOfSamplesForChannels];
    channelVoltage3 = new float[totalNumberOfSamplesForChannels];
    channelVoltage4 = new float[totalNumberOfSamplesForChannels];
    
    BoardNum = 0;
    Gain = BIP5VOLTS;
   
    LowChan = 11;
    HighChan = 14;
    Count = (HighChan - LowChan + 1)*totalNumberOfSamplesForChannels;
    ADData = new double[(HighChan - LowChan + 1)*totalNumberOfSamplesForChannels];
    Rate = 2000;
    DataValue = 0;
    DataValue32 = 0;

    RevLevel = (float)CURRENTREVNUM;
    HighResAD = FALSE;
    Options = SCALEDATA;

    cbDeclareRevision(&RevLevel);
    cbErrHandling(PRINTALL, DONTSTOP);
    cbGetConfig(BOARDINFO, BoardNum, 0, BIADRES, &ADRes);

    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)getVoltageFromChannel, NULL, NULL, NULL);
}


float getChannelOneVoltage(int samplePosition)
{
    return channelVoltage1[samplePosition];
}

float getChannelTwoVoltage(int samplePosition)
{
    return channelVoltage2[samplePosition];
}

float getChannelThreeVoltage(int samplePosition)
{
    return channelVoltage3[samplePosition];
}

float getChannelFourVoltage(int samplePosition)
{
    return channelVoltage4[samplePosition];
}

#endif