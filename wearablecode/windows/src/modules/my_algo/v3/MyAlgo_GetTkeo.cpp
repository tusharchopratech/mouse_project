#ifndef MyAlgo_GetTkeo_CPP
#define MyAlgo_GetTkeo_CPP
#include "MyAlgo.hpp"

std::vector<std::vector<double>> MyAlgo::tkoSpatial(std::vector<std::vector<double>> signal, int p)
{
    std::vector<std::vector<double>> datafeat;
    std::vector<double> tmp;
    for (int i = 0; i < signal.size(); i++)
    {
        //For Channel 1, then 2, then 3 then 4
        tmp.push_back(getTkeoValue(pow(signal.at(i).at(0), p), pow(signal.at(i).at(1), p), pow(signal.at(i).at(2), p)));
        tmp.push_back(getTkeoValue(pow(signal.at(i).at(1), p), pow(signal.at(i).at(2), p), pow(signal.at(i).at(3), p)));
        tmp.push_back(getTkeoValue(pow(signal.at(i).at(2), p), pow(signal.at(i).at(3), p), pow(signal.at(i).at(0), p)));
        tmp.push_back(getTkeoValue(pow(signal.at(i).at(3), p), pow(signal.at(i).at(0), p), pow(signal.at(i).at(1), p)));

        datafeat.push_back(tmp);
        tmp.clear();
    }

    return datafeat;
}

std::vector<std::vector<double>> MyAlgo::tkoTime(std::vector<std::vector<double>> signal, int p)
{
    std::vector<std::vector<double>> datafeat;
    std::vector<double> tmp;
    for (int i = 0; i < signal.size() - 2; i++)
    {
        //For Channel 1, then 2, then 3 then 4
        tmp.push_back(getTkeoValue(pow(signal.at(i).at(0), p), pow(signal.at(i + 1).at(0), p), pow(signal.at(i + 2).at(0), p)));
        tmp.push_back(getTkeoValue(pow(signal.at(i).at(1), p), pow(signal.at(i + 1).at(1), p), pow(signal.at(i + 2).at(1), p)));
        tmp.push_back(getTkeoValue(pow(signal.at(i).at(2), p), pow(signal.at(i + 1).at(2), p), pow(signal.at(i + 2).at(2), p)));
        tmp.push_back(getTkeoValue(pow(signal.at(i).at(3), p), pow(signal.at(i + 1).at(3), p), pow(signal.at(i + 2).at(3), p)));

        datafeat.push_back(tmp);
        tmp.clear();
    }

    return datafeat;
}

double MyAlgo::getTkeoValue(double v1, double v2, double v3)
{
    return v2 * v2 - v1 * v3;
}

#endif