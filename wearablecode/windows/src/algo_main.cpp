#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <numeric>

using namespace std;
#include <vector>
#include "algo_main_2.cpp"

vector<double> trainingDataChannel1, trainingDataChannel2, trainingDataChannel3, trainingDataChannel4;
vector<int> trainingDataLeftClick, trainingDataRightClick, trainingDataThumbClick;

static const double SAMPLING_RATE = 2048.00;
int trainingWindowStartPointForNoise = (int)(2.2 * SAMPLING_RATE);
int trainingWindowEndPointForNoise = (int)(1.8 * SAMPLING_RATE);

int trainingWindowStartPointForFeatureConstruction = (int)(1 * SAMPLING_RATE);

int totalNumberOfTrainingDataSamples;

vector<double> ch1_raw, ch1_tkeo, ch1_p3_tkeo, ch1_f_tkeo, ch1_p3_f_tkeo;
vector<double> ch2_raw, ch2_tkeo, ch2_p3_tkeo, ch2_f_tkeo, ch2_p3_f_tkeo;
vector<double> ch3_raw, ch3_tkeo, ch3_p3_tkeo, ch3_f_tkeo, ch3_p3_f_tkeo;
vector<double> ch4_raw, ch4_tkeo, ch4_p3_tkeo, ch4_f_tkeo, ch4_p3_f_tkeo;
vector<int> l_c, r_c, t_c;

double globalChannelNoise[4] = {5.0, 5.0, 5.0, 5.0};

/*
0 :RAW Signal
1 :TKEO 
2 :Powered 3 TKEO
3 :Filtered TKEO
4 :Powered 3, Filtered, TKEO
 */
static const int ALGO_MODE = 0;

/*
1 : consider positive phase
0 : consider both phase
-1 : consider negative phase
 */
static const int SIGN_FLAG = 1;

vector<vector<double>> covMatrixRightClick;
vector<vector<double>> covMatrixLeftClick;
vector<vector<double>> covMatrixThumbClick;
vector<double> meanLeftClick;
vector<double> meanRightClick;
vector<double> meanThumbClick;

std::string line;
std::ifstream infile("data_train.txt");

void readData();
void processData();

void computeGlobalNoice();
void getEachChannelMaxValueForClickType(int *clickArray, int algoMode, int signFlag, double (&eachChannelMaxSample)[4]);

void computeFeatures();
void getFeaturesForClickType(int *clickArray, int algoMode, int signFlag, vector<vector<double>> &featureVector);

int main()
{
    readData();
    processData();
    computeGlobalNoice();
    computeFeatures();

    return 0;
}

void printVecor(vector<vector<double>> vec)
{
    for (unsigned i = 0; i < vec.size(); i++)
    {
        for (unsigned j = 0; j < vec[i].size(); j++)
        {
            cout << vec[i][j] << " ";
        }
        cout << endl;
    }
}

void computeFeatures()
{
    double mean1, mean2, mean3, mean4;
    // Left Click
    vector<vector<double>> leftCLickFeatures;
    getFeaturesForClickType(&l_c[0], ALGO_MODE, SIGN_FLAG, leftCLickFeatures);
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
    vector<vector<double>> rightCLickFeatures;
    getFeaturesForClickType(&r_c[0], ALGO_MODE, SIGN_FLAG, rightCLickFeatures);
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
    vector<vector<double>> thumbCLickFeatures;
    getFeaturesForClickType(&t_c[0], ALGO_MODE, SIGN_FLAG, thumbCLickFeatures);
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

void getFeaturesForClickType(int *clickArray, int algoMode, int signFlag, vector<vector<double>> &featureVector)
{
    vector<double> featureCh1, featureCh2, featureCh3, featureCh4;
    double *ch1, *ch2, *ch3, *ch4;
    if (algoMode == 0)
    {
        ch1 = &ch1_raw[0];
        ch2 = &ch2_raw[0];
        ch3 = &ch3_raw[0];
        ch4 = &ch4_raw[0];
    }
    else if (algoMode == 1)
    {
        ch1 = &ch1_tkeo[0];
        ch2 = &ch2_tkeo[0];
        ch3 = &ch3_tkeo[0];
        ch4 = &ch4_tkeo[0];
    }
    else if (algoMode == 2)
    {
        ch1 = &ch1_p3_tkeo[0];
        ch2 = &ch2_p3_tkeo[0];
        ch3 = &ch3_p3_tkeo[0];
        ch4 = &ch4_p3_tkeo[0];
    }
    else if (algoMode == 3)
    {
        ch1 = &ch1_f_tkeo[0];
        ch2 = &ch2_f_tkeo[0];
        ch3 = &ch3_f_tkeo[0];
        ch4 = &ch4_f_tkeo[0];
    }
    else if (algoMode == 4)
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
            vector<double> tmpCh1, tmpCh2, tmpCh3, tmpCh4;
            for (int j = i - trainingWindowStartPointForFeatureConstruction; j < i; j++)
            {
                // Considering Positive Phase
                if (signFlag == 1)
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
                else if (signFlag == -1)
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
                else if (signFlag == 0)
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

void computeGlobalNoice()
{
    double leftClickEachChannelMaxValue[] = {-5.0, -5.0, -5.0, -5.0};
    double rightClickEachChannelMaxValue[] = {-5.0, -5.0, -5.0, -5.0};
    double thumbClickEachChannelMaxValue[] = {-5.0, -5.0, -5.0, -5.0};
    getEachChannelMaxValueForClickType(&l_c[0], ALGO_MODE, SIGN_FLAG, leftClickEachChannelMaxValue);  // Left Click
    getEachChannelMaxValueForClickType(&r_c[0], ALGO_MODE, SIGN_FLAG, rightClickEachChannelMaxValue); // Right Click
    getEachChannelMaxValueForClickType(&t_c[0], ALGO_MODE, SIGN_FLAG, thumbClickEachChannelMaxValue); // Thumb Click
    for (int i = 0; i < 4; i++)
    {
        globalChannelNoise[i] = std::min({leftClickEachChannelMaxValue[i], rightClickEachChannelMaxValue[i], thumbClickEachChannelMaxValue[i]});
    }
    cout << globalChannelNoise[0] << " " << globalChannelNoise[1] << " " << globalChannelNoise[2] << " " << globalChannelNoise[3] << endl;
}

void getEachChannelMaxValueForClickType(int *clickArray, int algoMode, int signFlag, double (&eachChannelMaxSample)[4])
{

    double *ch1, *ch2, *ch3, *ch4;
    if (algoMode == 0)
    {
        ch1 = &ch1_raw[0];
        ch2 = &ch2_raw[0];
        ch3 = &ch3_raw[0];
        ch4 = &ch4_raw[0];
    }
    else if (algoMode == 1)
    {
        ch1 = &ch1_tkeo[0];
        ch2 = &ch2_tkeo[0];
        ch3 = &ch3_tkeo[0];
        ch4 = &ch4_tkeo[0];
    }
    else if (algoMode == 2)
    {
        ch1 = &ch1_p3_tkeo[0];
        ch2 = &ch2_p3_tkeo[0];
        ch3 = &ch3_p3_tkeo[0];
        ch4 = &ch4_p3_tkeo[0];
    }
    else if (algoMode == 3)
    {
        ch1 = &ch1_f_tkeo[0];
        ch2 = &ch2_f_tkeo[0];
        ch3 = &ch3_f_tkeo[0];
        ch4 = &ch4_f_tkeo[0];
    }
    else if (algoMode == 4)
    {
        ch1 = &ch1_p3_f_tkeo[0];
        ch2 = &ch2_p3_f_tkeo[0];
        ch3 = &ch3_p3_f_tkeo[0];
        ch4 = &ch4_p3_f_tkeo[0];
    }

    int previousValue = 0;
    for (int i = 0; i < totalNumberOfTrainingDataSamples; i++)
    {
        if (i > trainingWindowStartPointForNoise && clickArray[i] == 1 && previousValue == 0)
        {
            for (int j = i - trainingWindowStartPointForNoise; j < i - trainingWindowEndPointForNoise; j++)
            {
                // Considering Positive Phase
                if (signFlag == 1)
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
                else if (signFlag == -1)
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
                else if (signFlag == 0)
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

double getTkeoValue(double v1, double v2, double v3)
{
    v1 = v1 * v1 * v1;
    v2 = v2 * v2 * v2;
    v3 = v3 * v3 * v3;
    double result = ((v2 * v2) - (v1 * v3));
    return result;
}

void processData()
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

            prev_val = *(--ch2);
            prev_prev_val = *(--ch2);
            ch2++;
            ch2++;
            ch2_tkeo.push_back(getTkeoValue(prev_prev_val, prev_val, *ch2));
            ch2_p3_tkeo.push_back(getTkeoValue(pow(prev_prev_val, 3), pow(prev_val, 3), pow(*ch2, 3)));

            prev_val = *(--ch3);
            prev_prev_val = *(--ch3);
            ch3++;
            ch3++;
            ch3_tkeo.push_back(getTkeoValue(prev_prev_val, prev_val, *ch3));
            ch3_p3_tkeo.push_back(getTkeoValue(pow(prev_prev_val, 3), pow(prev_val, 3), pow(*ch3, 3)));

            prev_val = *(--ch4);
            prev_prev_val = *(--ch4);
            ch4++;
            ch4++;
            ch4_tkeo.push_back(getTkeoValue(prev_prev_val, prev_val, *ch4));
            ch4_p3_tkeo.push_back(getTkeoValue(pow(prev_prev_val, 3), pow(prev_val, 3), pow(*ch4, 3)));

            // ch1_f_tkeo.push_back() similarly using filter
            // ch1_p3_f_tkeo.push_back() similarly using filter
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

void readData()
{
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
                trainingDataLeftClick.push_back(std::stod(token));
            }
            else if (i == 5)
            {
                trainingDataRightClick.push_back(std::stod(token));
            }
            i++;
        }
        // std::cout << s << std::endl;
        trainingDataThumbClick.push_back(std::stod(s));
    }
}