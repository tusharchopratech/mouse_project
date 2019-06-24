/* Include files */
// Run Command cl test2.cpp /link ../iir.lib
#ifndef MyFilter
#define MyFilter
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "iir_c_files/iir.h"

#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

Iir::Butterworth::BandPass<5> fCh1, fCh2, fCh3, fCh4;
void setupFilter()
{
    double samplingrate = 2048;
    double lf = 110;
    double hf = 250;
    fCh1.setup(5, samplingrate, (lf + hf) / 2, (hf - lf));
    fCh2.setup(5, samplingrate, (lf + hf) / 2, (hf - lf));
    fCh3.setup(5, samplingrate, (lf + hf) / 2, (hf - lf));
    fCh4.setup(5, samplingrate, (lf + hf) / 2, (hf - lf));
}

double getFilteredValue(int channelNumber, double value)
{
    if (channelNumber == 1)
    {
        return fCh1.filter(value);
    }
    else if (channelNumber == 2)
    {
        return fCh2.filter(value);
    }
    else if (channelNumber == 3)
    {
        return fCh3.filter(value);
    }
    else if (channelNumber == 4)
    {
        return fCh4.filter(value);
    }
    return 0.0;
}

#endif