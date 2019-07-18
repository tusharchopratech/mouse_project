#include <iostream>
#include <winsock2.h>
#include <stdio.h>
#include <chrono>
#include <thread>

#include "modules\socket\SocketServer.cpp"
// #include "modules\m_daq\MDaq.cpp"

int main()
{

	// FilterTools filterTools;

	// MouseFunctions::Instance().setupMouseMonitoring();
	// MDaq mDaq;
	// std::thread newThread(&MDaq::getVoltageFromChannel, mDaq);
	SocketServer s;
	// GloveTools gt;
	// gt.startTraining();

	// setupDaqCard(totalNumberOfSamples);
	// setupMouseMonitoring(totalNumberOfSamples);
	// setupSocket(totalNumberOfSamples, filterTools);

	return 0;
}
