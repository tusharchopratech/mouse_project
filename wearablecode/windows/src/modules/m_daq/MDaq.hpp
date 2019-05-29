#ifndef MDaq_H
#define MDaq_H

#include <iostream>
#include <stdio.h>
#include "..\lib\daq\cbw.h"

#define MAX_STR_LENGTH 64
#define MAX_DEV_COUNT 100

int BoardNum;
int Gain;
WORD DataValue;
DWORD DataValue32;

float RevLevel;
BOOL HighResAD;
int ADRes;
int Options;

int channelNumber1 = 11;
int channelNumber2 = 12;
int channelNumber3 = 13;
int channelNumber4 = 14;
float channelVoltage1 = 0.0;
float channelVoltage2 = 0.0;
float channelVoltage3 = 0.0;
float channelVoltage4 = 0.0;

void getVoltageFromChannel()
{
    while (1)
    {
        cbAIn(BoardNum, channelNumber1, Gain, &DataValue);
        cbToEngUnits(BoardNum, Gain, DataValue, &channelVoltage1);

        cbAIn(BoardNum, channelNumber2, Gain, &DataValue);
        cbToEngUnits(BoardNum, Gain, DataValue, &channelVoltage2);

        cbAIn(BoardNum, channelNumber3, Gain, &DataValue);
        cbToEngUnits(BoardNum, Gain, DataValue, &channelVoltage3);

        cbAIn(BoardNum, channelNumber4, Gain, &DataValue);
        cbToEngUnits(BoardNum, Gain, DataValue, &channelVoltage4);
    }
}

void setupDaqCard()
{
    BoardNum = 0;
    Gain = BIP5VOLTS;
    DataValue = 0;
    DataValue32 = 0;

    RevLevel = (float)CURRENTREVNUM;
    HighResAD = FALSE;
    Options = 0;

    cbDeclareRevision(&RevLevel);
    cbErrHandling(PRINTALL, DONTSTOP);
    cbGetConfig(BOARDINFO, BoardNum, 0, BIADRES, &ADRes);

    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)getVoltageFromChannel, NULL, NULL, NULL);
}

float getChannelOneVoltage()
{
    return channelVoltage1;
}

float getChannelTwoVoltage()
{
    return channelVoltage2;
}

float getChannelThreeVoltage()
{
    return channelVoltage3;
}

float getChannelFourVoltage()
{
    return channelVoltage4;
}

#endif