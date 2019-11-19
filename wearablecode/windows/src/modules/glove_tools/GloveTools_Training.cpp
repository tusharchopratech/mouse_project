#ifndef GloveTools_Training_HPP
#define GloveTools_Training_HPP

#include "GloveTools.hpp"

int GloveTools::startTraining()
{
    isTrainingRunning = true;
    std::thread newThread(&GloveTools::startTrainingRecording, this);
    newThread.detach();
    if (!std::experimental::filesystem::remove_all(GB_IMPULSE_DIRECTORY))
    {
        cout << "Unable to delete folder : " << GB_IMPULSE_DIRECTORY << endl;
    }
    return 1;
}

void GloveTools::startTrainingRecording()
{
    double t1 = 0.0, t2 = 0.0, t3 = 0.0, t4 = 0.0;
    trainingDataChannel1.clear();
    trainingDataChannel2.clear();
    trainingDataChannel3.clear();
    trainingDataChannel4.clear();
    trainingDataLeftClick.clear();
    trainingDataRightClick.clear();
    trainingDataThumbClick.clear();

    while (isTrainingRunning)
    {
        if (t1 == 0.0 || t2 == 0.0 || t3 == 0.0 || t4 == 0.0)
        {
        }
        else
        {
            if (gb_getCurrentHardwareType() == GB_HARDWARE_MDAQ)
            {
                while (t1 == mDaq.getChannelOneVoltage(0) || t2 == mDaq.getChannelTwoVoltage(0) || t3 == mDaq.getChannelThreeVoltage(0) || t4 == mDaq.getChannelFourVoltage(0))
                {
                }
            }
            else if (gb_getCurrentHardwareType() == GB_HARDWARE_STM32)
            {
                while (t1 == stm32.getChannelOneVoltage(0) || t2 == stm32.getChannelTwoVoltage(0) || t3 == stm32.getChannelThreeVoltage(0) || t4 == stm32.getChannelFourVoltage(0))
                {
                }
            }
        }

        int lCStatus = MouseFunctions::Instance().getLeftMouseStatus();
        int rCStatus = MouseFunctions::Instance().getRightMouseStatus();
        int tCStatus = MouseFunctions::Instance().getThumbMouseStatus();

        for (int i = 0; i < GB_TOTAL_NUMBER_OF_SAMPLES; i++)
        {
            if (gb_getCurrentHardwareType() == GB_HARDWARE_MDAQ)
            {
                trainingDataChannel1.push_back(mDaq.getChannelOneVoltage(i));
                trainingDataChannel2.push_back(mDaq.getChannelTwoVoltage(i));
                trainingDataChannel3.push_back(mDaq.getChannelThreeVoltage(i));
                trainingDataChannel4.push_back(mDaq.getChannelFourVoltage(i));
            }
            else if (gb_getCurrentHardwareType() == GB_HARDWARE_STM32)
            {
                trainingDataChannel1.push_back(stm32.getChannelOneVoltage(i));
                trainingDataChannel2.push_back(stm32.getChannelTwoVoltage(i));
                trainingDataChannel3.push_back(stm32.getChannelThreeVoltage(i));
                trainingDataChannel4.push_back(stm32.getChannelFourVoltage(i));
            }
            trainingDataLeftClick.push_back(lCStatus);
            trainingDataRightClick.push_back(rCStatus);
            trainingDataThumbClick.push_back(tCStatus);
        }

        t1 = mDaq.getChannelOneVoltage(0);
        t2 = mDaq.getChannelTwoVoltage(0);
        t3 = mDaq.getChannelThreeVoltage(0);
        t4 = mDaq.getChannelFourVoltage(0);
    }
}

Json GloveTools::getRealTimeTraingDataForDisplay()
{
    Json json;
    std::vector<double> v1, v2, v3, v4, v5, v6, v7;
    int size = trainingDataChannel1.size();

    int start = realTimeTraingDataForDisplaySizeIndex;
    int end = size;
    for (int i = start; i < end; i++)
    {
        v1.push_back(trainingDataChannel1.at(i));
        v2.push_back(trainingDataChannel2.at(i));
        v3.push_back(trainingDataChannel3.at(i));
        v4.push_back(trainingDataChannel4.at(i));
        v5.push_back(trainingDataLeftClick.at(i));
        v6.push_back(trainingDataRightClick.at(i));
        v7.push_back(trainingDataThumbClick.at(i));
    }
    json["total_samples"] = v1.size();
    json["ch_v1"] = v1;
    json["ch_v2"] = v2;
    json["ch_v3"] = v3;
    json["ch_v4"] = v4;
    json["left_click"] = v5;
    json["right_click"] = v6;
    json["thumb_click"] = v7;
    realTimeTraingDataForDisplaySizeIndex = size;
    return json;
}

Json GloveTools::stopTraining()
{
    isTrainingRunning = false;
    try
    {
        if (!std::experimental::filesystem::remove_all(GB_IMPULSE_DIRECTORY))
        {
            cout << "Unable to delete folder : " << GB_IMPULSE_DIRECTORY << endl;
        }
        if (!CreateDirectoryA(GB_IMPULSE_DIRECTORY.c_str(), NULL))
        {
            cout << "Unable to create folder : " << GB_IMPULSE_DIRECTORY << endl;
        }
        if (gb_getCurrentEnvirnoment() == GB_ENV_DEVELOPMENT)
        {
            trainingDataChannel1.clear();
            trainingDataChannel2.clear();
            trainingDataChannel3.clear();
            trainingDataChannel4.clear();
            trainingDataLeftClick.clear();
            trainingDataRightClick.clear();
            trainingDataThumbClick.clear();
            trainingDataChannel1 = demoTrainingDataChannel1;
            trainingDataChannel2 = demoTrainingDataChannel2;
            trainingDataChannel3 = demoTrainingDataChannel3;
            trainingDataChannel4 = demoTrainingDataChannel4;
            trainingDataLeftClick = demoTrainingDataLeftClick;
            trainingDataRightClick = demoTrainingDataRightClick;
            trainingDataThumbClick = demoTrainingDataThumbClick;
        }
        string file = GB_IMPULSE_DIRECTORY + "/data_" + participantName + std::to_string(trialNumber) + "_C" + std::to_string(numberOfChannelesUsedForTraining) + ".txt";
        std::ofstream myfile(file);
        if (myfile.fail())
        {
            cout << "Unable to write file : " << file << endl;
        }
        if (myfile.is_open())
        {
            for (int i = 0; i < trainingDataChannel1.size(); i++)
            {
                myfile << trainingDataChannel1.at(i) << " " << trainingDataChannel2.at(i) << " " << trainingDataChannel3.at(i) << " " << trainingDataChannel4.at(i) << " " << trainingDataLeftClick.at(i) << " " << trainingDataRightClick.at(i) << " " << trainingDataThumbClick.at(i) << endl;
            }
            myfile.close();
        }
        else
        {
            cout << "Error! File is not open.";
        }
    }
    catch (exception &e)
    {
        cout << e.what() << "   **Info**   File : " << __FILE__ << " Function : " << __func__ << " at Line : " << __LINE__ << '\n';
    }
    Json result = myAlgo.getAlgoResults(participantName, numberOfChannelesUsedForTraining, trialNumber, clickType);
    return result;
}

#endif