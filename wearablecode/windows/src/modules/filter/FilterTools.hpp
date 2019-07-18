/* Include files */
// Run Command cl test2.cpp /link ../iir.lib
#ifndef My_Filter
#define My_Filter

#include "iir_c_files/iir.h"
#include <iostream>
using namespace std;

class FilterTools
{
private:
    double samplingrate = 2048;
    double lf = 110;
    double hf = 250;
    Iir::Butterworth::BandPass<5> fCh1, fCh2, fCh3, fCh4;

public:
    FilterTools()
    {
        setupFilter();
    }
    void setupFilter();
    double getFilteredValue(int channelNumber, double value);
};

#endif