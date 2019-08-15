#include <iostream>
#include <winsock2.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include "modules\edata\Global.cpp"
#include "modules\socket\SocketServer.cpp"
// #include "modules\algorithm\MyAlgo.hpp"

using namespace std;

int main()
{
	gb_setCurrentEnvirnoment(GB_ENV_STAGING);
	SocketServer socketServer;
	// MyAlgo M;
	return 0;
}
