#include <iostream>
#include <winsock2.h>
#include <stdio.h>
#include <math.h>
#include <chrono>
#include <thread>
#include "modules\edata\Global.cpp"
#include "modules\socket\SocketServer.cpp"
#include "modules\my_algo\v3\MyAlgo.cpp"

#include <fstream>

using namespace std;
using Json = nlohmann::json;

int main()
{
	gb_setCurrentEnvirnoment(GB_ENV_PRODUCTION, GB_HARDWARE_STM32);
	// gb_setCurrentEnvirnoment(GB_ENV_PRODUCTION, GB_HARDWARE_STM32);
	// MyAlgo myAlgo;
	// myAlgo.getAlgoResults("tushar", 4, 1, 3);
	SocketServer ss;

	// test_filter_code();
	return 0;
}
