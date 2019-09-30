#ifndef MyAlgo_LabelClickType_HPP
#define MyAlgo_LabelClickType_HPP

#include "MyAlgo.hpp"

std::vector<int> MyAlgo::labelClickType(std::vector<std::vector<int>> clicks, int t1, int t2)
{
    std::vector<int> clickAssemble;
    int n = clicks.at(0).size(); // # of click types

    // initialization
    for (int i = 0; i < clicks.size(); i++)
    {
        clickAssemble.push_back(0);
    }

    int i = 0;
    while (i < clicks.size())
    {
        int temp = 0;
        int j = 0;

        for (; j < n; j++)
        {
            temp = clicks.at(i).at(j);
            if (temp > 0)
                break;
        }
        if (temp > 0)
        {
            // change the previous to the click type id
            for (int k = 1; k <= t1 && i - k >= 0 && clickAssemble.at(i - k) == 0; k++)
            {
                clickAssemble.at(i - k) = j + 1;
            }
            // change the following to 4
            do
            {

                clickAssemble.at(i) = 4;
                i++;
            } while (i < clicks.size() && clicks.at(i).at(j) == temp);
            // change the after to 4

            for (int k = 0; k <= t2; k++)
            {
                if (i + k < clickAssemble.size())
                {
                    clickAssemble.at(i + k) = 4;
                }
            }
            i = i + t2;
        }
        else
        {
            i++;
        }
    }

    return clickAssemble;
}

#endif