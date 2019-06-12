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
double ADData[12];

float channelVoltage1[3] = {0.0, 0.0, 0.0};
float channelVoltage2[3] = {0.0, 0.0, 0.0};
float channelVoltage3[3] = {0.0, 0.0, 0.0};
float channelVoltage4[3] = {0.0, 0.0, 0.0};

void getVoltageFromChannel()
{
    while (1)
    {   

        cbAInScan(BoardNum, LowChan, HighChan, Count, &Rate, Gain, ADData, Options);
        for (int I = 0; I < 3; I++)
        {
            channelVoltage1[I] = ADData[I * 4 + 0];
            channelVoltage2[I] = ADData[I * 4 + 1];
            channelVoltage3[I] = ADData[I * 4 + 2];
            channelVoltage4[I] = ADData[I * 4 + 3];
            // printf("\n\n I : %d    Ch1 : %.6f Ch2 : %.6f Ch3 : %.6f Ch4 : %.6f ", I, channelVoltage1[I], channelVoltage2[I], channelVoltage3[I], channelVoltage4[I]);
            //  printf("\n\n I : %d   Ch1 : %.6f Ch2 : %.6f Ch3 : %.6f Ch4 : %.6f ", I, ADData[I * 4 + 0], ADData[I * 4 + 1], ADData[I * 4 + 2], ADData[I * 4 + 3]);
            // printf("\nCh1 : %.6f Ch2 : %.6f Ch3 : %.6f Ch4 : %.6f", ch1, ch2, ch3, ch4);
            // printf("\nCh1 : %.6f Ch2 : %.6f Ch3 : %.6f Ch4 : %.6f ", ch1, ch2, ch3, ch4);
        }

        // cbAIn(BoardNum, channelNumber1, Gain, &DataValue);
        // cbToEngUnits(BoardNum, Gain, DataValue, &channelVoltage1);

        // cbAIn(BoardNum, channelNumber2, Gain, &DataValue);
        // cbToEngUnits(BoardNum, Gain, DataValue, &channelVoltage2);

        // cbAIn(BoardNum, channelNumber3, Gain, &DataValue);
        // cbToEngUnits(BoardNum, Gain, DataValue, &channelVoltage3);

        // cbAIn(BoardNum, channelNumber4, Gain, &DataValue);
        // cbToEngUnits(BoardNum, Gain, DataValue, &channelVoltage4);
    }
}

void setupDaqCard()
{
    BoardNum = 0;
    Gain = BIP5VOLTS;
    LowChan = 11;
    HighChan = 14;
    Count = 12;
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