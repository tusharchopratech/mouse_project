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
            while (t1 == mDaq.getChannelOneVoltage(0) || t2 == mDaq.getChannelTwoVoltage(0) || t3 == mDaq.getChannelThreeVoltage(0) || t4 == mDaq.getChannelFourVoltage(0))
            {
            }
        }

        int lCStatus = MouseFunctions::Instance().getLeftMouseStatus();
        int rCStatus = MouseFunctions::Instance().getRightMouseStatus();
        int tCStatus = MouseFunctions::Instance().getThumbMouseStatus();

        for (int i = 0; i < GB_TOTAL_NUMBER_OF_SAMPLES; i++)
        {
            trainingDataChannel1.push_back(mDaq.getChannelOneVoltage(i));
            trainingDataChannel2.push_back(mDaq.getChannelTwoVoltage(i));
            trainingDataChannel3.push_back(mDaq.getChannelThreeVoltage(i));
            trainingDataChannel4.push_back(mDaq.getChannelFourVoltage(i));
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

string GloveTools::stopTraining()
{
    isTrainingRunning = false;
    cout << "Stop Training 1" << endl;
    if (!std::experimental::filesystem::remove_all(GB_IMPULSE_DIRECTORY))
    {
        cout << "Unable to delete folder : " << GB_IMPULSE_DIRECTORY << endl;
    }
    if (!CreateDirectoryA(GB_IMPULSE_DIRECTORY.c_str(), NULL))
    {
        cout << "Unable to create folder : " << GB_IMPULSE_DIRECTORY << endl;
    }
    cout << "Stop Training 2" << endl;
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
    cout << "Stop Training 3" << endl;
    string file = GB_IMPULSE_DIRECTORY + "/data_" + participantName + std::to_string(trialNumber) + "_C" + std::to_string(numberOfChannelesUsedForTraining) + ".txt";
    std::ofstream myfile(file);
    if (myfile.fail())
    {
        cout << "Unable to write file : " << file << endl;
    }
    cout << "Stop Training 4" << endl;
    if (myfile.is_open())
    {
        cout << "Stop Training 4.1 Data sizes : " << trainingDataChannel1.size() << " " << trainingDataChannel2.size() << " " << trainingDataChannel3.size() << " " << trainingDataChannel4.size() << " " << trainingDataLeftClick.size() << " " << trainingDataRightClick.size() << " " << trainingDataThumbClick.size() << endl;
        for (int i = 0; i < trainingDataChannel1.size(); i++)
        {
            myfile << trainingDataChannel1.at(i) << " " << trainingDataChannel2.at(i) << " " << trainingDataChannel3.at(i) << " " << trainingDataChannel4.at(i) << " " << trainingDataLeftClick.at(i) << " " << trainingDataRightClick.at(i) << " " << trainingDataThumbClick.at(i) << endl;
        }

        cout << "Stop Training 4.2" << endl;

        myfile.close();
        cout << "Stop Training 4.3" << endl;
    }
    else
    {
        cout << "Error! File is not open.";
    }
    cout << "Stop Training 5" << endl;
    string result = myAlgo.getAlgoResults(participantName, numberOfChannelesUsedForTraining, trialNumber);
    cout << "Stop Training 6" << endl;
    return result;
}

#endif