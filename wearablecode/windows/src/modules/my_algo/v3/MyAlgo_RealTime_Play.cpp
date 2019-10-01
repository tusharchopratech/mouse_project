/**
    MyAlgo_RealTime.cpp
    Purpose: Computes realtime samples and detects whether to fire click or not. 
    If it is not within click and not in the refractory time (refractoryTime after the last detected click), start detection.

    @author Jiayuan He (Ebionics Waterloo)
    @version 3.0 30/09/2019
*/

#ifndef MyAlgo_RealTime_Play_HPP
#define MyAlgo_RealTime_Play_HPP

#include "MyAlgo.hpp"

bool MyAlgo::fnRealTime(std::vector<std::vector<double>> rawdata3Samples, std::vector<int> channel, std::vector<double> thresholdValues, int vots)
{

    // feature extraction
    std::vector<std::vector<double>> d_feat;
    d_feat.clear();
    d_feat = tkoTime(rawdata3Samples, 1); // TKO feature extraction
    int f1 = 0;
    if (d_feat.at(0).at(channel.at(0) - 1) > thresholdValues.at(0))
        f1 = 1;

    d_feat.clear();
    d_feat = tkoTime(rawdata3Samples, 3);
    int f2 = 0;
    if (d_feat.at(0).at(channel.at(1) - 1) > thresholdValues.at(1))
        f2 = 1;

    d_feat.clear();
    d_feat = tkoSpatial(rawdata3Samples, 1);
    int f3 = 0;
    if (d_feat.at(0).at(channel.at(2) - 1) > thresholdValues.at(2))
        f3 = 1;

    // majority vote
    if (f1 + f2 + f3 > vots)
    {
        // cout << "Fire" << endl;
        return true;
    }
    else
    {
        return false;
    }
}

#endif