#ifndef GloveTools_CPP
#define GloveTools_CPP

#include "GloveTools.hpp"

#include <iostream>
#include <fstream>

GloveTools::GloveTools()
{
 
        std::thread newThread(&MDaq::getVoltageFromChannel, mDaq);
        newThread.detach();

    MouseFunctions::Instance().setupMouseMonitoring();

    chV1 = new double[GB_TOTAL_NUMBER_OF_SAMPLES];
    chV2 = new double[GB_TOTAL_NUMBER_OF_SAMPLES];
    chV3 = new double[GB_TOTAL_NUMBER_OF_SAMPLES];
    chV4 = new double[GB_TOTAL_NUMBER_OF_SAMPLES];
    lC = new int[GB_TOTAL_NUMBER_OF_SAMPLES];
    rC = new int[GB_TOTAL_NUMBER_OF_SAMPLES];
    tC = new int[GB_TOTAL_NUMBER_OF_SAMPLES];
}

int GloveTools::startTraining()
{
    isTrainingRunning = true;
    std::thread newThread(&GloveTools::startTrainingRecording, this);
    newThread.detach();
    return 1;
}

void GloveTools::stopTraining()
{
    isTrainingRunning = false;

    ofstream myfile("data.txt");
    if (myfile.is_open())
    {
        auto ch1 = trainingDataChannel1.begin();
        auto ch2 = trainingDataChannel2.begin();
        auto ch3 = trainingDataChannel3.begin();
        auto ch4 = trainingDataChannel4.begin();
        auto lc = trainingDataLeftClick.begin();
        auto rc = trainingDataRightClick.begin();
        auto tc = trainingDataThumbClick.begin();

        while (ch1 != trainingDataChannel1.end())
        {
            myfile << *ch1++ << " " << *ch2++ << " " << *ch3++ << " " << *ch4++ << " " << *lc++ << " " << *rc++ << " " << *tc++ << endl;
        }
        myfile.close();
    }
    cout << "\nRecording Saved";
}

void GloveTools::startTrainingRecording()
{
    double t1 = 0.0, t2 = 0.0, t3 = 0.0, t4 = 0.0;
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

double GloveTools::getTkeoValue(double sample1, double sample2, double sample3, int channelNumber)
{
    double v1 = filterTools.getFilteredValue(channelNumber, sample1);
    double v2 = filterTools.getFilteredValue(channelNumber, sample2);
    double v3 = filterTools.getFilteredValue(channelNumber, sample3);
    v1 = v1 * v1 * v1;
    v2 = v2 * v2 * v2;
    v3 = v3 * v3 * v3;
    double result = v2 * v2 - v1 * v3;
    return result;
}

string GloveTools::getRealTimeRawData()
{
    if (chV1[0] == 0.0 || chV2[0] == 0.0 || chV3[0] == 0.0 || chV4[0] == 0.0)
    {
    }
    else
    {
        while (chV1[0] == mDaq.getChannelOneVoltage(0) || chV2[0] == mDaq.getChannelTwoVoltage(0) || chV3[0] == mDaq.getChannelThreeVoltage(0) || chV4[0] == mDaq.getChannelFourVoltage(0))
        {
        }
    }

    string chV1String = "", chV2String = "", chV3String = "", chV4String = "";
    string lCString = "", rCString = "", tCString = "";

    int lc, rc, tc;
    lc = MouseFunctions::Instance().getLeftMouseStatus();
    rc = MouseFunctions::Instance().getRightMouseStatus();
    tc = MouseFunctions::Instance().getThumbMouseStatus();
    for (int i = 0; i < GB_TOTAL_NUMBER_OF_SAMPLES; i++)
    {
        chV1[i] = mDaq.getChannelOneVoltage(i);
        chV2[i] = mDaq.getChannelTwoVoltage(i);
        chV3[i] = mDaq.getChannelThreeVoltage(i);
        chV4[i] = mDaq.getChannelFourVoltage(i);
        // lC[i] = MouseFunctions::Instance().getLeftMouseStatusAtIndex(i);
        // rC[i] = MouseFunctions::Instance().getRightMouseStatusAtIndex(i);
        // tC[i] = MouseFunctions::Instance().getThumbMouseStatusAtIndex(i);
        lC[i] = lc;
        rC[i] = rc;
        tC[i] = tc;
        if (i == 0)
        {
            chV1String = to_string(chV1[i]);
            chV2String = to_string(chV2[i]);
            chV3String = to_string(chV3[i]);
            chV4String = to_string(chV4[i]);
            lCString = to_string(lc);
            rCString = to_string(rc);
            tCString = to_string(tc);
        }
        else
        {
            chV1String = chV1String + "," + to_string(chV1[i]);
            chV2String = chV2String + "," + to_string(chV2[i]);
            chV3String = chV3String + "," + to_string(chV3[i]);
            chV4String = chV4String + "," + to_string(chV4[i]);
            lCString = lCString + "," + to_string(lc);
            rCString = rCString + "," + to_string(rc);
            tCString = tCString + "," + to_string(tc);
        }
    }
    string data = "{\"type\":\"real_time_raw_data\", \"total_samples\": " + to_string(GB_TOTAL_NUMBER_OF_SAMPLES) + ", \"ch_v1\": [" + chV1String + "]" + ", \"ch_v2\":[" + chV2String + "]" + ", \"ch_v3\":[" + chV3String + "]" + ", \"ch_v4\":[" + chV4String + "]" + ", \"left_click\": [" + lCString + "]" + ", \"right_click\": [" + rCString + "]" + ", \"thumb_click\": [" + tCString + "]" + "}";
    return data;
}

string GloveTools::getRealTimeDebuggingData()
{
    if (chV1[0] == 0.0 || chV2[0] == 0.0 || chV3[0] == 0.0 || chV4[0] == 0.0)
    {
    }
    else
    {
        while (chV1[0] == mDaq.getChannelOneVoltage(0) || chV2[0] == mDaq.getChannelTwoVoltage(0) || chV3[0] == mDaq.getChannelThreeVoltage(0) || chV4[0] == mDaq.getChannelFourVoltage(0))
        {
        }
    }

    string chV1String = "", chV2String = "", chV3String = "", chV4String = "";
    string chV1TkeoString = "", chV2TkeoString = "", chV3TkeoString = "", chV4TkeoString = "";
    string lCString = "", rCString = "";
    double ch1Tkeo, ch2Tkeo, ch3Tkeo, ch4Tkeo;
    for (int i = 0; i < GB_TOTAL_NUMBER_OF_SAMPLES; i++)
    {
        chV1[i] = mDaq.getChannelOneVoltage(i);
        chV2[i] = mDaq.getChannelTwoVoltage(i);
        chV3[i] = mDaq.getChannelThreeVoltage(i);
        chV4[i] = mDaq.getChannelFourVoltage(i);
        lC[i] = MouseFunctions::Instance().getLeftMouseStatusAtIndex(i);
        rC[i] = MouseFunctions::Instance().getRightMouseStatusAtIndex(i);

        if (i == GB_TOTAL_NUMBER_OF_SAMPLES - 1)
        {
            ch1Tkeo = getTkeoValue(chV1[i - 2], chV1[i - 1], chV1[i], 1);
            ch2Tkeo = getTkeoValue(chV2[i - 2], chV2[i - 1], chV2[i], 2);
            ch3Tkeo = getTkeoValue(chV3[i - 2], chV3[i - 1], chV3[i], 3);
            ch4Tkeo = getTkeoValue(chV4[i - 2], chV4[i - 1], chV4[i], 4);
            chV1TkeoString = chV1TkeoString + "," + to_string(ch1Tkeo) + "," + to_string(ch1Tkeo) + "," + to_string(ch1Tkeo);
            chV2TkeoString = chV2TkeoString + "," + to_string(ch2Tkeo) + "," + to_string(ch2Tkeo) + "," + to_string(ch2Tkeo);
            chV3TkeoString = chV3TkeoString + "," + to_string(ch3Tkeo) + "," + to_string(ch3Tkeo) + "," + to_string(ch3Tkeo);
            chV4TkeoString = chV4TkeoString + "," + to_string(ch4Tkeo) + "," + to_string(ch4Tkeo) + "," + to_string(ch4Tkeo);
        }
        else if (i == 2)
        {
            ch1Tkeo = getTkeoValue(chV1[i - 2], chV1[i - 1], chV1[i], 1);
            ch2Tkeo = getTkeoValue(chV2[i - 2], chV2[i - 1], chV2[i], 2);
            ch3Tkeo = getTkeoValue(chV3[i - 2], chV3[i - 1], chV3[i], 3);
            ch4Tkeo = getTkeoValue(chV4[i - 2], chV4[i - 1], chV4[i], 4);
            chV1TkeoString = to_string(ch1Tkeo);
            chV2TkeoString = to_string(ch2Tkeo);
            chV3TkeoString = to_string(ch3Tkeo);
            chV4TkeoString = to_string(ch4Tkeo);
        }
        else if (i > 2)
        {
            ch1Tkeo = getTkeoValue(chV1[i - 2], chV1[i - 1], chV1[i], 1);
            ch2Tkeo = getTkeoValue(chV2[i - 2], chV2[i - 1], chV2[i], 2);
            ch3Tkeo = getTkeoValue(chV3[i - 2], chV3[i - 1], chV3[i], 3);
            ch4Tkeo = getTkeoValue(chV4[i - 2], chV4[i - 1], chV4[i], 4);
            chV1TkeoString = chV1TkeoString + "," + to_string(ch1Tkeo);
            chV2TkeoString = chV2TkeoString + "," + to_string(ch2Tkeo);
            chV3TkeoString = chV3TkeoString + "," + to_string(ch3Tkeo);
            chV4TkeoString = chV4TkeoString + "," + to_string(ch4Tkeo);
        }

        if (i == 0)
        {
            chV1String = to_string(chV1[i]);
            chV2String = to_string(chV2[i]);
            chV3String = to_string(chV3[i]);
            chV4String = to_string(chV4[i]);
            lCString = to_string(lC[i]);
            rCString = to_string(rC[i]);
        }
        else
        {
            chV1String = chV1String + "," + to_string(chV1[i]);
            chV2String = chV2String + "," + to_string(chV2[i]);
            chV3String = chV3String + "," + to_string(chV3[i]);
            chV4String = chV4String + "," + to_string(chV4[i]);
            lCString = lCString + "," + to_string(lC[i]);
            rCString = rCString + "," + to_string(rC[i]);
        }
    }

    string data = "{\"type\":\"real_time_debugging_data\", \"total_samples\": " + to_string(GB_TOTAL_NUMBER_OF_SAMPLES) + ", \"ch_v1\": [" + chV1String + "]" + ", \"ch_v2\":[" + chV2String + "]" + ", \"ch_v3\":[" + chV3String + "]" + ", \"ch_v4\":[" + chV4String + "]" + ", \"ch_v1_tkeo\": [" + chV1TkeoString + "]" + ", \"ch_v2_tkeo\":[" + chV2TkeoString + "]" + ", \"ch_v3_tkeo\":[" + chV3TkeoString + "]" + ", \"ch_v4_tkeo\":[" + chV4TkeoString + "]" + ", \"left_click\": [" + lCString + "]" + ", \"right_click\": [" + rCString + "]" + "}";
    return data;
}

#endif // ! GloveTools_CPP