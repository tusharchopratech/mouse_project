#ifndef MyAlgo_CPP
#define MyAlgo_CPP
#include "MyAlgo.hpp"

void MyAlgo::predictAndWriteResults()
{
    computeGlobalNoice(ALGO_MODE_F_TKEO, ALGO_SIGN_FLAG_BOTH);
    computeFeatures(ALGO_MODE_F_TKEO, ALGO_SIGN_FLAG_BOTH);
    predictAndWriteAlgoSpecificResults(ALGO_MODE_F_TKEO, ALGO_SIGN_FLAG_BOTH, "data_result_algo_f_tkeo_sign_both.txt");

    computeGlobalNoice(ALGO_MODE_P3_TKEO, ALGO_SIGN_FLAG_BOTH);
    computeFeatures(ALGO_MODE_P3_TKEO, ALGO_SIGN_FLAG_BOTH);
    predictAndWriteAlgoSpecificResults(ALGO_MODE_P3_TKEO, ALGO_SIGN_FLAG_BOTH, "data_result_algo_p3_tkeo_sign_both.txt");

    computeGlobalNoice(ALGO_MODE_TKEO, ALGO_SIGN_FLAG_BOTH);
    computeFeatures(ALGO_MODE_TKEO, ALGO_SIGN_FLAG_BOTH);
    predictAndWriteAlgoSpecificResults(ALGO_MODE_TKEO, ALGO_SIGN_FLAG_BOTH, "data_result_algo_tkeo_sign_both.txt");

    computeGlobalNoice(ALGO_MODE_P3_F_TKEO, ALGO_SIGN_FLAG_BOTH);
    computeFeatures(ALGO_MODE_P3_F_TKEO, ALGO_SIGN_FLAG_BOTH);
    predictAndWriteAlgoSpecificResults(ALGO_MODE_P3_F_TKEO, ALGO_SIGN_FLAG_BOTH, "data_result_algo_p3_f_tkeo_sign_both.txt");
}

void MyAlgo::predictAndWriteAlgoSpecificResults(int algoMode, int signFlag, string fileName)
{
    totalNumberOfTrainingDataSamples = ch1_tkeo.size();

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

    ofstream myfile(GB_IMPULSE_DIRECTORY + "/" + fileName);
    for (int i = 0; i < totalNumberOfTrainingDataSamples; i++)
    {
        if (i > 1)
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

            clickType = predictCLickTypeFromThreeSamples(threeSamples);
            if (i > 3)
            {
                if (clickType == "left")
                {
                    myfile << trainingDataChannel1.at(i) << " " << trainingDataChannel2.at(i) << " " << trainingDataChannel3.at(i)
                           << " " << trainingDataChannel4.at(i) << " " << trainingDataLeftClick.at(i) << " " << trainingDataRightClick.at(i)
                           << " " << trainingDataThumbClick.at(i) << " 1 0 0" << endl;
                }
                else if (clickType == "right")
                {
                    myfile << trainingDataChannel1.at(i) << " " << trainingDataChannel2.at(i) << " " << trainingDataChannel3.at(i)
                           << " " << trainingDataChannel4.at(i) << " " << trainingDataLeftClick.at(i) << " " << trainingDataRightClick.at(i)
                           << " " << trainingDataThumbClick.at(i) << " 0 1 0" << endl;
                }
                else if (clickType == "thumb")
                {
                    myfile << trainingDataChannel1.at(i) << " " << trainingDataChannel2.at(i) << " " << trainingDataChannel3.at(i)
                           << " " << trainingDataChannel4.at(i) << " " << trainingDataLeftClick.at(i) << " " << trainingDataRightClick.at(i)
                           << " " << trainingDataThumbClick.at(i) << " 0 0 1" << endl;
                }
                else if (clickType == "none")
                {
                    myfile << trainingDataChannel1.at(i) << " " << trainingDataChannel2.at(i) << " " << trainingDataChannel3.at(i)
                           << " " << trainingDataChannel4.at(i) << " " << trainingDataLeftClick.at(i) << " " << trainingDataRightClick.at(i)
                           << " " << trainingDataThumbClick.at(i) << " 0 0 0" << endl;
                }
            }
            else
            {
                myfile << trainingDataChannel1.at(i) << " " << trainingDataChannel2.at(i) << " " << trainingDataChannel3.at(i)
                       << " " << trainingDataChannel4.at(i) << " " << trainingDataLeftClick.at(i) << " " << trainingDataRightClick.at(i)
                       << " " << trainingDataThumbClick.at(i) << " 0 0 0" << endl;
            }
        }
    }
    myfile.close();
}

string MyAlgo::predictCLickTypeFromThreeSamples(std::vector<std::vector<double>> threeSamples)
{
    string clickType1 = predictCLickTypeFromOneSample(threeSamples.at(0));
    string clickType2 = predictCLickTypeFromOneSample(threeSamples.at(1));
    string clickType3 = predictCLickTypeFromOneSample(threeSamples.at(2));
    if (clickType1 == clickType2 && clickType1 == clickType3 && clickType2 == clickType3)
    {
        return clickType1;
    }
    return "none";
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
    getFeaturesForClickType(&l_c[0], algoMode, signFlag, leftCLickFeatures);
    mean1 = std::accumulate(leftCLickFeatures[0].begin(), leftCLickFeatures[0].end(), 0.0) / leftCLickFeatures[0].size();
    mean2 = std::accumulate(leftCLickFeatures[1].begin(), leftCLickFeatures[1].end(), 0.0) / leftCLickFeatures[1].size();
    mean3 = std::accumulate(leftCLickFeatures[2].begin(), leftCLickFeatures[2].end(), 0.0) / leftCLickFeatures[2].size();
    mean4 = std::accumulate(leftCLickFeatures[3].begin(), leftCLickFeatures[3].end(), 0.0) / leftCLickFeatures[3].size();
    meanLeftClick.push_back(mean1);
    meanLeftClick.push_back(mean2);
    meanLeftClick.push_back(mean3);
    meanLeftClick.push_back(mean4);
    // print2DVector(leftCLickFeatures);
    computeCovarianceMatrix(leftCLickFeatures, covMatrixLeftClick);

    // Right Click Features
    std::vector<std::vector<double>> rightCLickFeatures;
    getFeaturesForClickType(&r_c[0], algoMode, signFlag, rightCLickFeatures);
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
    getFeaturesForClickType(&t_c[0], algoMode, signFlag, thumbCLickFeatures);
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

void MyAlgo::getFeaturesForClickType(int *clickArray, int algoMode, int signFlag, std::vector<std::vector<double>> &featureVector)
{
    std::vector<double> featureCh1, featureCh2, featureCh3, featureCh4;
    double *ch1, *ch2, *ch3, *ch4;
    if (algoMode == ALGO_MODE_RAW)
    {
        ch1 = &ch1_raw[0];
        ch2 = &ch2_raw[0];
        ch3 = &ch3_raw[0];
        ch4 = &ch4_raw[0];
    }
    else if (algoMode == ALGO_MODE_TKEO)
    {
        ch1 = &ch1_tkeo[0];
        ch2 = &ch2_tkeo[0];
        ch3 = &ch3_tkeo[0];
        ch4 = &ch4_tkeo[0];
    }
    else if (algoMode == ALGO_MODE_P3_TKEO)
    {
        ch1 = &ch1_p3_tkeo[0];
        ch2 = &ch2_p3_tkeo[0];
        ch3 = &ch3_p3_tkeo[0];
        ch4 = &ch4_p3_tkeo[0];
    }
    else if (algoMode == ALGO_MODE_F_TKEO)
    {
        ch1 = &ch1_f_tkeo[0];
        ch2 = &ch2_f_tkeo[0];
        ch3 = &ch3_f_tkeo[0];
        ch4 = &ch4_f_tkeo[0];
    }
    else if (algoMode == ALGO_MODE_P3_F_TKEO)
    {
        ch1 = &ch1_p3_f_tkeo[0];
        ch2 = &ch2_p3_f_tkeo[0];
        ch3 = &ch3_p3_f_tkeo[0];
        ch4 = &ch4_p3_f_tkeo[0];
    }
    int previousValue = 0;
    for (int i = 0; i < totalNumberOfTrainingDataSamples; i++)
    {
        if (i > trainingWindowStartPointForFeatureConstruction && clickArray[i] == 1 && previousValue == 0)
        {
            std::vector<double> tmpCh1, tmpCh2, tmpCh3, tmpCh4;
            for (int j = i - trainingWindowStartPointForFeatureConstruction; j < i; j++)
            {
                // Considering Positive Phase
                if (signFlag == ALGO_SIGN_FLAG_POS)
                {
                    if (ch1[j] < 0.0)
                    {
                        ch1[j] = 0.0;
                    }
                    if (ch2[j] < 0.0)
                    {
                        ch2[j] = 0.0;
                    }
                    if (ch3[j] < 0.0)
                    {
                        ch3[j] = 0.0;
                    }
                    if (ch4[j] < 0.0)
                    {
                        ch4[j] = 0.0;
                    }
                }
                // Considering Negative Phase
                else if (signFlag == ALGO_SIGN_FLAG_NEG)
                {
                    if (ch1[j] > 0.0)
                    {
                        ch1[j] = 0.0;
                    }
                    if (ch2[j] > 0.0)
                    {
                        ch2[j] = 0.0;
                    }
                    if (ch3[j] > 0.0)
                    {
                        ch3[j] = 0.0;
                    }
                    if (ch4[j] > 0.0)
                    {
                        ch4[j] = 0.0;
                    }
                }
                // Considering Both
                else if (signFlag == ALGO_SIGN_FLAG_BOTH)
                {
                    ch1[j] = abs(ch1[j]);
                    ch2[j] = abs(ch2[j]);
                    ch3[j] = abs(ch3[j]);
                    ch4[j] = abs(ch4[j]);
                }

                if (ch1[j] > globalChannelNoise[0])
                {
                    tmpCh1.push_back(ch1[j]);
                }
                if (ch2[j] > globalChannelNoise[1])
                {
                    tmpCh2.push_back(ch2[j]);
                }
                if (ch3[j] > globalChannelNoise[2])
                {
                    tmpCh4.push_back(ch3[j]);
                }
                if (ch4[j] > globalChannelNoise[3])
                {
                    tmpCh4.push_back(ch4[j]);
                }
            }
            featureCh1.push_back(vectorMedian(tmpCh1));
            featureCh2.push_back(vectorMedian(tmpCh2));
            featureCh3.push_back(vectorMedian(tmpCh3));
            featureCh4.push_back(vectorMedian(tmpCh4));
        }
        previousValue = clickArray[i];
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
    getEachChannelMaxValueForClickType(&l_c[0], algoMode, signFlag, leftClickEachChannelMaxValue);  // Left Click
    getEachChannelMaxValueForClickType(&r_c[0], algoMode, signFlag, rightClickEachChannelMaxValue); // Right Click
    getEachChannelMaxValueForClickType(&t_c[0], algoMode, signFlag, thumbClickEachChannelMaxValue); // Thumb Click
    for (int i = 0; i < 4; i++)
    {
        globalChannelNoise[i] = minOfThree(leftClickEachChannelMaxValue[i], rightClickEachChannelMaxValue[i], thumbClickEachChannelMaxValue[i]);
    }
    // cout << globalChannelNoise[0] << " " << globalChannelNoise[1] << " " << globalChannelNoise[2] << " " << globalChannelNoise[3] << endl;
}

double MyAlgo::minOfThree(double x, double y, double z)
{
    return x < y ? (x < z ? x : z) : (y < z ? y : z);
}

void MyAlgo::getEachChannelMaxValueForClickType(int *clickArray, int algoMode, int signFlag, double (&eachChannelMaxSample)[4])
{

    double *ch1, *ch2, *ch3, *ch4;
    if (algoMode == ALGO_MODE_RAW)
    {
        ch1 = &ch1_raw[0];
        ch2 = &ch2_raw[0];
        ch3 = &ch3_raw[0];
        ch4 = &ch4_raw[0];
    }
    else if (algoMode == ALGO_MODE_TKEO)
    {
        ch1 = &ch1_tkeo[0];
        ch2 = &ch2_tkeo[0];
        ch3 = &ch3_tkeo[0];
        ch4 = &ch4_tkeo[0];
    }
    else if (algoMode == ALGO_MODE_P3_TKEO)
    {
        ch1 = &ch1_p3_tkeo[0];
        ch2 = &ch2_p3_tkeo[0];
        ch3 = &ch3_p3_tkeo[0];
        ch4 = &ch4_p3_tkeo[0];
    }
    else if (algoMode == ALGO_MODE_F_TKEO)
    {
        ch1 = &ch1_f_tkeo[0];
        ch2 = &ch2_f_tkeo[0];
        ch3 = &ch3_f_tkeo[0];
        ch4 = &ch4_f_tkeo[0];
    }
    else if (algoMode == ALGO_MODE_P3_F_TKEO)
    {
        ch1 = &ch1_p3_f_tkeo[0];
        ch2 = &ch2_p3_f_tkeo[0];
        ch3 = &ch3_p3_f_tkeo[0];
        ch4 = &ch4_p3_f_tkeo[0];
    }

    int previousValue = 0;
    for (int i = 0; i < ch1_raw.size(); i++)
    {
        if (i > trainingWindowStartPointForNoise && clickArray[i] == 1 && previousValue == 0)
        {
            for (int j = i - trainingWindowStartPointForNoise; j < i - trainingWindowEndPointForNoise; j++)
            {
                // Considering Positive Phase
                if (signFlag == ALGO_SIGN_FLAG_POS)
                {
                    if (ch1[j] < 0.0)
                    {
                        ch1[j] = 0.0;
                    }
                    if (ch2[j] < 0.0)
                    {
                        ch2[j] = 0.0;
                    }
                    if (ch3[j] < 0.0)
                    {
                        ch3[j] = 0.0;
                    }
                    if (ch4[j] < 0.0)
                    {
                        ch4[j] = 0.0;
                    }
                }
                // Considering Negative Phase
                else if (signFlag == ALGO_SIGN_FLAG_NEG)
                {
                    if (ch1[j] > 0.0)
                    {
                        ch1[j] = 0.0;
                    }
                    if (ch2[j] > 0.0)
                    {
                        ch2[j] = 0.0;
                    }
                    if (ch3[j] > 0.0)
                    {
                        ch3[j] = 0.0;
                    }
                    if (ch4[j] > 0.0)
                    {
                        ch4[j] = 0.0;
                    }
                }
                // Considering Both
                else if (signFlag == ALGO_SIGN_FLAG_BOTH)
                {
                    ch1[j] = abs(ch1[j]);
                    ch2[j] = abs(ch2[j]);
                    ch3[j] = abs(ch3[j]);
                    ch4[j] = abs(ch4[j]);
                }

                //Getthing MAX value among all windows in each channel
                if (ch1[j] > eachChannelMaxSample[0])
                {
                    eachChannelMaxSample[0] = ch1[j];
                }

                if (ch2[j] > eachChannelMaxSample[1])
                {
                    eachChannelMaxSample[1] = ch2[j];
                }

                if (ch3[j] > eachChannelMaxSample[2])
                {
                    eachChannelMaxSample[2] = ch3[j];
                }

                if (ch4[j] > eachChannelMaxSample[3])
                {
                    eachChannelMaxSample[3] = ch4[j];
                }
            }
        }
        previousValue = clickArray[i];
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
    totalNumberOfTrainingDataSamples = trainingDataChannel1.size();

    auto ch1 = trainingDataChannel1.begin();
    auto ch2 = trainingDataChannel2.begin();
    auto ch3 = trainingDataChannel3.begin();
    auto ch4 = trainingDataChannel4.begin();
    auto lc = trainingDataLeftClick.begin();
    auto rc = trainingDataRightClick.begin();
    auto tc = trainingDataThumbClick.begin();

    double prev_val, prev_prev_val;

    int i = 0;
    while (ch1 != trainingDataChannel1.end())
    {
        if (i > 1)
        {
            ch1_raw.push_back(*ch1);
            ch2_raw.push_back(*ch2);
            ch3_raw.push_back(*ch3);
            ch4_raw.push_back(*ch4);
            l_c.push_back(*lc);
            r_c.push_back(*rc);
            t_c.push_back(*tc);

            prev_val = *(--ch1);
            prev_prev_val = *(--ch1);
            ch1++;
            ch1++;
            ch1_tkeo.push_back(getTkeoValue(prev_prev_val, prev_val, *ch1));
            ch1_p3_tkeo.push_back(getTkeoValue(pow(prev_prev_val, 3), pow(prev_val, 3), pow(*ch1, 3)));
            ch1_p3_f_tkeo.push_back(getTkeoValue(filterTools.getFilteredValue(1, pow(prev_prev_val, 3)), filterTools.getFilteredValue(1, pow(prev_val, 3)), filterTools.getFilteredValue(1, pow(*ch1, 3))));
            ch1_f_tkeo.push_back(getTkeoValue(filterTools.getFilteredValue(1, prev_prev_val), filterTools.getFilteredValue(1, prev_val), filterTools.getFilteredValue(1, *ch1)));

            prev_val = *(--ch2);
            prev_prev_val = *(--ch2);
            ch2++;
            ch2++;
            ch2_tkeo.push_back(getTkeoValue(prev_prev_val, prev_val, *ch2));
            ch2_p3_tkeo.push_back(getTkeoValue(pow(prev_prev_val, 3), pow(prev_val, 3), pow(*ch2, 3)));
            ch2_p3_f_tkeo.push_back(getTkeoValue(filterTools.getFilteredValue(2, pow(prev_prev_val, 3)), filterTools.getFilteredValue(2, pow(prev_val, 3)), filterTools.getFilteredValue(2, pow(*ch2, 3))));
            ch2_f_tkeo.push_back(getTkeoValue(filterTools.getFilteredValue(2, prev_prev_val), filterTools.getFilteredValue(2, prev_val), filterTools.getFilteredValue(2, *ch2)));

            prev_val = *(--ch3);
            prev_prev_val = *(--ch3);
            ch3++;
            ch3++;
            ch3_tkeo.push_back(getTkeoValue(prev_prev_val, prev_val, *ch3));
            ch3_p3_tkeo.push_back(getTkeoValue(pow(prev_prev_val, 3), pow(prev_val, 3), pow(*ch3, 3)));
            ch3_p3_f_tkeo.push_back(getTkeoValue(filterTools.getFilteredValue(3, pow(prev_prev_val, 3)), filterTools.getFilteredValue(3, pow(prev_val, 3)), filterTools.getFilteredValue(3, pow(*ch3, 3))));
            ch3_f_tkeo.push_back(getTkeoValue(filterTools.getFilteredValue(3, prev_prev_val), filterTools.getFilteredValue(3, prev_val), filterTools.getFilteredValue(3, *ch2)));

            prev_val = *(--ch4);
            prev_prev_val = *(--ch4);
            ch4++;
            ch4++;
            ch4_tkeo.push_back(getTkeoValue(prev_prev_val, prev_val, *ch4));
            ch4_p3_tkeo.push_back(getTkeoValue(pow(prev_prev_val, 3), pow(prev_val, 3), pow(*ch4, 3)));
            ch4_p3_f_tkeo.push_back(getTkeoValue(filterTools.getFilteredValue(4, pow(prev_prev_val, 3)), filterTools.getFilteredValue(4, pow(prev_val, 3)), filterTools.getFilteredValue(4, pow(*ch4, 3))));
            ch4_f_tkeo.push_back(getTkeoValue(filterTools.getFilteredValue(4, prev_prev_val), filterTools.getFilteredValue(4, prev_val), filterTools.getFilteredValue(4, *ch4)));
        }
        ch1++;
        ch2++;
        ch3++;
        ch4++;
        lc++;
        rc++;
        tc++;
        i++;
    }
}

void MyAlgo::readData(string fileName)
{
    std::string line;
    std::ifstream infile(GB_IMPULSE_DIRECTORY+"/"+fileName);
    if (infile.fail())
    {
        cout << "Unable to open file : " << GB_IMPULSE_DIRECTORY+"/"+fileName << endl;
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
        // std::cout << s << std::endl;
        trainingDataThumbClick.push_back(std::stoi(s));
    }
}

#endif // !MyAlgo_CPP
