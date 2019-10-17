#ifndef GloveTools_CPP
#define GloveTools_CPP

#include "GloveTools.hpp"
#include "GloveTools_Training.cpp"
#include "GloveTools_RealTime_Play.cpp"
#include "GloveTools_RealTime_Data.cpp"

GloveTools::GloveTools()
{
    if (gb_getCurrentEnvirnoment() == GB_ENV_STAGING || gb_getCurrentEnvirnoment() == GB_ENV_PRODUCTION)
    {
        std::thread newThread(&MDaq::getVoltageFromChannel, mDaq);
        newThread.detach();
    }
    MouseFunctions::Instance().setupMouseMonitoring();

    chV1 = new double[GB_TOTAL_NUMBER_OF_SAMPLES];
    chV2 = new double[GB_TOTAL_NUMBER_OF_SAMPLES];
    chV3 = new double[GB_TOTAL_NUMBER_OF_SAMPLES];
    chV4 = new double[GB_TOTAL_NUMBER_OF_SAMPLES];
    lC = new int[GB_TOTAL_NUMBER_OF_SAMPLES];
    rC = new int[GB_TOTAL_NUMBER_OF_SAMPLES];
    tC = new int[GB_TOTAL_NUMBER_OF_SAMPLES];
}

void GloveTools::setTrainingSettings(string pName, int trialNo, int noCh, string cType)
{
    participantName = pName;
    trialNumber = trialNo;
    numberOfChannelesUsedForTraining = noCh;
    if (cType == "left")
    {
        clickType = 1;
    }
    else if (cType == "right")
    {
        clickType = 2;
    }
    else if (cType == "both")
    {
        clickType = 3;
    }
}

#endif // ! GloveTools_CPP