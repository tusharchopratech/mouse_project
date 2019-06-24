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

Iir::Butterworth::BandPass<5> f;
void setupFilter()
{
    double samplingrate = 2000;
    double lf = 110;
    double hf = 250; 
    f.setup(5,samplingrate, (lf+hf)/2,  (hf-lf));
}

double getFilteredValue(double value)
{
    return f.filter(value);
}

#endif