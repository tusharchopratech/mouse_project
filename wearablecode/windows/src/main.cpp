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
	setupDaqCard();
	setupMouseMonitoring();
	setupSocket();
	return 0;
}
