/*
 * main.c
 *
 *  Created on: 2019-05-16
 *      Author: tushar
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "modules/m_daq/MDaq.hpp"

using namespace std;

int main()
{
	MDaq mDaq;
	mDaq.functionOne();
	while (1)
	{	
		printf("Channel(10) Data: %10.6f\n", mDaq.getVoltageFromChannel(10));
		printf("Channel(11) Data: %10.6f\n", mDaq.getVoltageFromChannel(11));
		printf("Channel(12) Data: %10.6f\n", mDaq.getVoltageFromChannel(12));
		printf("Channel(13) Data: %10.6f\n", mDaq.getVoltageFromChannel(13));
		printf("Channel(14) Data: %10.6f\n", mDaq.getVoltageFromChannel(14));
	}
	return 0;
}
