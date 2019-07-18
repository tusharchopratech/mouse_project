#ifndef GloveTools_CPP
#define GloveTools_CPP

#include "GloveTools.hpp"


// int GloveTools::startTraining()
// {
//     cout << yo;
//     return 0;
// }

void GloveTools::setupGloveTools()
{
    MouseFunctions::Instance().setupMouseMonitoring();

    chV1 = new double[GB_TOTAL_NUMBER_OF_SAMPLES];
    chV2 = new double[GB_TOTAL_NUMBER_OF_SAMPLES];
    chV3 = new double[GB_TOTAL_NUMBER_OF_SAMPLES];
    chV4 = new double[GB_TOTAL_NUMBER_OF_SAMPLES];
    lC = new int[GB_TOTAL_NUMBER_OF_SAMPLES];
    rC = new int[GB_TOTAL_NUMBER_OF_SAMPLES];
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

string GloveTools::getSocketData()
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
        lC[i] =  MouseFunctions::Instance().getLeftMouseStatusAtIndex(i);
        rC[i] =  MouseFunctions::Instance().getRightMouseStatusAtIndex(i);

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

    string l = to_string(MouseFunctions::Instance().getLeftMouseStatus());
    string r = to_string(MouseFunctions::Instance().getRightMouseStatus());
    string data = "{\"type\":\"real_time_data\", \"total_samples\": " + to_string(GB_TOTAL_NUMBER_OF_SAMPLES) + ", \"ch_v1\": [" + chV1String + "]" + ", \"ch_v2\":[" + chV2String + "]" + ", \"ch_v3\":[" + chV3String + "]" + ", \"ch_v4\":[" + chV4String + "]" + ", \"ch_v1_tkeo\": [" + chV1TkeoString + "]" + ", \"ch_v2_tkeo\":[" + chV2TkeoString + "]" + ", \"ch_v3_tkeo\":[" + chV3TkeoString + "]" + ", \"ch_v4_tkeo\":[" + chV4TkeoString + "]" + ", \"left_click\": [" + lCString + "]" + ", \"right_click\": [" + rCString + "]" + "}";
    return data;
}


#endif // ! GloveTools_CPP