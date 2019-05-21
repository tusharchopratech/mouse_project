/*
 * main.c
 *
 *  Created on: 2019-05-16
 *      Author: tushar
 */
#include <iostream>
#include <stdio.h>
#include "uldaq.h"
#include "modules/m_daq/MDaq.hpp"
#define MAX_DEV_COUNT  100
#define MAX_STR_LENGTH 64

using namespace std;

int main()
{
	unsigned int numDevs = MAX_DEV_COUNT;
	DaqDeviceDescriptor devDescriptors[MAX_DEV_COUNT];
	DaqDeviceHandle handle = 0;

	int chan = 0;
	double data = 0;
	UlError err = ERR_NO_ERROR;

	MDaq m;
	m.functionOne();

	// Get descriptors for all of the available DAQ devices
	ulGetDaqDeviceInventory(ANY_IFC, devDescriptors, &numDevs);

	// verify at least one DAQ device is detected
	if (numDevs)
	{
		// while(1){

		// get a handle to the DAQ device associated with the first descriptor
		handle = ulCreateDaqDevice(devDescriptors[0]);

		// check if the DAQ device handle is valid
		if (handle)
		{
			// establish a connection to the DAQ device
			err = ulConnectDaqDevice(handle);

			// read data for the first 4 analog input channels
			// system("clear");
//			err = ulAIn(handle, 11, AI_SINGLE_ENDED, BIP5VOLTS, AIN_FF_DEFAULT, &data);
//			printf("Channel(%d) Data: %10.6f\n", chan, data);

			for (chan = 10; chan <= 14; chan++)
			{
				err = ulAIn(handle, chan, AI_SINGLE_ENDED, BIP5VOLTS, AIN_FF_DEFAULT, &data);
				printf("Channel(%d) Data: %10.6f\n", chan, data);
			}

			ulDisconnectDaqDevice(handle);
			ulReleaseDaqDevice(handle);
		// }
		}
	}

	return 0;
}
