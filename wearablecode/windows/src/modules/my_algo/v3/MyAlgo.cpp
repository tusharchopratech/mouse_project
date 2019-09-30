#ifndef MyAlgo_V2_CPP
#define MyAlgo_V2_CPP
#include "MyAlgo.hpp"
#include "MyAlgo_ReadNProcessData.cpp"
#include "MyAlgo_GetTkeo.cpp"
#include "MyAlgo_LabelClickType.cpp"
#include "MyAlgo_Train.cpp"
#include "MyAlgo_Evaluate.cpp"

string MyAlgo::getAlgoResults(string pName, int noCh, int trialNo)
{
    participantName = pName;
    trialNumber = trialNo;
    numberOfChannelesUsedForTraining = noCh;
    readData();
    processData();
    return startAnalysing();
}

string MyAlgo::startAnalysing()
{
    // set parameters
    int clickType = 1;                        // only two values: 1 is for left and 2 is for right
    std::vector<int> channelIDRight{3, 3, 3}; // feature sequence: tko, p3tko, stko
    std::vector<int> channelIDLeft{1, 1, 4};
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

    // **************RealTime Test************************
    // if it is not within click and not in the refractory time (refractoryTime after the last detected click), start detection
    // input is the rawdata with only three samples
    // bool clickDetected = fnRealTime(d_rawdata, channelID.at(clickType-1), thresholdValues, numV);
    // return if the click is deteced or not
    //**********************

    Json finalJson;
    finalJson["type"] = "algo_outputs";
    finalJson["true_positives"] = results.at(0);
    finalJson["false_positives"] = results.at(1);
    finalJson["average_lead"] = results.at(2);
    std::cout << finalJson.dump(4) << endl;
    return finalJson.dump();
}

#endif // !MyAlgo_CPP
