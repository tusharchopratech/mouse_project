#ifndef GloveTools_RealTime_Data_HPP
#define GloveTools_RealTime_Data_HPP

#include "GloveTools.hpp"

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
    // Json json;
    // json["type"]="real_time_raw_data";
    // json["total_samples"]= to_string(GB_TOTAL_NUMBER_OF_SAMPLES);
    // json["ch_v1"]="real_time_raw_data";
    // json["type"]="real_time_raw_data";
    // json["type"]="real_time_raw_data";
    string data = "{\"type\":\"real_time_raw_data\", \"total_samples\": " + to_string(GB_TOTAL_NUMBER_OF_SAMPLES) + ", \"ch_v1\": [" + chV1String + "]" + ", \"ch_v2\":[" + chV2String + "]" + ", \"ch_v3\":[" + chV3String + "]" + ", \"ch_v4\":[" + chV4String + "]" + ", \"left_click\": [" + lCString + "]" + ", \"right_click\": [" + rCString + "]" + ", \"thumb_click\": [" + tCString + "]" + "}";
    return data;
}

void GloveTools::readDemoData()
{
    demoTrainingDataChannel1.clear();
    demoTrainingDataChannel2.clear();
    demoTrainingDataChannel3.clear();
    demoTrainingDataChannel4.clear();
    demoTrainingDataLeftClick.clear();
    demoTrainingDataRightClick.clear();
    demoTrainingDataThumbClick.clear();

    std::string line;
    std::ifstream infile(GB_IMPULSE_DEV_DIRECTORY + "/data.txt");
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        std::string s = line;
        std::string delimiter = " ";
        size_t pos = 0;
        std::string token;
        int i = 0;

        while ((pos = s.find(delimiter)) != std::string::npos)
        {
            token = s.substr(0, pos);
            // std::cout << token << std::endl;
            s.erase(0, pos + delimiter.length());
            if (i == 0)
            {
                demoTrainingDataChannel1.push_back(std::stod(token));
            }
            else if (i == 1)
            {
                demoTrainingDataChannel2.push_back(std::stod(token));
            }
            else if (i == 2)
            {
                demoTrainingDataChannel3.push_back(std::stod(token));
            }
            else if (i == 3)
            {
                demoTrainingDataChannel4.push_back(std::stod(token));
            }
            else if (i == 4)
            {
                demoTrainingDataLeftClick.push_back(std::stoi(token));
            }
            else if (i == 5)
            {
                demoTrainingDataRightClick.push_back(std::stoi(token));
            }
            i++;
        }
        // std::cout << s << std::endl;
        demoTrainingDataThumbClick.push_back(std::stoi(s));
    }
}

string GloveTools::getRealTimeRawDemoData()
{
    start = demoDataIndex;
    last = demoDataIndex + GB_TOTAL_NUMBER_OF_SAMPLES;
    string chV1String = "", chV2String = "", chV3String = "", chV4String = "";
    string lCString = "", rCString = "", tCString = "";
    if (last > demoTrainingDataChannel1.size())
    {
        demoDataIndex = 0;
        start = demoDataIndex;
        last = demoDataIndex + GB_TOTAL_NUMBER_OF_SAMPLES;
    }

    Sleep(7);

    for (int i = start; i < last; i++)
    {
        tmpCh1 = demoTrainingDataChannel1.at(i);
        tmpCh2 = demoTrainingDataChannel2.at(i);
        tmpCh3 = demoTrainingDataChannel3.at(i);
        tmpCh4 = demoTrainingDataChannel4.at(i);
        tmpLC1 = demoTrainingDataLeftClick.at(i);
        tmpRC1 = demoTrainingDataRightClick.at(i);
        tmpTC1 = demoTrainingDataThumbClick.at(i);
        if (i == start)
        {
            chV1String = to_string(tmpCh1);
            chV2String = to_string(tmpCh2);
            chV3String = to_string(tmpCh3);
            chV4String = to_string(tmpCh4);
            lCString = to_string(tmpLC1);
            rCString = to_string(tmpRC1);
            tCString = to_string(tmpTC1);
        }
        else
        {
            chV1String = chV1String + "," + to_string(tmpCh1);
            chV2String = chV2String + "," + to_string(tmpCh2);
            chV3String = chV3String + "," + to_string(tmpCh3);
            chV4String = chV4String + "," + to_string(tmpCh4);
            lCString = lCString + "," + to_string(tmpLC1);
            rCString = rCString + "," + to_string(tmpRC1);
            tCString = tCString + "," + to_string(tmpTC1);
        }
    }
    string data = "{\"type\":\"real_time_raw_data\", \"total_samples\": " + to_string(GB_TOTAL_NUMBER_OF_SAMPLES) + ", \"ch_v1\": [" + chV1String + "]" + ", \"ch_v2\":[" + chV2String + "]" + ", \"ch_v3\":[" + chV3String + "]" + ", \"ch_v4\":[" + chV4String + "]" + ", \"left_click\": [" + lCString + "]" + ", \"right_click\": [" + rCString + "]" + ", \"thumb_click\": [" + tCString + "]" + "}";
    demoDataIndex = last;

    return data;
}

#endif