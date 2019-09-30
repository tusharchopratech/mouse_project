#ifndef MyAlgo_GetTkeo_CPP
#define MyAlgo_GetTkeo_CPP
#include "MyAlgo.hpp"


double MyAlgo::getTkeoValue(double v1, double v2, double v3)
{
    // v1 = v1 * v1 * v1;
    // v2 = v2 * v2 * v2;
    // v3 = v3 * v3 * v3;
    // double result = ((v2 * v2) - (v1 * v3));
    double result = v1 * v2 * v3;
    return result;
}

#endif