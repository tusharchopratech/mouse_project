#ifndef MDaq_H
#define MDaq_H

#include "uldaq.h"
#include <iostream>
#include <stdio.h>

using namespace std;

#define MAX_STR_LENGTH 64
#define MAX_DEV_COUNT 100

class MDaq
{
private:
    unsigned int numDevs;
    DaqDeviceDescriptor devDescriptors[100];
    DaqDeviceHandle handle;
    int chan;
    double data;
    UlError err;

public:
    MDaq()
    {
        numDevs = MAX_DEV_COUNT;
        handle = 0;
        chan = 0;
        data = 0;
        err = ERR_NO_ERROR;
        ulGetDaqDeviceInventory(ANY_IFC, devDescriptors, &numDevs);
        if (numDevs)
        {
            handle = ulCreateDaqDevice(devDescriptors[0]);
            if (handle)
            {
                err = ulConnectDaqDevice(handle);
                std::cout << "DAQ Initialized." << std::endl;
            }
        }
    }


    double getVoltageFromChannel(int channel)
    {
        err = ulAIn(handle, channel, AI_SINGLE_ENDED, BIP5VOLTS, AIN_FF_DEFAULT, &data);
        return data;
    }

    ~MDaq()
    {
        ulDisconnectDaqDevice(handle);
        ulReleaseDaqDevice(handle);
        std::cout << "DAQ Released." << std::endl;
    }

    void functionOne();
};

#endif