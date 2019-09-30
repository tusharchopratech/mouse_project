#ifndef MyAlgo_V2_CPP
#define MyAlgo_V2_CPP
#include "MyAlgo.hpp"
#include "MyAlgo_GlobalNoise.cpp"
#include "MyAlgo_ReadNProcessData.cpp"
#include "MyAlgo_GetTrainingData_V3.cpp"
#include "MyA;go_ComputeFeatures_V2.cpp"
#include "MyAlgo_GetTkeo.cpp"
#include "MyAlgo_RealTime.cpp"

string MyAlgo::getAlgoResults(string pName, int noCh, int trialNo)
{
    participantName = pName;
    trialNumber = trialNo;
    numberOfChannelesUsedForTraining = noCh;
    readData();
    processData();
    // string result = predictAndWriteResults();

    // return result;
    startAnalysing();
    return "";
}

void MyAlgo::startAnalysing()
{
    // For d_tkeo
    computeGlobalNoice(d_tkeo);
    computeFeatures(d_tkeo);
    // gb_print2DVector(d_training_data);
}



#endif // !MyAlgo_CPP
