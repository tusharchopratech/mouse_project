/* Include files */
// Run Command cl test2.cpp /link ../iir.lib
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "iir_c_files/iir.h"

#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

const int order = 395;
Iir::Butterworth::BandPass<order> f;
const float samplingrate = 2000;

void setupFilter()
{
    f.setup(samplingrate, 180, 140);
}

double getFilteredValue(double value)
{
    return f.filter(value);
}
