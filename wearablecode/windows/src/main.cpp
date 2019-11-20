#include <iostream>
#include <winsock2.h>
#include <stdio.h>
#include <math.h>
#include <chrono>
#include <thread>
#include "modules\edata\Global.cpp"
#include "modules\socket\SocketServer.cpp"
#include "modules\my_algo\v3\MyAlgo.cpp"

using namespace std;
using Json = nlohmann::json;

void test_filter_code();

int main()
{
	// gb_setCurrentEnvirnoment(GB_ENV_STAGING, GB_HARDWARE_MDAQ);
	gb_setCurrentEnvirnoment(GB_ENV_PRODUCTION, GB_HARDWARE_STM32);
	// MyAlgo myAlgo;
	// myAlgo.getAlgoResults("tushar", 4, 1, 3);
	SocketServer ss;
	return 0;
}
