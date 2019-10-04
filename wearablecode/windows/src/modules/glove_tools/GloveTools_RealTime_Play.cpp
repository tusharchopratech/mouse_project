#ifndef GloveTools_RealTime_Play_HPP
#define GloveTools_RealTime_Play_HPP

#include "GloveTools.hpp"

int GloveTools::startRealTime()
{

    isRealTimeRunning = true;
    MouseFunctions::Instance().startRealTimePlay();
    if (gb_getCurrentEnvirnoment() == GB_ENV_PRODUCTION || gb_getCurrentEnvirnoment() == GB_ENV_STAGING)
    {
        std::thread newThread(&GloveTools::startRealTimeSampleCollections, this);
        newThread.detach();
    }
    else if (gb_getCurrentEnvirnoment() == GB_ENV_DEVELOPMENT)
    {

        std::thread newThread(&GloveTools::startDemoSampleCollections, this);
        newThread.detach();
    }
    cout << "Real Time Started!" << endl;
    return 1;
}

void GloveTools::startRealTimeSampleCollections()
{
    double t1 = 0.0, t2 = 0.0, t3 = 0.0, t4 = 0.0;

    std::vector<std::vector<double>> raw_data_10_samples;
    std::vector<double> tmp;
    while (isRealTimeRunning)
    {
        tmp.clear();
        raw_data_10_samples.clear();
        if (t1 == 0.0 || t2 == 0.0 || t3 == 0.0 || t4 == 0.0)
        {
        }
        else
        {
            while (t1 == mDaq.getChannelOneVoltage(0) || t2 == mDaq.getChannelTwoVoltage(0) || t3 == mDaq.getChannelThreeVoltage(0) || t4 == mDaq.getChannelFourVoltage(0))
            {
            }
        }

        for (int i = 0; i < GB_TOTAL_NUMBER_OF_SAMPLES; i++)
        {
            tmp.push_back(mDaq.getChannelOneVoltage(i));
            tmp.push_back(mDaq.getChannelTwoVoltage(i));
            tmp.push_back(mDaq.getChannelThreeVoltage(i));
            tmp.push_back(mDaq.getChannelFourVoltage(i));
            raw_data_10_samples.push_back(tmp);
            tmp.clear();
        }

        t1 = mDaq.getChannelOneVoltage(0);
        t2 = mDaq.getChannelTwoVoltage(0);
        t3 = mDaq.getChannelThreeVoltage(0);
        t4 = mDaq.getChannelFourVoltage(0);

        myAlgo.detectAndFireImpulseClicks(raw_data_10_samples);
    }
    cout << "Real Time Stopped!" << endl;
}

void GloveTools::startDemoSampleCollections()
{
    std::vector<std::vector<double>> raw_data_10_samples;
    std::vector<double> tmp;
    while (isRealTimeRunning)
    {
        startRealTimePlay = demoDataIndexRealTimePlay;
        lastRealTimePlay = demoDataIndexRealTimePlay + GB_TOTAL_NUMBER_OF_SAMPLES;

        if (lastRealTimePlay > demoTrainingDataChannel1.size())
        {
            demoDataIndexRealTimePlay = 0;
            startRealTimePlay = demoDataIndexRealTimePlay;
            lastRealTimePlay = demoDataIndexRealTimePlay + GB_TOTAL_NUMBER_OF_SAMPLES;
        }

        Sleep(7);

        for (int i = startRealTimePlay; i < lastRealTimePlay; i++)
        {
            tmp.push_back(demoTrainingDataChannel1.at(i));
            tmp.push_back(demoTrainingDataChannel2.at(i));
            tmp.push_back(demoTrainingDataChannel3.at(i));
            tmp.push_back(demoTrainingDataChannel4.at(i));
            raw_data_10_samples.push_back(tmp);
            tmp.clear();
        }
        if (myAlgo.detectAndFireImpulseClicks(raw_data_10_samples))
        {
            // cout << "Click fired at sample no. " << lastRealTimePlay << " -- at time : " << gb_getCurrentTimeInMilliseconds()<<endl;
        }
        raw_data_10_samples.clear();
        demoDataIndexRealTimePlay = lastRealTimePlay;
    }
}

void GloveTools::stopRealTime()
{
    isRealTimeRunning = false;
    MouseFunctions::Instance().stopRealTimePlay();
}

#endif