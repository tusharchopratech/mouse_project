#include <iostream>
#include <winsock2.h>
#include <stdio.h>
#include <chrono>

#include "modules\m_daq\MDaq.hpp"
#include "modules\mouse\MouseFunctions.hpp"
#include "modules\socket\socket_server.hpp"

using namespace std;
using namespace std::chrono;

int main()
{

	// float chV1 = 0.0;
	// float chV2 = 0.0;
	// float chV3 = 0.0;
	// float chV4 = 0.0;

	setupDaqCard();
	setupMouseMonitoring();
	setupSocket();
	

	// cout<<getSocketData();
	// while (1)
	// {

	// 	if (chV1 != getChannelOneVoltage() && chV2 != getChannelTwoVoltage() && chV3 != getChannelThreeVoltage() && chV4 != getChannelFourVoltage())
	// 	{
	// 		chV1 = getChannelOneVoltage();
	// 		chV2 = getChannelTwoVoltage();
	// 		chV3 = getChannelThreeVoltage();
	// 		chV4 = getChannelFourVoltage();
	// 		printf("Channel(11) Data: %10.8f\n", getChannelOneVoltage());
	// 		printf("Channel(12) Data: %10.8f\n", getChannelTwoVoltage());
	// 		printf("Channel(13) Data: %10.8f\n", getChannelThreeVoltage());
	// 		printf("Channel(14) Data: %10.8f\n", getChannelFourVoltage());
	// 		printf("Left Mouse Click Status: %d\n", getLeftMouseStatus());
	// 		printf("Right Mouse Click Status: %d\n", getRightMouseStatus());
	// 		// 	mouseEvent('r','d');
	// 		// 	mouseEvent('r','u');
	// 		cout << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() << "\n\n";
	// 	}

	// }

	

	return 0;
}
