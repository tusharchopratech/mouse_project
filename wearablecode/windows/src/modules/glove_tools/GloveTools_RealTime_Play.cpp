#ifndef GloveTools_RealTime_Play_HPP
#define GloveTools_RealTime_Play_HPP

#include "GloveTools.hpp"
#include <exception>

int GloveTools::startRealTime(double thresholdPrecentageLeft, double thresholdPrecentageRight)
{

    isRealTimeRunning = true;
    raw_data_n_samples.clear();
    myAlgo.setThresholdValues(thresholdPrecentageLeft, thresholdPrecentageRight);
    MouseFunctions::Instance().startRealTimePlay();
    if (gb_getCurrentEnvirnoment() == GB_ENV_PRODUCTION || gb_getCurrentEnvirnoment() == GB_ENV_STAGING)
    {
        std::thread newThread(&GloveTools::startRealTimeSampleCollectionsForRealTimePlay, this);
        newThread.detach();
        std::thread newThread2(&GloveTools::writeRealTimeData, this);
        newThread2.detach();
    }
    else if (gb_getCurrentEnvirnoment() == GB_ENV_DEVELOPMENT)
    {

        std::thread newThread(&GloveTools::startDemoSampleCollections, this);
        newThread.detach();
    }
    cout << "Real Time Started!" << endl;
    return 1;
}

void GloveTools::startRealTimeSampleCollectionsForRealTimePlay()
{
    double t1 = 0.0, t2 = 0.0, t3 = 0.0, t4 = 0.0;

    std::vector<std::vector<double>> raw_data_10_samples;
    std::vector<double> tmp;
    // int yo = 0;
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

        int lc = MouseFunctions::Instance().getLeftMouseStatus();
        int rc = MouseFunctions::Instance().getRightMouseStatus();
        int tc = MouseFunctions::Instance().getThumbMouseStatus();
        int ilc, irc;

        if (clickType == 1)
        {
            ilc = MouseFunctions::Instance().getImpulseLeftClickStatus();
            irc = -1;
        }
        else if (clickType == 2)
        {
            irc = MouseFunctions::Instance().getImpulseRightClickStatus();
            ilc = -1;
        }
        else if (clickType == 3)
        {
            ilc = MouseFunctions::Instance().getImpulseLeftClickStatus();
            irc = MouseFunctions::Instance().getImpulseRightClickStatus();
        }

        for (int i = 0; i < GB_TOTAL_NUMBER_OF_SAMPLES; i++)
        {
            tmp.push_back(mDaq.getChannelOneVoltage(i));
            tmp.push_back(mDaq.getChannelTwoVoltage(i));
            tmp.push_back(mDaq.getChannelThreeVoltage(i));
            tmp.push_back(mDaq.getChannelFourVoltage(i));
            raw_data_10_samples.push_back(tmp);
            tmp.push_back(lc);
            tmp.push_back(rc);
            tmp.push_back(tc);

            if (clickType == 1)
            {
                tmp.push_back(ilc);
            }
            else if (clickType == 2)
            {
                tmp.push_back(ilc);
            }
            else if (clickType == 3)
            {
                tmp.push_back(ilc);
                tmp.push_back(irc);
            }

            raw_data_n_samples.push_back(tmp);
            tmp.clear();
        }

        t1 = mDaq.getChannelOneVoltage(0);
        t2 = mDaq.getChannelTwoVoltage(0);
        t3 = mDaq.getChannelThreeVoltage(0);
        t4 = mDaq.getChannelFourVoltage(0);

        myAlgo.detectAndFireImpulseClicks(raw_data_10_samples);
    }
}

Json GloveTools::getRealTimeGamePlayDataForDisplay()
{
    Json json;
    try
    {
        std::vector<double> v1, v2, v3, v4, v5, v6, v7, v8, v9;
        int size = raw_data_n_samples.size();
        std::vector<string> logs = MouseFunctions::Instance().getImpulseLogs();

        int start = realTimeGamePlayDataForDisplaySizeIndex;
        int end = size;
        for (int i = start; i < end; i++)
        {
            v1.push_back(raw_data_n_samples.at(i).at(0));
            v2.push_back(raw_data_n_samples.at(i).at(1));
            v3.push_back(raw_data_n_samples.at(i).at(2));
            v4.push_back(raw_data_n_samples.at(i).at(3));
            v5.push_back(raw_data_n_samples.at(i).at(4));
            v6.push_back(raw_data_n_samples.at(i).at(5));
            v7.push_back(raw_data_n_samples.at(i).at(6));
            v8.push_back(raw_data_n_samples.at(i).at(7));
            v9.push_back(raw_data_n_samples.at(i).at(8));
        }
        json["logs"] = logs;
        json["total_samples"] = v1.size();
        json["ch_v1"] = v1;
        json["ch_v2"] = v2;
        json["ch_v3"] = v3;
        json["ch_v4"] = v4;
        json["left_click"] = v5;
        json["right_click"] = v6;
        json["thumb_click"] = v7;
        json["impulse_left_click"] = v8;
        json["impulse_right_click"] = v9;

        realTimeGamePlayDataForDisplaySizeIndex = size;
    }
    catch (exception &e)
    {
        cout << e.what() << "   **Info**   File : " << __FILE__ << " Function : " << __func__ << " at Line : " << __LINE__ << '\n';
    }
    return json;
}

void GloveTools::writeRealTimeData()
{
    try
    {
        string file = GB_IMPULSE_DIRECTORY + "/data_real_time_play_" + participantName + std::to_string(trialNumber) + "_C" + std::to_string(numberOfChannelesUsedForTraining) + ".txt";
        std::ofstream myfile(file, std::ios::app);
        if (myfile.fail())
        {
            cout << "Unable to write file : " << file << endl;
        }
        else
        {
            if (myfile.is_open())
            {
                for (int i = 0; i < raw_data_n_samples.size(); i++)
                {
                    myfile << raw_data_n_samples.at(i).at(0) << " " << raw_data_n_samples.at(i).at(1) << " " << raw_data_n_samples.at(i).at(2) << " " << raw_data_n_samples.at(i).at(3) << " "
                           << raw_data_n_samples.at(i).at(4) << " " << raw_data_n_samples.at(i).at(5) << " " << raw_data_n_samples.at(i).at(6) << " " << raw_data_n_samples.at(i).at(7)
                           << endl;
                }
            }
            else
            {
                cout << "Error! File is not open.";
            }
        }
        myfile.close();
    }
    catch (exception &e)
    {
        cout << e.what() << "   **Info**   File : " << __FILE__ << " Function : " << __func__ << " at Line : " << __LINE__ << '\n';
    }
}

void GloveTools::stopRealTime()
{
    isRealTimeRunning = false;
    MouseFunctions::Instance().stopRealTimePlay();
    cout << "Writing Real Time Data!" << endl;
    writeRealTimeData();
    raw_data_n_samples.clear();
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

#endif