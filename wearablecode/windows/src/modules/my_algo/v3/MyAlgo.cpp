#ifndef MyAlgo_V2_CPP
#define MyAlgo_V2_CPP
#include "MyAlgo.hpp"
#include "MyAlgo_ReadNProcessData.cpp"
#include "MyAlgo_GetTkeo.cpp"
#include "MyAlgo_LabelClickType.cpp"
#include "MyAlgo_Train.cpp"
#include "MyAlgo_Evaluate.cpp"
#include "MyAlgo_RealTime_Play.cpp"

Json MyAlgo::getAlgoResults(string pName, int noCh, int trialNo, int cType)
{
    participantName = pName;
    trialNumber = trialNo;
    numberOfChannelesUsedForTraining = noCh;
    clickType = cType;
    readData();
    processData();
    cout << "Training Log 3 : MyAlgo read the data." << endl;
    return startAnalysing();
}

Json MyAlgo::startAnalysing()
{
    Json finalJson;
    finalJson["status"] = "failed";
    try
    {
        // set parameters
        Json tmp;
        std::vector<double> results;

        std::vector<std::vector<int>> channelID;
        channelID.push_back(channelIDLeft);
        channelID.push_back(channelIDRight);

        std::vector<double> thresholdValue;
        std::vector<std::vector<double>> d_feat;
        std::vector<std::vector<std::vector<double>>> featData;
        // Get Feature
        d_feat.clear();
        d_feat = tkoTime(d_emg, 1); // TKO feature extraction
        featData.push_back(d_feat);

        d_feat.clear();
        d_feat = tkoTime(d_emg, 3);
        featData.push_back(d_feat);

        d_feat.clear();
        d_feat = tkoSpatial(d_emg, 1);
        featData.push_back(d_feat);
        // Label the click of the timing
        int sampRate = GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD;
        //  int rangeBeforeClick = -0.1;
        int captureRangeBefore = round(0.1 * sampRate);
        int captureRangeAfter = round(0.05 * sampRate);
        std::vector<int> clickLabel;
        clickLabel = labelClickType(d_clicks, captureRangeBefore, captureRangeAfter); // 0: rest, 1,2,3 before right, left and thumb click, 4 within click

        cout << "Training Log 4 : MyAlgo labeled the data." << endl;

        // Training
        if (clickType == 1)
        {
            cout << "Training Log 5 : MyAlgo getting results for Left click" << endl;
            thresholdValues = fnTrain(featData, channelID, clickLabel, clickType);
            backupThresholdValues = thresholdValues;
            results = fnEvaluate(featData, channelID, thresholdValues, clickLabel, clickType, sampRate, refractoryTime, numV);
            tmp["true_positives"] = results.at(0);
            tmp["false_positives"] = results.at(1);
            tmp["average_lead"] = results.at(2);
            finalJson["left_click"] = tmp;
            cout << "Training Log 6 : MyAlgo got results for Left click" << endl;
        }
        else if (clickType == 2)
        {
            cout << "Training Log 5 : MyAlgo getting results for Right click" << endl;
            thresholdValues = fnTrain(featData, channelID, clickLabel, clickType);
            backupThresholdValues = thresholdValues;
            results = fnEvaluate(featData, channelID, thresholdValues, clickLabel, clickType, sampRate, refractoryTime, numV);
            tmp["true_positives"] = results.at(0);
            tmp["false_positives"] = results.at(1);
            tmp["average_lead"] = results.at(2);
            finalJson["right_click"] = tmp;
            cout << "Training Log 6 : MyAlgo got results for Left click" << endl;
        }
        else if (clickType == 3)
        {
            cout << "Training Log 5 : MyAlgo getting results for Both clicks" << endl;
           
            // For Left Click
            thresholdValuesLeftClick = fnTrainBothClicks(featData, clickLabel, channelIDLeft, 1);
           
            backupThresholdValuesLeftClick = thresholdValuesLeftClick;
           
            // For Right Click
            thresholdValuesRightClick = fnTrainBothClicks(featData, clickLabel, channelIDRight, 2);
            backupThresholdValuesRightClick = thresholdValuesRightClick;
         
            // For Left Click
            results = fnEvaluateBothClicks(featData, channelIDLeft, thresholdValuesLeftClick, clickLabel, 1, sampRate, refractoryTime, numV);
           
            tmp["true_positives"] = results.at(0);
            tmp["false_positives"] = results.at(1);
            tmp["average_lead"] = results.at(2);
            finalJson["left_click"] = tmp;
           
            // For Right Click
            results.clear();
            results = fnEvaluateBothClicks(featData, channelIDRight, thresholdValuesRightClick, clickLabel, 2, sampRate, refractoryTime, numV);
            tmp["true_positives"] = results.at(0);
            tmp["false_positives"] = results.at(1);
            tmp["average_lead"] = results.at(2);
            finalJson["right_click"] = tmp;
            results.clear();
            cout << "Training Log 6 : MyAlgo got results for Both clicks" << endl;
            finalJson["status"] = "success";
        }
    }
    catch (exception &e)
    {
        cout << e.what() << "   **Info**   File : " << __FILE__ << " Function : " << __func__ << " at Line : " << __LINE__ << '\n';
        cout << "Restarting startAnalysing()" << endl;
        startAnalysing();
    }
    cout << "Training Log 7 : Results are :-" << endl;
    std::cout << finalJson.dump(4) << endl;
    return finalJson;
}

bool MyAlgo::detectAndFireImpulseClicks(std::vector<std::vector<double>> raw_data_10_samples)
{
    bool isClickFired = false;
    int i = 0;
    std::vector<double> tmp;
    if (prevSampleRealTime.size() == 0 && prevPrevSampleRealTime.size() == 0)
    {
        prevPrevSampleRealTime = raw_data_10_samples.at(0);
        prevSampleRealTime = raw_data_10_samples.at(1);
        i = 2;
    }

    while (i < GB_TOTAL_NUMBER_OF_SAMPLES)
    {
        tmp = raw_data_10_samples.at(i);
        threeSamplesRealTime.push_back(prevPrevSampleRealTime);
        threeSamplesRealTime.push_back(prevSampleRealTime);
        threeSamplesRealTime.push_back(tmp);

        /**
         * For Left Click Detection
        */
        if (clickType == 1)
        {
            if (fnRealTime(threeSamplesRealTime, channelIDLeft, thresholdValues, 1))
            {
                MouseFunctions::Instance().fireMouseEvent('l', 'd');
                isClickFired = true;
            }
        }
        /**
         * For Right Click Detection
        */
        else if (clickType == 2)
        {

            if (fnRealTime(threeSamplesRealTime, channelIDRight, thresholdValues, 1))
            {

                MouseFunctions::Instance().fireMouseEvent('r', 'd');
                isClickFired = true;
            }
        }
        /**
         * For Both Click Detection
        */
        else if (clickType == 3)
        {
            string s = fnRealTimeBoth(threeSamplesRealTime, 1);
            if (s == "left")
            {
                MouseFunctions::Instance().fireMouseEvent('l', 'd');
            }
            else if (s == "right")
            {
                MouseFunctions::Instance().fireMouseEvent('r', 'd');
            }
            else if (s == "both")
            {
                MouseFunctions::Instance().fireMouseEvent('l', 'd');
                MouseFunctions::Instance().fireMouseEvent('r', 'd');
            }
            isClickFired = true;
        }

        prevPrevSampleRealTime = prevSampleRealTime;
        prevSampleRealTime = tmp;
        tmp.clear();
        threeSamplesRealTime.clear();
        i++;
    }
    return isClickFired;
}

#endif // !MyAlgo_CPP
