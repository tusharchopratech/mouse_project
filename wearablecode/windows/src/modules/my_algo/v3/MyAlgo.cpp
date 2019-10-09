#ifndef MyAlgo_V2_CPP
#define MyAlgo_V2_CPP
#include "MyAlgo.hpp"
#include "MyAlgo_ReadNProcessData.cpp"
#include "MyAlgo_GetTkeo.cpp"
#include "MyAlgo_LabelClickType.cpp"
#include "MyAlgo_Train.cpp"
#include "MyAlgo_Evaluate.cpp"
#include "MyAlgo_RealTime_Play.cpp"

Json MyAlgo::getAlgoResults(string pName, int noCh, int trialNo)
{
    participantName = pName;
    trialNumber = trialNo;
    numberOfChannelesUsedForTraining = noCh;
    readData();
    processData();
    return startAnalysing();
}

Json MyAlgo::startAnalysing()
{
    // set parameters

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

    // Training

    thresholdValues = fnTrain(featData, channelID, clickLabel, clickType);

    // Testing on the training data
    double refractoryTime = 0.1;
    int numV = 1;
    std::vector<double> results = fnEvaluate(featData, channelID, thresholdValues, clickLabel, clickType, sampRate, refractoryTime, numV);

    Json finalJson;
    finalJson["true_positives"] = results.at(0);
    finalJson["false_positives"] = results.at(1);
    finalJson["average_lead"] = results.at(2);
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
         * For Left Right Detection
        */
        else if (clickType == 2)
        {

            if (fnRealTime(threeSamplesRealTime, channelIDRight, thresholdValues, 1))
            {
                MouseFunctions::Instance().fireMouseEvent('r', 'd');
                isClickFired = true;
            }
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
