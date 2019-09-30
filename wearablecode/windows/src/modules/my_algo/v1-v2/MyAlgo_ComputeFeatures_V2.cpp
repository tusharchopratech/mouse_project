#ifndef MyAlgo_ComputeFeatures_V2_CPP
#define MyAlgo_ComputeFeatures_V2_CPP
#include "MyAlgo.hpp"

string MyAlgo::predictAndWriteResults()
{
    string info = "";
    int leftTotalTruePositives, rightTotalTruePositives;
    Json finalJson, tmp, bestAlgoModeJson;

    finalJson["type"] = "algo_outputs";

    std::vector<int> leftClickIndices = getActualClickIndices(trainingDataLeftClick);
    std::vector<int> rightClickIndices = getActualClickIndices(trainingDataRightClick);
    finalJson["actual_left_click_indices"] = leftClickIndices;
    finalJson["actual_right_click_indices"] = rightClickIndices;

    // ********************************************************************* tkeo_sign_both ********************************************************************************
    computeGlobalNoice(ALGO_MODE_TKEO, ALGO_SIGN_FLAG_BOTH);
    computeFeatures(ALGO_MODE_TKEO, ALGO_SIGN_FLAG_BOTH);
    info = predictAndWriteAlgoSpecificResults(ALGO_MODE_TKEO, ALGO_SIGN_FLAG_BOTH, "data_result_algo_tkeo_sign_both");
    bestAlgoModeJson = Json::parse(info);
    // cout << bestAlgoModeJson.dump(4) << endl;
    tmp.push_back(bestAlgoModeJson);

    if (bestAlgoModeJson["left_click"]["true_positives"]["lead"].size() > leftTotalTruePositives)
    {
        leftTotalTruePositives = bestAlgoModeJson["left_click"]["true_positives"]["lead"].size();
        bestAlgoModeLC = ALGO_MODE_TKEO;
        bestAlgoSignFlagLC = ALGO_SIGN_FLAG_BOTH;
    }
    if (bestAlgoModeJson["right_click"]["true_positives"]["lead"].size() > rightTotalTruePositives)
    {
        rightTotalTruePositives = bestAlgoModeJson["right_click"]["true_positives"]["lead"].size();
        bestAlgoModeRC = ALGO_MODE_TKEO;
        bestAlgoSignFlagRC = ALGO_SIGN_FLAG_BOTH;
    }
    // ttmp=1;

    if (gb_getCurrentEnvirnoment() == GB_ENV_DEVELOPMENT || gb_getCurrentEnvirnoment() == GB_ENV_STAGING)
    {
        cout << "For tkeo_sign_both" << endl;
        cout << "Left click TP/Actual Clicks : " << (double)((double)leftTotalTruePositives / (double)leftClickIndices.size()) << endl;
        cout << "Right click TP/Actual Clicks : " << (double)((double)rightTotalTruePositives / (double)rightClickIndices.size()) << endl;
        cout << "Left click FP/Actual Clicks : " << (double)((double)bestAlgoModeJson["left_click"]["false_positives_indices"].size() / (double)leftClickIndices.size()) << endl;
        cout << "Right click FP/Actual Clicks : " << (double)((double)bestAlgoModeJson["right_click"]["false_positives_indices"].size() / (double)rightClickIndices.size()) << endl
             << endl;
    }

    // ********************************************************************* f_tkeo_sign_both ********************************************************************************
    computeGlobalNoice(ALGO_MODE_F_TKEO, ALGO_SIGN_FLAG_BOTH);
    computeFeatures(ALGO_MODE_F_TKEO, ALGO_SIGN_FLAG_BOTH);
    info = predictAndWriteAlgoSpecificResults(ALGO_MODE_F_TKEO, ALGO_SIGN_FLAG_BOTH, "data_result_algo_f_tkeo_sign_both");
    bestAlgoModeJson = Json::parse(info);
    tmp.push_back(bestAlgoModeJson);

    leftTotalTruePositives = bestAlgoModeJson["left_click"]["true_positives"]["lead"].size();
    rightTotalTruePositives = bestAlgoModeJson["right_click"]["true_positives"]["lead"].size();
    bestAlgoModeLC = ALGO_MODE_F_TKEO;
    bestAlgoSignFlagLC = ALGO_SIGN_FLAG_BOTH;
    bestAlgoModeRC = ALGO_MODE_F_TKEO;
    bestAlgoSignFlagRC = ALGO_SIGN_FLAG_BOTH;

    if (gb_getCurrentEnvirnoment() == GB_ENV_DEVELOPMENT || gb_getCurrentEnvirnoment() == GB_ENV_STAGING)
    {
        cout << "For f_tkeo_sign_both" << endl;
        cout << "Left click TP/Actual Clicks : " << (double)((double)leftTotalTruePositives / (double)leftClickIndices.size()) << endl;
        cout << "Right click TP/Actual Clicks : " << (double)((double)rightTotalTruePositives / (double)rightClickIndices.size()) << endl;
        cout << "Left click FP/Actual Clicks : " << (double)((double)bestAlgoModeJson["left_click"]["false_positives_indices"].size() / (double)leftClickIndices.size()) << endl;
        cout << "Right click FP/Actual Clicks : " << (double)((double)bestAlgoModeJson["right_click"]["false_positives_indices"].size() / (double)rightClickIndices.size()) << endl
             << endl;
    }

    // ********************************************************************* p3_tkeo_sign_both ********************************************************************************
    computeGlobalNoice(ALGO_MODE_P3_TKEO, ALGO_SIGN_FLAG_BOTH);
    computeFeatures(ALGO_MODE_P3_TKEO, ALGO_SIGN_FLAG_BOTH);
    info = predictAndWriteAlgoSpecificResults(ALGO_MODE_P3_TKEO, ALGO_SIGN_FLAG_BOTH, "data_result_algo_p3_tkeo_sign_both");
    bestAlgoModeJson = Json::parse(info);
    // cout << bestAlgoModeJson.dump(4) << endl;
    tmp.push_back(bestAlgoModeJson);

    if (bestAlgoModeJson["left_click"]["true_positives"]["lead"].size() > leftTotalTruePositives)
    {
        leftTotalTruePositives = bestAlgoModeJson["left_click"]["true_positives"]["lead"].size();
        bestAlgoModeLC = ALGO_MODE_P3_TKEO;
        bestAlgoSignFlagLC = ALGO_SIGN_FLAG_BOTH;
    }
    if (bestAlgoModeJson["right_click"]["true_positives"]["lead"].size() > rightTotalTruePositives)
    {
        rightTotalTruePositives = bestAlgoModeJson["right_click"]["true_positives"]["lead"].size();
        bestAlgoModeRC = ALGO_MODE_P3_TKEO;
        bestAlgoSignFlagRC = ALGO_SIGN_FLAG_BOTH;
    }

    if (gb_getCurrentEnvirnoment() == GB_ENV_DEVELOPMENT || gb_getCurrentEnvirnoment() == GB_ENV_STAGING)
    {
        cout << "For p3_tkeo_sign_both" << endl;
        cout << "Left click TP/Actual Clicks : " << (double)((double)leftTotalTruePositives / (double)leftClickIndices.size()) << endl;
        cout << "Right click TP/Actual Clicks : " << (double)((double)rightTotalTruePositives / (double)rightClickIndices.size()) << endl;
        cout << "Left click FP/Actual Clicks : " << (double)((double)bestAlgoModeJson["left_click"]["false_positives_indices"].size() / (double)leftClickIndices.size()) << endl;
        cout << "Right click FP/Actual Clicks : " << (double)((double)bestAlgoModeJson["right_click"]["false_positives_indices"].size() / (double)rightClickIndices.size()) << endl
             << endl;
    }

    // ********************************************************************* p3_f_tkeo_sign_both ********************************************************************************
    computeGlobalNoice(ALGO_MODE_P3_F_TKEO, ALGO_SIGN_FLAG_BOTH);
    computeFeatures(ALGO_MODE_P3_F_TKEO, ALGO_SIGN_FLAG_BOTH);
    info = predictAndWriteAlgoSpecificResults(ALGO_MODE_P3_F_TKEO, ALGO_SIGN_FLAG_BOTH, "data_result_algo_p3_f_tkeo_sign_both");
    bestAlgoModeJson = Json::parse(info);
    // cout << bestAlgoModeJson.dump(4) << endl;
    tmp.push_back(bestAlgoModeJson);

    if (bestAlgoModeJson["left_click"]["true_positives"]["lead"].size() > leftTotalTruePositives)
    {
        leftTotalTruePositives = bestAlgoModeJson["left_click"]["true_positives"]["lead"].size();
        bestAlgoModeLC = ALGO_MODE_P3_F_TKEO;
        bestAlgoSignFlagLC = ALGO_SIGN_FLAG_BOTH;
    }
    if (bestAlgoModeJson["right_click"]["true_positives"]["lead"].size() > rightTotalTruePositives)
    {
        rightTotalTruePositives = bestAlgoModeJson["right_click"]["true_positives"]["lead"].size();
        bestAlgoModeRC = ALGO_MODE_P3_F_TKEO;
        bestAlgoSignFlagRC = ALGO_SIGN_FLAG_BOTH;
    }
    if (gb_getCurrentEnvirnoment() == GB_ENV_DEVELOPMENT || gb_getCurrentEnvirnoment() == GB_ENV_STAGING)
    {
        cout << "For p3_f_tkeo_sign_both" << endl;
        cout << "Left click TP/Actual Clicks : " << (double)((double)leftTotalTruePositives / (double)leftClickIndices.size()) << endl;
        cout << "Right click TP/Actual Clicks : " << (double)((double)rightTotalTruePositives / (double)rightClickIndices.size()) << endl;
        cout << "Left click FP/Actual Clicks : " << (double)((double)bestAlgoModeJson["left_click"]["false_positives_indices"].size() / (double)leftClickIndices.size()) << endl;
        cout << "Right click FP/Actual Clicks : " << (double)((double)bestAlgoModeJson["right_click"]["false_positives_indices"].size() / (double)rightClickIndices.size()) << endl
             << endl;
    }
    finalJson["results"] = tmp;
    if (gb_getCurrentEnvirnoment() == GB_ENV_DEVELOPMENT || gb_getCurrentEnvirnoment() == GB_ENV_STAGING)
    {
        //  cout<< finalJson.dump(4)<<endl<<endl;
    }
    return finalJson.dump();
}

string MyAlgo::predictAndWriteAlgoSpecificResults(int algoMode, int signFlag, string algoType)
{
    Json info;
    info["algo_type"] = algoType;
    std::vector<int> truePositivesLeftClickLead;
    std::vector<int> truePositivesLeftClickIndex;
    std::vector<int> falsePositivesLeftClickIndex;
    std::vector<int> truePositivesRightClickLead;
    std::vector<int> truePositivesRightClickIndex;
    std::vector<int> falsePositivesRightClickIndex;
    std::vector<int> truePositivesThumbClickLead;
    std::vector<int> truePositivesThumbClickIndex;
    std::vector<int> falsePositivesThumbClickIndex;
    int lead = -100;

    int nextLeftClickCheckAfterSampleNumber = 0;
    int nextRightClickCheckAfterSampleNumber = 0;
    int nextThumbClickCheckAfterSampleNumber = 0;

    std::vector<double> tmpCh1;
    std::vector<double> tmpCh2;
    std::vector<double> tmpCh3;
    std::vector<double> tmpCh4;

    std::vector<double> sample1;
    std::vector<double> sample2;
    std::vector<double> sample3;
    std::vector<std::vector<double>> threeSamples;
    string clickType;

    if (algoMode == ALGO_MODE_RAW)
    {
        tmpCh1 = ch1_raw;
        tmpCh2 = ch2_raw;
        tmpCh3 = ch3_raw;
        tmpCh4 = ch4_raw;
    }
    else if (algoMode == ALGO_MODE_TKEO)
    {
        tmpCh1 = ch1_tkeo;
        tmpCh2 = ch2_tkeo;
        tmpCh3 = ch3_tkeo;
        tmpCh4 = ch4_tkeo;
    }
    else if (algoMode == ALGO_MODE_P3_TKEO)
    {
        tmpCh1 = ch1_p3_tkeo;
        tmpCh2 = ch2_p3_tkeo;
        tmpCh3 = ch3_p3_tkeo;
        tmpCh4 = ch4_p3_tkeo;
    }
    else if (algoMode == ALGO_MODE_F_TKEO)
    {
        tmpCh1 = ch1_f_tkeo;
        tmpCh2 = ch2_f_tkeo;
        tmpCh3 = ch3_f_tkeo;
        tmpCh4 = ch4_f_tkeo;
    }
    else if (algoMode == ALGO_MODE_P3_F_TKEO)
    {
        tmpCh1 = ch1_p3_f_tkeo;
        tmpCh2 = ch2_p3_f_tkeo;
        tmpCh3 = ch3_p3_f_tkeo;
        tmpCh4 = ch4_p3_f_tkeo;
    }

    // ofstream myfile(GB_IMPULSE_DIRECTORY + "/" + algoType + ".txt");
    ofstream myfile(GB_IMPULSE_DIRECTORY + "/data_" + participantName + std::to_string(trialNumber) + "_C" + std::to_string(numberOfChannelesUsedForTraining) + "_" + algoType + ".txt");

    for (int i = 2; i < ch1_tkeo.size(); i++)
    {
        sample1.clear();
        sample2.clear();
        sample3.clear();
        threeSamples.clear();

        sample1.push_back(tmpCh1.at(i - 2));
        sample1.push_back(tmpCh2.at(i - 2));
        sample1.push_back(tmpCh3.at(i - 2));
        sample1.push_back(tmpCh4.at(i - 2));

        sample2.push_back(tmpCh1.at(i - 1));
        sample2.push_back(tmpCh2.at(i - 1));
        sample2.push_back(tmpCh3.at(i - 1));
        sample2.push_back(tmpCh4.at(i - 1));

        sample3.push_back(tmpCh1.at(i));
        sample3.push_back(tmpCh2.at(i));
        sample3.push_back(tmpCh3.at(i));
        sample3.push_back(tmpCh4.at(i));

        threeSamples.push_back(sample1);
        threeSamples.push_back(sample2);
        threeSamples.push_back(sample3);

        clickType = predictCLickTypeFromThreeSamples(threeSamples, false);

        if (clickType == "left")
        {
            if (i > nextLeftClickCheckAfterSampleNumber && trainingDataLeftClick.at(i) != 1)
            {
                myfile << trainingDataChannel1.at(i) << " " << trainingDataChannel2.at(i) << " " << trainingDataChannel3.at(i)
                       << " " << trainingDataChannel4.at(i) << " " << trainingDataLeftClick.at(i) << " " << trainingDataRightClick.at(i)
                       << " " << trainingDataThumbClick.at(i) << " 1 0 0" << endl;
                nextLeftClickCheckAfterSampleNumber = ((int)((GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD * GB_NEXT_SAMPLE_CHECK_AFTER_TRUE_POSITIVE) / 1000)) + i;
                lead = getClickLead(i, trainingDataLeftClick);
                if (lead == -1)
                {
                    falsePositivesLeftClickIndex.push_back(i);
                }
                else
                {
                    truePositivesLeftClickLead.push_back(lead);
                    truePositivesLeftClickIndex.push_back(i);
                }
            }
            else
            {
                myfile << trainingDataChannel1.at(i) << " " << trainingDataChannel2.at(i) << " " << trainingDataChannel3.at(i)
                       << " " << trainingDataChannel4.at(i) << " " << trainingDataLeftClick.at(i) << " " << trainingDataRightClick.at(i)
                       << " " << trainingDataThumbClick.at(i) << " 0 0 0" << endl;
            }
        }
        else if (clickType == "right")
        {

            if (i > nextRightClickCheckAfterSampleNumber && trainingDataRightClick.at(i) != 1)
            {
                myfile << trainingDataChannel1.at(i) << " " << trainingDataChannel2.at(i) << " " << trainingDataChannel3.at(i)
                       << " " << trainingDataChannel4.at(i) << " " << trainingDataLeftClick.at(i) << " " << trainingDataRightClick.at(i)
                       << " " << trainingDataThumbClick.at(i) << " 0 1 0" << endl;
                nextRightClickCheckAfterSampleNumber = ((int)((GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD * GB_NEXT_SAMPLE_CHECK_AFTER_TRUE_POSITIVE) / 1000)) + i;
                lead = getClickLead(i, trainingDataRightClick);
                if (lead == -1)
                {
                    falsePositivesRightClickIndex.push_back(i);
                }
                else
                {
                    truePositivesRightClickLead.push_back(lead);
                    truePositivesRightClickIndex.push_back(i);
                }
            }
            else
            {
                myfile << trainingDataChannel1.at(i) << " " << trainingDataChannel2.at(i) << " " << trainingDataChannel3.at(i)
                       << " " << trainingDataChannel4.at(i) << " " << trainingDataLeftClick.at(i) << " " << trainingDataRightClick.at(i)
                       << " " << trainingDataThumbClick.at(i) << " 0 0 0" << endl;
            }
        }
        else if (clickType == "thumb")
        {

            if (i > nextThumbClickCheckAfterSampleNumber)
            {
                myfile << trainingDataChannel1.at(i) << " " << trainingDataChannel2.at(i) << " " << trainingDataChannel3.at(i)
                       << " " << trainingDataChannel4.at(i) << " " << trainingDataLeftClick.at(i) << " " << trainingDataRightClick.at(i)
                       << " " << trainingDataThumbClick.at(i) << " 0 0 1" << endl;
                nextThumbClickCheckAfterSampleNumber = ((int)((GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD * GB_NEXT_SAMPLE_CHECK_AFTER_TRUE_POSITIVE) / 1000)) + i;
                lead = getClickLead(i, trainingDataThumbClick);
                if (lead == -1)
                {
                    falsePositivesThumbClickIndex.push_back(i);
                }
                else
                {
                    truePositivesThumbClickLead.push_back(lead);
                    truePositivesThumbClickIndex.push_back(i);
                }
            }
            else
            {
                myfile << trainingDataChannel1.at(i) << " " << trainingDataChannel2.at(i) << " " << trainingDataChannel3.at(i)
                       << " " << trainingDataChannel4.at(i) << " " << trainingDataLeftClick.at(i) << " " << trainingDataRightClick.at(i)
                       << " " << trainingDataThumbClick.at(i) << " 0 0 0" << endl;
            }
        }
        else if (clickType == "none")
        {
            myfile << trainingDataChannel1.at(i) << " " << trainingDataChannel2.at(i) << " " << trainingDataChannel3.at(i)
                   << " " << trainingDataChannel4.at(i) << " " << trainingDataLeftClick.at(i) << " " << trainingDataRightClick.at(i)
                   << " " << trainingDataThumbClick.at(i) << " 0 0 0" << endl;
        }
    }
    myfile.close();
    Json tmp, tmp2;

    tmp["false_positives_indices"] = falsePositivesLeftClickIndex;
    tmp2["lead"] = truePositivesLeftClickLead;
    tmp2["indices"] = truePositivesLeftClickIndex;
    tmp["true_positives"] = tmp2;
    info["left_click"] = tmp;

    tmp["false_positives_indices"] = falsePositivesRightClickIndex;
    tmp2["lead"] = truePositivesRightClickLead;
    tmp2["indices"] = truePositivesRightClickIndex;
    tmp["true_positives"] = tmp2;
    info["right_click"] = tmp;

    return info.dump();
}




std::vector<int> MyAlgo::getActualClickIndices(std::vector<int> clickData)
{
    std::vector<int> tmp;
    int flag = 1;
    for (int i = 0; i < clickData.size(); i++)
    {
        if (clickData.at(i) == 1)
        {
            if (flag == 1)
            {
                tmp.push_back(i);
                flag = 0;
            }
        }
        else
        {
            flag = 1;
        }
    }
    return tmp;
}

int MyAlgo::getClickLead(int loc, std::vector<int> clickArray)
{
    int i = loc;
    int clickStartingIndex = ((int)((GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD * TRUE_POSTIVE_MILLISECONDS_CHECK) / 1000)) + loc;

    while (i < clickArray.size() && i < clickStartingIndex)
    {
        if (clickArray.at(i) == 1)
        {
            return (int)((i - loc) / 2);
        }
        i++;
    }
    return -1;
}

string MyAlgo::predictCLickTypeFromThreeSamples(std::vector<std::vector<double>> threeSamples, bool fireClicks)
{
    string finalClickType = "none";
    string clickType1 = predictCLickTypeFromOneSample(threeSamples.at(0));
    string clickType2 = predictCLickTypeFromOneSample(threeSamples.at(1));
    string clickType3 = predictCLickTypeFromOneSample(threeSamples.at(2));

    if (clickType1 == clickType2)
    {
        finalClickType = clickType1;
    }
    else if (clickType2 == clickType3)
    {
        finalClickType = clickType2;
    }
    else if (clickType3 == clickType1)
    {
        finalClickType = clickType3;
    }
    
    if (fireClicks)
    {
        if (finalClickType == "left")
        {
            MouseFunctions::Instance().fireMouseEvent('l', 'd');
        }
        else if (finalClickType == "right")
        {
            MouseFunctions::Instance().fireMouseEvent('r', 'd');
        }
    }

    return finalClickType;
}

string MyAlgo::predictCLickTypeFromOneSample(std::vector<double> sample)
{
    if (sample.at(0) >= globalChannelNoise[0] || sample.at(1) >= globalChannelNoise[1] || sample.at(2) >= globalChannelNoise[2] || sample.at(3) >= globalChannelNoise[3])
    {
        double leftClickDistance = getDistance(sample, meanLeftClick, covMatrixLeftClick);
        double rightClickDistance = getDistance(sample, meanRightClick, covMatrixRightClick);
        double thumbClickDistance = getDistance(sample, meanThumbClick, covMatrixThumbClick);

        if (leftClickDistance <= rightClickDistance && leftClickDistance <= thumbClickDistance)
        {
            return "left";
        }
        else if (rightClickDistance <= leftClickDistance && rightClickDistance <= thumbClickDistance)
        {
            return "right";
        }
        else if (thumbClickDistance <= rightClickDistance && thumbClickDistance <= leftClickDistance)
        {
            return "thumb";
        }
    }
    return "none";
}

double MyAlgo::getDistance(std::vector<double> sample, std::vector<double> mean, std::vector<std::vector<double>> cov)
{
    double distance;
    matrix<double> M = dlib::mat(mean);
    matrix<double> S = dlib::mat(sample);
    matrix<double> COV;
    COV.set_size(cov.size(), cov.at(0).size());
    for (unsigned i = 0; i < cov.size(); i++)
    {
        for (unsigned j = 0; j < cov[i].size(); j++)
        {
            COV(i, j) = cov[i][j];
        }
    }
    matrix<double> term1 = trans(M - S);
    matrix<double> term2 = pinv(COV);
    matrix<double> term3 = M - S;
    distance = term1 * (term2 * term3);
    return distance;
}


#endif