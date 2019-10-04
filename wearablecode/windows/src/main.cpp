#include <iostream>
#include <winsock2.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include "modules\edata\Global.cpp"
#include "modules\socket\SocketServer.cpp"
#include "modules\my_algo\v3\MyAlgo.cpp"

using namespace std;
using Json = nlohmann::json;

int main()
{
	gb_setCurrentEnvirnoment(GB_ENV_PRODUCTION);
	SocketServer ss;
	// SocketServer::Instance().startBackend();
	return 0;
}