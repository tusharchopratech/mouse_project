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
        return true;
    }
    else
    {
        return false;
    }
}

string MyAlgo::fnRealTimeBoth(std::vector<std::vector<double>> rawdata3Samples, int vots)
{
    // left, right, both
    string fireClick = "none";
    std::vector<std::vector<double>> d_feat;
    int f1_l = 0, f2_l = 0, f3_l = 0, f1_r = 0, f2_r = 0, f3_r = 0;
    int fireLeftClick = 0;
    int fireRightClick = 0;

    // feature extraction for Left Click and Right
    d_feat.clear();
    d_feat = tkoTime(rawdata3Samples, 1); // TKO feature extraction
    if (d_feat.at(0).at(channelIDLeft.at(0) - 1) > thresholdValuesLeftClick.at(0))
    {
        f1_l = 1;
    }
    if (d_feat.at(0).at(channelIDRight.at(0) - 1) > thresholdValuesRightClick.at(0))
    {
        f1_r = 1;
    }

    d_feat.clear();
    d_feat = tkoTime(rawdata3Samples, 3);
    if (d_feat.at(0).at(channelIDLeft.at(1) - 1) > thresholdValuesLeftClick.at(1))
    {
        f2_l = 1;
    }
    if (d_feat.at(0).at(channelIDRight.at(1) - 1) > thresholdValuesRightClick.at(1))
    {
        f2_r = 1;
    }

    d_feat.clear();
    d_feat = tkoSpatial(rawdata3Samples, 1);
    if (d_feat.at(0).at(channelIDLeft.at(2) - 1) > thresholdValuesLeftClick.at(2))
    {
        f1_l = 1;
    }
    if (d_feat.at(0).at(channelIDRight.at(2) - 1) > thresholdValuesRightClick.at(2))
    {
        f2_r = 1;
    }

 
    // majority vote for Left Click
    if (f1_l + f2_l + f3_l > vots)
    {
        fireLeftClick = 1;
    }
    // majority vote for Right Click
    if (f1_r + f2_r + f3_r > vots)
    {
        fireRightClick = 1;
    }

    if (fireLeftClick == 1 && fireRightClick == 1)
    {
        fireClick = "both";
    }
    else if (fireLeftClick == 1 && fireRightClick == 0)
    {
        fireClick = "left";
    }
    else if (fireLeftClick == 0 && fireRightClick == 1)
    {
        fireClick = "right";
    }

    return fireClick;
}

#endif