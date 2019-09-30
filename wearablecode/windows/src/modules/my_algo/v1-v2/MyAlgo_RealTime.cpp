#ifndef MyAlgo_RealTime_CPP
#define MyAlgo_RealTime_CPP
#include "MyAlgo.hpp"

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
        else if (bestAlgoModeLC == ALGO_MODE_P3_TKEO)
        {
            sample.push_back(getTkeoValue(pow(prevPrevSampleRealTime.at(0), 3), pow(prevSampleRealTime.at(0), 3), pow(ch1.at(i), 3)));
            sample.push_back(getTkeoValue(pow(prevPrevSampleRealTime.at(1), 3), pow(prevSampleRealTime.at(1), 3), pow(ch2.at(i), 3)));
            sample.push_back(getTkeoValue(pow(prevPrevSampleRealTime.at(2), 3), pow(prevSampleRealTime.at(2), 3), pow(ch3.at(i), 3)));
            sample.push_back(getTkeoValue(pow(prevPrevSampleRealTime.at(3), 3), pow(prevSampleRealTime.at(3), 3), pow(ch4.at(i), 3)));
        }

        // tmp1.clear();
        // tmp2.clear();
        // tmp3.clear();
        // tmp4.clear();
        // for (int i = 0; i < trainingDataChannel1.size(); i++)
        // {
        //     tmp1.push_back(pow(filterTools.getFilteredValue(1, trainingDataChannel1.at(i)), 3));
        //     tmp2.push_back(pow(filterTools.getFilteredValue(2, trainingDataChannel2.at(i)), 3));
        //     tmp3.push_back(pow(filterTools.getFilteredValue(3, trainingDataChannel3.at(i)), 3));
        //     tmp4.push_back(pow(filterTools.getFilteredValue(4, trainingDataChannel4.at(i)), 3));
        // }
        // for (int i = 2; i < tmp1.size(); i++)
        // {
        //     ch1_p3_f_tkeo.push_back(getTkeoValue(tmp1.at(i - 2), tmp1.at(i - 1), tmp1.at(i)));
        //     ch2_p3_f_tkeo.push_back(getTkeoValue(tmp2.at(i - 2), tmp2.at(i - 1), tmp2.at(i)));
        //     ch3_p3_f_tkeo.push_back(getTkeoValue(tmp3.at(i - 2), tmp3.at(i - 1), tmp3.at(i)));
        //     ch4_p3_f_tkeo.push_back(getTkeoValue(tmp4.at(i - 2), tmp4.at(i - 1), tmp4.at(i)));
        // }

        // tmp1.clear();
        // tmp2.clear();
        // tmp3.clear();
        // tmp4.clear();
        // for (int i = 0; i < trainingDataChannel1.size(); i++)
        // {
        //     tmp1.push_back(filterTools.getFilteredValue(1, trainingDataChannel1.at(i)));
        //     tmp2.push_back(filterTools.getFilteredValue(2, trainingDataChannel2.at(i)));
        //     tmp3.push_back(filterTools.getFilteredValue(3, trainingDataChannel3.at(i)));
        //     tmp4.push_back(filterTools.getFilteredValue(4, trainingDataChannel4.at(i)));
        // }
        // for (int i = 2; i < tmp1.size(); i++)
        // {
        //     ch1_f_tkeo.push_back(getTkeoValue(tmp1.at(i - 2), tmp1.at(i - 1), tmp1.at(i)));
        //     ch2_f_tkeo.push_back(getTkeoValue(tmp2.at(i - 2), tmp2.at(i - 1), tmp2.at(i)));
        //     ch3_f_tkeo.push_back(getTkeoValue(tmp3.at(i - 2), tmp3.at(i - 1), tmp3.at(i)));
        //     ch4_f_tkeo.push_back(getTkeoValue(tmp4.at(i - 2), tmp4.at(i - 1), tmp4.at(i)));
        // }

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

        threeSamplesRealTime.push_back(sample);

        predictCLickTypeFromThreeSamples(threeSamplesRealTime, true);

        threeSamplesRealTime.erase(threeSamplesRealTime.begin());
        prevPrevSampleRealTime = prevSampleRealTime;
        prevSampleRealTime = sample;
    }
}

#endif