#ifndef GloveTools_CPP
#define GloveTools_CPP

#include "GloveTools.hpp"
#include "GloveTools_Training.cpp"
#include "GloveTools_RealTime_Play.cpp"
#include "GloveTools_RealTime_Data.cpp"

GloveTools::GloveTools()
{

    if (gb_getCurrentHardwareType() == GB_HARDWARE_MDAQ)
    {
        mDaq.setupDaqCard();
    }

    if (gb_getCurrentEnvirnoment() == GB_ENV_STAGING || gb_getCurrentEnvirnoment() == GB_ENV_PRODUCTION)
    {
        if (gb_getCurrentHardwareType() == GB_HARDWARE_MDAQ)
        {
            std::thread newThread2(&MDaq::getVoltageFromChannel, mDaq);
            newThread2.detach();
        }
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

Json GloveTools::setTrainingSettings(string pName, int trialNo, int noCh, string cType, string sessionType)
{
    Json json;

    if (sessionType == "old")
    {
        if (ifFileExist(pName, trialNo, noCh))
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
            json["status"] = "success";
            json["value"] = "old_file_found";
        }
        else
        {
            json["status"] = "failed";
            json["value"] = "old_file_not_found";
        }
    }
    else
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
        json["status"] = "success";
        json["value"] = "settings_set_for_new_recording";
    }

    return json;
}

bool GloveTools::ifFileExist(string participantName, int trialNumber, int numberOfChannelesUsedForTraining)
{
    string filename = GB_IMPULSE_DIRECTORY + "/data_" + participantName + std::to_string(trialNumber) + "_C" + std::to_string(numberOfChannelesUsedForTraining) + ".txt";
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}

bool GloveTools::deleteFile(string participantName, int trialNumber, int numberOfChannelesUsedForTraining)
{
    if (ifFileExist(participantName, trialNumber, numberOfChannelesUsedForTraining))
    {
        string filename = GB_IMPULSE_DIRECTORY + "/data_" + participantName + std::to_string(trialNumber) + "_C" + std::to_string(numberOfChannelesUsedForTraining) + ".txt";
        DeleteFile(filename.c_str());
        return true;
    }
    return false;
}

#endif // ! GloveTools_CPP