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
	gb_setCurrentEnvirnoment(GB_ENV_STAGING, GB_HARDWARE_STM32);
	test_filter_code();
	SocketServer ss;
	return 0;
}

void test_filter_code()
{

	// double test_data[] = {0.08133058, -0.02639811, -0.12893874, -0.9687953, -1.28831922, -1.02433814, -0.63309682, -0.30014496, 0.09811551, 0.54276341, 0.73990997, 0.58457313, 0.60013733, 0.5772488, 0.81345845, 1.01640345, 0.87266346, 0.48661021, 0.28244449, -0.8113222};
	// double lf = 20;
	// double hf = 500;
	// Iir::Butterworth::BandPass<6> f_bp;
	// f_bp.setup(6, GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD, (lf + hf) / 2, (hf - lf));

	// std::vector<double> filteredValues;
	// for (int i = 0; i < 20; i++)
	// {
	// 	filteredValues.push_back(f_bp.filter(test_data[i]));
	// 	cout << filteredValues.at(i) << " ";
	// }

	// cout << endl;

	// Iir::RBJ::IIRNotch f_n;
	// f_n.setup(GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD, 60.0, 15);
	// for (int i = 0; i < 20; i++)
	// {
	// 	cout << f_n.filter(filteredValues.at(i)) << " ";
	// }
}