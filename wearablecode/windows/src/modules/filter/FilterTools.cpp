#include "FilterTools.hpp"


void FilterTools::setupFilter()
{
    fCh1.setup(5, samplingrate, (lf + hf) / 2, (hf - lf));
    fCh2.setup(5, samplingrate, (lf + hf) / 2, (hf - lf));
    fCh3.setup(5, samplingrate, (lf + hf) / 2, (hf - lf));
    fCh4.setup(5, samplingrate, (lf + hf) / 2, (hf - lf));
}

double FilterTools::getFilteredValue(int channelNumber, double value)
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