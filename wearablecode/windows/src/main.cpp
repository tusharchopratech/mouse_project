#include <iostream>
#include <winsock2.h>
#include <stdio.h>
#include <chrono>

#include "modules\m_daq\MDaq.hpp"
#include "modules\mouse\MouseFunctions.hpp"
#include "modules\socket\socket_server.hpp"
#include "modules\filter\Filter.hpp"

using namespace std;
using namespace std::chrono;

int main()
{
	int totalNumberOfSamples = 20;

	setupFilter();
	setupDaqCard(totalNumberOfSamples);
	setupMouseMonitoring(totalNumberOfSamples);
	setupSocket(totalNumberOfSamples);
	return 0;
}
