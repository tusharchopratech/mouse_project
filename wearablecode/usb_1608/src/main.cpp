/*
 * main.c
 *
 *  Created on: 2019-05-16
 *      Author: tushar
 */
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <chrono>
#include <stdlib.h>
#include "modules/m_daq/MDaq.hpp"

using namespace std;
using namespace std::chrono;

int main()
{
	MDaq mDaq;
	mDaq.functionOne();
	std::time_t result = std::time(nullptr);
	cout << result << endl;

	cout<<duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count()<<endl;
	// for (int i = 0; i < 1; i++)
	// {
		// printf("Channel(10) Data: %10.6f\n", mDaq.getVoltageFromChannel(10));
		while(1){
			
		printf("Channel(11) Data: %10.6f\n", mDaq.getVoltageFromChannel(11));
		printf("Channel(12) Data: %10.12f\n", mDaq.getVoltageFromChannel(12));
		printf("Channel(13) Data: %10.6f\n", mDaq.getVoltageFromChannel(13));
		printf("Channel(14) Data: %10.6f\n", mDaq.getVoltageFromChannel(14));
		cout<<duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count()<<"\n\n\n";
		}

		// mDaq.getVoltageFromChannel(4);
		// mDaq.getVoltageFromChannel(11);
		// mDaq.getVoltageFromChannel(12);
		// mDaq.getVoltageFromChannel(13);
		// mDaq.getVoltageFromChannel(14);
	// }
	
	// cout << std::time(nullptr) << endl;
	// cout << std::time(nullptr) - result << endl;

	return 0;
}
