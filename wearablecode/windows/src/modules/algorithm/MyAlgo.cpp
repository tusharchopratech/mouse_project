#ifndef MyAlgo_CPP
#define MyAlgo_CPP
#include "MyAlgo.hpp"

string MyAlgo::getAlgoResults(string pName, int noCh, int trialNo)
{
    participantName = pName;
    trialNumber = trialNo;
    numberOfChannelesUsedForTraining = noCh;
    readData();
    processData();
    string result = predictAndWriteResults();
    return result;
}

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

    if (gb_getCurrentEnvirnoment() == GB_ENV_DEVELOPMENT)
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

    if (gb_getCurrentEnvirnoment() == GB_ENV_DEVELOPMENT)
    {
        cout << "For p3_tkeo_sign_both" << endl;
        cout << "Left click TP/Actual Clicks : " << (double)((double)leftTotalTruePositives / (double)leftClickIndices.size()) << endl;
        cout << "Right click TP/Actual Clicks : " << (double)((double)rightTotalTruePositives / (double)rightClickIndices.size()) << endl;
        cout << "Left click FP/Actual Clicks : " << (double)((double)bestAlgoModeJson["left_click"]["false_positives_indices"].size() / (double)leftClickIndices.size()) << endl;
        cout << "Right click FP/Actual Clicks : " << (double)((double)bestAlgoModeJson["right_click"]["false_positives_indices"].size() / (double)rightClickIndices.size()) << endl
             << endl;
    }

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

    if (gb_getCurrentEnvirnoment() == GB_ENV_DEVELOPMENT)
    {
        cout << "For tkeo_sign_both" << endl;
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

    if (gb_getCurrentEnvirnoment() == GB_ENV_DEVELOPMENT)
    {
        cout << "For p3_f_tkeo_sign_both" << endl;
        cout << "Left click TP/Actual Clicks : " << (double)((double)leftTotalTruePositives / (double)leftClickIndices.size()) << endl;
        cout << "Right click TP/Actual Clicks : " << (double)((double)rightTotalTruePositives / (double)rightClickIndices.size()) << endl;
        cout << "Left click FP/Actual Clicks : " << (double)((double)bestAlgoModeJson["left_click"]["false_positives_indices"].size() / (double)leftClickIndices.size()) << endl;
        cout << "Right click FP/Actual Clicks : " << (double)((double)bestAlgoModeJson["right_click"]["false_positives_indices"].size() / (double)rightClickIndices.size()) << endl
             << endl;
    }

    finalJson["results"] = tmp;

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
    ofstream myfile(GB_IMPULSE_DIRECTORY + "/" + participantName + "_xxx_" + std::to_string(numberOfChannelesUsedForTraining) + "_channels_xxx_" + std::to_string(trialNumber) + "_xxx_" + algoType + ".txt");

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
            if (i > nextLeftClickCheckAfterSampleNumber)
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

            if (i > nextRightClickCheckAfterSampleNumber)
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
    int next150MsSampleIndex = ((int)((GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD * TRUE_POSTIVE_MILLISECONDS_CHECK) / 1000)) + loc;

    while (i < clickArray.size() && i < next150MsSampleIndex)
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

    // if (clickType1 == clickType2 && clickType1 == clickType3 && clickType2 == clickType3)
    // {
    //     finalClickType = clickType1;
    // }

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

void MyAlgo::computeFeatures(int algoMode, int signFlag)
{
    double mean1, mean2, mean3, mean4;
    // Left Click
    std::vector<std::vector<double>> leftCLickFeatures;
    getFeaturesForClickType(l_c, algoMode, signFlag, leftCLickFeatures);
    mean1 = std::accumulate(leftCLickFeatures[0].begin(), leftCLickFeatures[0].end(), 0.0) / leftCLickFeatures[0].size();
    mean2 = std::accumulate(leftCLickFeatures[1].begin(), leftCLickFeatures[1].end(), 0.0) / leftCLickFeatures[1].size();
    mean3 = std::accumulate(leftCLickFeatures[2].begin(), leftCLickFeatures[2].end(), 0.0) / leftCLickFeatures[2].size();
    mean4 = std::accumulate(leftCLickFeatures[3].begin(), leftCLickFeatures[3].end(), 0.0) / leftCLickFeatures[3].size();
    meanLeftClick.push_back(mean1);
    meanLeftClick.push_back(mean2);
    meanLeftClick.push_back(mean3);
    meanLeftClick.push_back(mean4);

    computeCovarianceMatrix(leftCLickFeatures, covMatrixLeftClick);

    // Right Click Features
    std::vector<std::vector<double>> rightCLickFeatures;
    getFeaturesForClickType(r_c, algoMode, signFlag, rightCLickFeatures);
    mean1 = std::accumulate(rightCLickFeatures[0].begin(), rightCLickFeatures[0].end(), 0.0) / rightCLickFeatures[0].size();
    mean2 = std::accumulate(rightCLickFeatures[1].begin(), rightCLickFeatures[1].end(), 0.0) / rightCLickFeatures[1].size();
    mean3 = std::accumulate(rightCLickFeatures[2].begin(), rightCLickFeatures[2].end(), 0.0) / rightCLickFeatures[2].size();
    mean4 = std::accumulate(rightCLickFeatures[3].begin(), rightCLickFeatures[3].end(), 0.0) / rightCLickFeatures[3].size();
    meanRightClick.push_back(mean1);
    meanRightClick.push_back(mean2);
    meanRightClick.push_back(mean3);
    meanRightClick.push_back(mean4);
    computeCovarianceMatrix(rightCLickFeatures, covMatrixRightClick);

    // Thumb Click Features
    std::vector<std::vector<double>> thumbCLickFeatures;
    getFeaturesForClickType(t_c, algoMode, signFlag, thumbCLickFeatures);
    mean1 = std::accumulate(thumbCLickFeatures[0].begin(), thumbCLickFeatures[0].end(), 0.0) / thumbCLickFeatures[0].size();
    mean2 = std::accumulate(thumbCLickFeatures[1].begin(), thumbCLickFeatures[1].end(), 0.0) / thumbCLickFeatures[1].size();
    mean3 = std::accumulate(thumbCLickFeatures[2].begin(), thumbCLickFeatures[2].end(), 0.0) / thumbCLickFeatures[2].size();
    mean4 = std::accumulate(thumbCLickFeatures[3].begin(), thumbCLickFeatures[3].end(), 0.0) / thumbCLickFeatures[3].size();
    meanThumbClick.push_back(mean1);
    meanThumbClick.push_back(mean2);
    meanThumbClick.push_back(mean3);
    meanThumbClick.push_back(mean4);
    computeCovarianceMatrix(thumbCLickFeatures, covMatrixThumbClick);
}

void MyAlgo::getFeaturesForClickType(std::vector<int> clickArray, int algoMode, int signFlag, std::vector<std::vector<double>> &featureVector)
{
    std::vector<double> featureCh1, featureCh2, featureCh3, featureCh4;
    std::vector<double> ch1, ch2, ch3, ch4;
    if (algoMode == ALGO_MODE_RAW)
    {
        ch1 = ch1_raw;
        ch2 = ch2_raw;
        ch3 = ch3_raw;
        ch4 = ch4_raw;
    }
    else if (algoMode == ALGO_MODE_TKEO)
    {
        ch1 = ch1_tkeo;
        ch2 = ch2_tkeo;
        ch3 = ch3_tkeo;
        ch4 = ch4_tkeo;
    }
    else if (algoMode == ALGO_MODE_P3_TKEO)
    {
        ch1 = ch1_p3_tkeo;
        ch2 = ch2_p3_tkeo;
        ch3 = ch3_p3_tkeo;
        ch4 = ch4_p3_tkeo;
    }
    else if (algoMode == ALGO_MODE_F_TKEO)
    {
        ch1 = ch1_f_tkeo;
        ch2 = ch2_f_tkeo;
        ch3 = ch3_f_tkeo;
        ch4 = ch4_f_tkeo;
    }
    else if (algoMode == ALGO_MODE_P3_F_TKEO)
    {
        ch1 = ch1_p3_f_tkeo;
        ch2 = ch2_p3_f_tkeo;
        ch3 = ch3_p3_f_tkeo;
        ch4 = ch4_p3_f_tkeo;
    }
    int previousValue = 0;
    for (int i = 0; i < clickArray.size(); i++)
    {
        if (i > trainingWindowStartPointForFeatureConstruction && clickArray.at(i) == 1 && previousValue == 0)
        {
            std::vector<double> tmpCh1, tmpCh2, tmpCh3, tmpCh4;
            for (int j = i - trainingWindowStartPointForFeatureConstruction; j < i; j++)
            {
                // Considering Positive Phase
                if (signFlag == ALGO_SIGN_FLAG_POS)
                {
                    if (ch1.at(j) < 0.0)
                    {
                        ch1.at(j) = 0.0;
                    }
                    if (ch2.at(j) < 0.0)
                    {
                        ch2.at(j) = 0.0;
                    }
                    if (ch3.at(j) < 0.0)
                    {
                        ch3.at(j) = 0.0;
                    }
                    if (ch4.at(j) < 0.0)
                    {
                        ch4.at(j) = 0.0;
                    }
                }
                // Considering Negative Phase
                else if (signFlag == ALGO_SIGN_FLAG_NEG)
                {
                    if (ch1.at(j) > 0.0)
                    {
                        ch1.at(j) = 0.0;
                    }
                    if (ch2.at(j) > 0.0)
                    {
                        ch2.at(j) = 0.0;
                    }
                    if (ch3.at(j) > 0.0)
                    {
                        ch3.at(j) = 0.0;
                    }
                    if (ch4.at(j) > 0.0)
                    {
                        ch4.at(j) = 0.0;
                    }
                }
                // Considering Both
                else if (signFlag == ALGO_SIGN_FLAG_BOTH)
                {
                    ch1.at(j) = abs(ch1.at(j));
                    ch2.at(j) = abs(ch2.at(j));
                    ch3.at(j) = abs(ch3.at(j));
                    ch4.at(j) = abs(ch4.at(j));
                }

                if (ch1.at(j) > globalChannelNoise[0])
                {
                    tmpCh1.push_back(ch1.at(j));
                }
                if (ch2.at(j) > globalChannelNoise[1])
                {
                    tmpCh2.push_back(ch2.at(j));
                }
                if (ch3.at(j) > globalChannelNoise[2])
                {
                    tmpCh4.push_back(ch3.at(j));
                }
                if (ch4.at(j) > globalChannelNoise[3])
                {
                    tmpCh4.push_back(ch4.at(j));
                }
            }
            featureCh1.push_back(vectorMedian(tmpCh1));
            featureCh2.push_back(vectorMedian(tmpCh2));
            featureCh3.push_back(vectorMedian(tmpCh3));
            featureCh4.push_back(vectorMedian(tmpCh4));
        }
        previousValue = clickArray.at(i);
    }
    featureVector.push_back(featureCh1);
    featureVector.push_back(featureCh2);
    featureVector.push_back(featureCh3);
    featureVector.push_back(featureCh4);
}

void MyAlgo::computeGlobalNoice(int algoMode, int signFlag)
{
    double leftClickEachChannelMaxValue[] = {-5.0, -5.0, -5.0, -5.0};
    double rightClickEachChannelMaxValue[] = {-5.0, -5.0, -5.0, -5.0};
    double thumbClickEachChannelMaxValue[] = {-5.0, -5.0, -5.0, -5.0};
    getEachChannelMaxValueForClickType(l_c, algoMode, signFlag, leftClickEachChannelMaxValue);  // Left Click
    getEachChannelMaxValueForClickType(r_c, algoMode, signFlag, rightClickEachChannelMaxValue); // Right Click
    getEachChannelMaxValueForClickType(t_c, algoMode, signFlag, thumbClickEachChannelMaxValue); // Thumb Click
    for (int i = 0; i < 4; i++)
    {
        globalChannelNoise[i] = minOfThree(leftClickEachChannelMaxValue[i], rightClickEachChannelMaxValue[i], thumbClickEachChannelMaxValue[i]);
        // cout << globalChannelNoise[i] << " ";
    }
    cout << endl;
}

double MyAlgo::minOfThree(double x, double y, double z)
{
    return x < y ? (x < z ? x : z) : (y < z ? y : z);
}

void MyAlgo::getEachChannelMaxValueForClickType(std::vector<int> clickArray, int algoMode, int signFlag, double (&eachChannelMaxSample)[4])
{

    std::vector<double> ch1, ch2, ch3, ch4;
    if (algoMode == ALGO_MODE_RAW)
    {
        ch1 = ch1_raw;
        ch2 = ch2_raw;
        ch3 = ch3_raw;
        ch4 = ch4_raw;
    }
    else if (algoMode == ALGO_MODE_TKEO)
    {
        ch1 = ch1_tkeo;
        ch2 = ch2_tkeo;
        ch3 = ch3_tkeo;
        ch4 = ch4_tkeo;
    }
    else if (algoMode == ALGO_MODE_P3_TKEO)
    {
        ch1 = ch1_p3_tkeo;
        ch2 = ch2_p3_tkeo;
        ch3 = ch3_p3_tkeo;
        ch4 = ch4_p3_tkeo;
    }
    else if (algoMode == ALGO_MODE_F_TKEO)
    {
        ch1 = ch1_f_tkeo;
        ch2 = ch2_f_tkeo;
        ch3 = ch3_f_tkeo;
        ch4 = ch4_f_tkeo;
    }
    else if (algoMode == ALGO_MODE_P3_F_TKEO)
    {
        ch1 = ch1_p3_f_tkeo;
        ch2 = ch2_p3_f_tkeo;
        ch3 = ch3_p3_f_tkeo;
        ch4 = ch4_p3_f_tkeo;
    }

    int previousValue = 0;
    for (int i = 0; i < ch1_raw.size(); i++)
    {
        if (i > trainingWindowStartPointForNoise && clickArray.at(i) == 1 && previousValue == 0)
        {
            for (int j = i - trainingWindowStartPointForNoise; j < i - trainingWindowEndPointForNoise; j++)
            {
                // Considering Positive Phase
                if (signFlag == ALGO_SIGN_FLAG_POS)
                {
                    if (ch1.at(j) < 0.0)
                    {
                        ch1.at(j) = 0.0;
                    }
                    if (ch2.at(j) < 0.0)
                    {
                        ch2.at(j) = 0.0;
                    }
                    if (ch3.at(j) < 0.0)
                    {
                        ch3.at(j) = 0.0;
                    }
                    if (ch4.at(j) < 0.0)
                    {
                        ch4.at(j) = 0.0;
                    }
                }
                // Considering Negative Phase
                else if (signFlag == ALGO_SIGN_FLAG_NEG)
                {
                    if (ch1.at(j) > 0.0)
                    {
                        ch1.at(j) = 0.0;
                    }
                    if (ch2.at(j) > 0.0)
                    {
                        ch2.at(j) = 0.0;
                    }
                    if (ch3.at(j) > 0.0)
                    {
                        ch3.at(j) = 0.0;
                    }
                    if (ch4.at(j) > 0.0)
                    {
                        ch4.at(j) = 0.0;
                    }
                }
                // Considering Both
                else if (signFlag == ALGO_SIGN_FLAG_BOTH)
                {
                    ch1.at(j) = abs(ch1.at(j));
                    ch2.at(j) = abs(ch2.at(j));
                    ch3.at(j) = abs(ch3.at(j));
                    ch4.at(j) = abs(ch4.at(j));
                }

                //Getthing MAX value among all windows in each channel
                if (ch1.at(j) > eachChannelMaxSample[0])
                {
                    eachChannelMaxSample[0] = ch1.at(j);
                }

                if (ch2.at(j) > eachChannelMaxSample[1])
                {
                    eachChannelMaxSample[1] = ch2.at(j);
                }

                if (ch3.at(j) > eachChannelMaxSample[2])
                {
                    eachChannelMaxSample[2] = ch3.at(j);
                }

                if (ch4.at(j) > eachChannelMaxSample[3])
                {
                    eachChannelMaxSample[3] = ch4.at(j);
                }
            }
        }
        previousValue = clickArray.at(i);
    }
}

double MyAlgo::getTkeoValue(double v1, double v2, double v3)
{
    v1 = v1 * v1 * v1;
    v2 = v2 * v2 * v2;
    v3 = v3 * v3 * v3;
    double result = ((v2 * v2) - (v1 * v3));
    return result;
}

void MyAlgo::processData()
{
    ch1_raw.clear();
    ch2_raw.clear();
    ch3_raw.clear();
    ch4_raw.clear();

    ch1_tkeo.clear();
    ch2_tkeo.clear();
    ch3_tkeo.clear();
    ch4_tkeo.clear();

    ch1_p3_tkeo.clear();
    ch2_p3_tkeo.clear();
    ch3_p3_tkeo.clear();
    ch4_p3_tkeo.clear();

    ch1_p3_f_tkeo.clear();
    ch2_p3_f_tkeo.clear();
    ch3_p3_f_tkeo.clear();
    ch4_p3_f_tkeo.clear();

    ch1_f_tkeo.clear();
    ch2_f_tkeo.clear();
    ch3_f_tkeo.clear();
    ch4_f_tkeo.clear();

    filterTools.resetFilters();
    for (int i = 2; i < trainingDataChannel1.size(); i++)
    {
        ch1_raw.push_back(trainingDataChannel1.at(i));
        ch2_raw.push_back(trainingDataChannel2.at(i));
        ch3_raw.push_back(trainingDataChannel3.at(i));
        ch4_raw.push_back(trainingDataChannel4.at(i));
        l_c.push_back(trainingDataLeftClick.at(i));
        r_c.push_back(trainingDataRightClick.at(i));
        t_c.push_back(trainingDataThumbClick.at(i));
    }

    filterTools.resetFilters();
    for (int i = 2; i < trainingDataChannel1.size(); i++)
    {
        ch1_tkeo.push_back(getTkeoValue(trainingDataChannel1.at(i - 2), trainingDataChannel1.at(i - 1), trainingDataChannel1.at(i)));
        ch2_tkeo.push_back(getTkeoValue(trainingDataChannel2.at(i - 2), trainingDataChannel2.at(i - 1), trainingDataChannel2.at(i)));
        ch3_tkeo.push_back(getTkeoValue(trainingDataChannel3.at(i - 2), trainingDataChannel3.at(i - 1), trainingDataChannel3.at(i)));
        ch4_tkeo.push_back(getTkeoValue(trainingDataChannel4.at(i - 2), trainingDataChannel4.at(i - 1), trainingDataChannel4.at(i)));
    }

    filterTools.resetFilters();
    for (int i = 2; i < trainingDataChannel1.size(); i++)
    {
        ch1_p3_f_tkeo.push_back(getTkeoValue(filterTools.getFilteredValue(1, pow(trainingDataChannel1.at(i - 2), 3)), filterTools.getFilteredValue(1, pow(trainingDataChannel1.at(i - 1), 3)), filterTools.getFilteredValue(1, pow(trainingDataChannel1.at(i), 3))));
        ch2_p3_f_tkeo.push_back(getTkeoValue(filterTools.getFilteredValue(2, pow(trainingDataChannel2.at(i - 2), 3)), filterTools.getFilteredValue(2, pow(trainingDataChannel2.at(i - 1), 3)), filterTools.getFilteredValue(2, pow(trainingDataChannel2.at(i), 3))));
        ch3_p3_f_tkeo.push_back(getTkeoValue(filterTools.getFilteredValue(3, pow(trainingDataChannel3.at(i - 2), 3)), filterTools.getFilteredValue(3, pow(trainingDataChannel3.at(i - 1), 3)), filterTools.getFilteredValue(3, pow(trainingDataChannel3.at(i), 3))));
        ch4_p3_f_tkeo.push_back(getTkeoValue(filterTools.getFilteredValue(4, pow(trainingDataChannel4.at(i - 2), 3)), filterTools.getFilteredValue(4, pow(trainingDataChannel4.at(i - 1), 3)), filterTools.getFilteredValue(4, pow(trainingDataChannel4.at(i), 3))));
    }

    filterTools.resetFilters();
    for (int i = 2; i < trainingDataChannel1.size(); i++)
    {
        ch1_p3_tkeo.push_back(getTkeoValue(pow(trainingDataChannel1.at(i - 2), 3), pow(trainingDataChannel1.at(i - 1), 3), pow(trainingDataChannel1.at(i), 3)));
        ch2_p3_tkeo.push_back(getTkeoValue(pow(trainingDataChannel2.at(i - 2), 3), pow(trainingDataChannel2.at(i - 1), 3), pow(trainingDataChannel2.at(i), 3)));
        ch3_p3_tkeo.push_back(getTkeoValue(pow(trainingDataChannel3.at(i - 2), 3), pow(trainingDataChannel3.at(i - 1), 3), pow(trainingDataChannel3.at(i), 3)));
        ch4_p3_tkeo.push_back(getTkeoValue(pow(trainingDataChannel4.at(i - 2), 3), pow(trainingDataChannel4.at(i - 1), 3), pow(trainingDataChannel4.at(i), 3)));
    }

    filterTools.resetFilters();
    for (int i = 2; i < trainingDataChannel1.size(); i++)
    {
        ch1_f_tkeo.push_back(getTkeoValue(filterTools.getFilteredValue(1, trainingDataChannel1.at(i - 2)), filterTools.getFilteredValue(1, trainingDataChannel1.at(i - 1)), filterTools.getFilteredValue(1, trainingDataChannel1.at(i))));
        ch2_f_tkeo.push_back(getTkeoValue(filterTools.getFilteredValue(2, trainingDataChannel2.at(i - 2)), filterTools.getFilteredValue(2, trainingDataChannel2.at(i - 1)), filterTools.getFilteredValue(2, trainingDataChannel2.at(i))));
        ch3_f_tkeo.push_back(getTkeoValue(filterTools.getFilteredValue(3, trainingDataChannel3.at(i - 2)), filterTools.getFilteredValue(3, trainingDataChannel3.at(i - 1)), filterTools.getFilteredValue(3, trainingDataChannel3.at(i))));
        ch4_f_tkeo.push_back(getTkeoValue(filterTools.getFilteredValue(4, trainingDataChannel4.at(i - 2)), filterTools.getFilteredValue(4, trainingDataChannel4.at(i - 1)), filterTools.getFilteredValue(4, trainingDataChannel4.at(i))));
    }
    filterTools.resetFilters();
}

void MyAlgo::readData()
{
    trainingDataChannel1.clear();
    trainingDataChannel2.clear();
    trainingDataChannel3.clear();
    trainingDataChannel4.clear();
    trainingDataLeftClick.clear();
    trainingDataRightClick.clear();
    trainingDataThumbClick.clear();

    string file = GB_IMPULSE_DIRECTORY + "/" + participantName + "_xxx_" + std::to_string(numberOfChannelesUsedForTraining) + "_channels_xxx_" + std::to_string(trialNumber) + "_xxx_" + "data.txt";

    std::string line;
    std::ifstream infile(file);
    if (infile.fail())
    {
        cout << "Unable to open file : " << file << endl;
    }
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
                trainingDataChannel1.push_back(std::stod(token));
            }
            else if (i == 1)
            {
                trainingDataChannel2.push_back(std::stod(token));
            }
            else if (i == 2)
            {
                trainingDataChannel3.push_back(std::stod(token));
            }
            else if (i == 3)
            {
                trainingDataChannel4.push_back(std::stod(token));
            }
            else if (i == 4)
            {
                trainingDataLeftClick.push_back(std::stoi(token));
            }
            else if (i == 5)
            {
                trainingDataRightClick.push_back(std::stoi(token));
            }
            i++;
        }

        trainingDataThumbClick.push_back(std::stoi(s));
    }

    std::vector<double> tmp;
    tmp = trainingDataChannel3;
    trainingDataChannel3 = trainingDataChannel4;
    trainingDataChannel4 = tmp;
}

void MyAlgo::fireImpulseClicks(std::vector<double> ch1, std::vector<double> ch2, std::vector<double> ch3, std::vector<double> ch4)
{
    int i = 0;
    std::vector<double> sample;

    if (prevSampleRealTime.size() == 0 && prevPrevSampleRealTime.size() == 0)
    {
        filterTools.resetFilters();
        prevPrevSampleRealTime.push_back(ch1.at(0));
        prevPrevSampleRealTime.push_back(ch2.at(0));
        prevPrevSampleRealTime.push_back(ch3.at(0));
        prevPrevSampleRealTime.push_back(ch4.at(0));
        prevSampleRealTime.push_back(ch1.at(1));
        prevSampleRealTime.push_back(ch2.at(1));
        prevSampleRealTime.push_back(ch3.at(1));
        prevSampleRealTime.push_back(ch4.at(1));
        threeSamplesRealTime.push_back(prevPrevSampleRealTime);
        threeSamplesRealTime.push_back(prevSampleRealTime);
        i = 2;
    }

    for (i = i; i < ch1.size(); i++)
    {
        sample.clear();
        if (bestAlgoModeLC == ALGO_MODE_TKEO)
        {
            sample.push_back(getTkeoValue(prevPrevSampleRealTime.at(0), prevSampleRealTime.at(0), ch1.at(i)));
            sample.push_back(getTkeoValue(prevPrevSampleRealTime.at(1), prevSampleRealTime.at(1), ch2.at(i)));
            sample.push_back(getTkeoValue(prevPrevSampleRealTime.at(2), prevSampleRealTime.at(2), ch3.at(i)));
            sample.push_back(getTkeoValue(prevPrevSampleRealTime.at(3), prevSampleRealTime.at(3), ch4.at(i)));
        }
        else if (bestAlgoModeLC == ALGO_MODE_F_TKEO)
        {
            sample.push_back(getTkeoValue(filterTools.getFilteredValue(1, prevPrevSampleRealTime.at(0)), filterTools.getFilteredValue(1, prevSampleRealTime.at(0)), filterTools.getFilteredValue(1, ch1.at(i))));
            sample.push_back(getTkeoValue(filterTools.getFilteredValue(2, prevPrevSampleRealTime.at(1)), filterTools.getFilteredValue(2, prevSampleRealTime.at(1)), filterTools.getFilteredValue(2, ch2.at(i))));
            sample.push_back(getTkeoValue(filterTools.getFilteredValue(3, prevPrevSampleRealTime.at(2)), filterTools.getFilteredValue(3, prevSampleRealTime.at(2)), filterTools.getFilteredValue(3, ch3.at(i))));
            sample.push_back(getTkeoValue(filterTools.getFilteredValue(4, prevPrevSampleRealTime.at(3)), filterTools.getFilteredValue(4, prevSampleRealTime.at(3)), filterTools.getFilteredValue(4, ch4.at(i))));
        }
        else if (bestAlgoModeLC == ALGO_MODE_P3_F_TKEO)
        {
            sample.push_back(getTkeoValue(filterTools.getFilteredValue(1, pow(prevPrevSampleRealTime.at(0), 3)), filterTools.getFilteredValue(1, pow(prevSampleRealTime.at(0), 3)), filterTools.getFilteredValue(1, pow(ch1.at(i), 3))));
            sample.push_back(getTkeoValue(filterTools.getFilteredValue(2, pow(prevPrevSampleRealTime.at(1), 3)), filterTools.getFilteredValue(2, pow(prevSampleRealTime.at(1), 3)), filterTools.getFilteredValue(2, pow(ch2.at(i), 3))));
            sample.push_back(getTkeoValue(filterTools.getFilteredValue(3, pow(prevPrevSampleRealTime.at(2), 3)), filterTools.getFilteredValue(3, pow(prevSampleRealTime.at(2), 3)), filterTools.getFilteredValue(3, pow(ch3.at(i), 3))));
            sample.push_back(getTkeoValue(filterTools.getFilteredValue(4, pow(prevPrevSampleRealTime.at(3), 3)), filterTools.getFilteredValue(4, pow(prevSampleRealTime.at(3), 3)), filterTools.getFilteredValue(4, pow(ch4.at(i), 3))));
        }
        else if (bestAlgoModeLC == ALGO_MODE_P3_TKEO)
        {
            sample.push_back(getTkeoValue(pow(prevPrevSampleRealTime.at(0), 3), pow(prevSampleRealTime.at(0), 3), pow(ch1.at(i), 3)));
            sample.push_back(getTkeoValue(pow(prevPrevSampleRealTime.at(1), 3), pow(prevSampleRealTime.at(1), 3), pow(ch2.at(i), 3)));
            sample.push_back(getTkeoValue(pow(prevPrevSampleRealTime.at(2), 3), pow(prevSampleRealTime.at(2), 3), pow(ch3.at(i), 3)));
            sample.push_back(getTkeoValue(pow(prevPrevSampleRealTime.at(3), 3), pow(prevSampleRealTime.at(3), 3), pow(ch4.at(i), 3)));
        }
        threeSamplesRealTime.push_back(sample);

        predictCLickTypeFromThreeSamples(threeSamplesRealTime, true);

        threeSamplesRealTime.erase(threeSamplesRealTime.begin());
        prevPrevSampleRealTime = prevSampleRealTime;
        prevSampleRealTime = sample;
    }
}

#endif // !MyAlgo_CPP
