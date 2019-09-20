#include <iostream>
#include <winsock2.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include "modules\edata\Global.cpp"
#include "modules\socket\SocketServer.cpp"

#include "modules\algorithm\MyAlgo.cpp"

using namespace std;
using Json = nlohmann::json;

int main()
{
	gb_setCurrentEnvirnoment(GB_ENV_DEVELOPMENT);
	// SocketServer socketServer;
	MyAlgo myAlgo;
	string result = myAlgo.getAlgoResults("Erik", 4, 14);
	// cout << "\n\n"
	// 	 << result;
	return 0;
}