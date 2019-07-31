/* Include files */
// Run Command cl test2.cpp /link ../iir.lib
#ifndef My_Filter
#define My_Filter

#include "iir_c_files/iir.h"
#include "..\edata\Global.cpp"
#include <iostream>
using namespace std;

class FilterTools
{
private:
    double samplingrate = GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD;
    double lf = GB_FILTER_LOW_FREQUENCY;
    double hf = GB_FILTER_HIGH_FREQUENCY;
    Iir::Butterworth::BandPass<GB_FILTER_ORDER> fCh1, fCh2, fCh3, fCh4;

public:
    FilterTools()
    {
        setupFilter();
    }
    void setupFilter();
    double getFilteredValue(int channelNumber, double value);
};

#endif