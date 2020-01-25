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

void test_filter_code();

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

void test_filter_code()
{

	std::string line;
	std::ifstream infile("data_tushar1_C4.txt");
	std::vector<std::vector<double>> d_emg;
	std::vector<std::vector<int>> d_clicks;
	while (std::getline(infile, line))
	{

		std::istringstream iss(line);
		std::string s = line;
		std::string delimiter = " ";
		size_t pos = 0;
		std::string token;
		int i = 0;

		std::vector<double> tmp1;
		std::vector<int> tmp2;

		while ((pos = s.find(delimiter)) != std::string::npos)
		{
			token = s.substr(0, pos);
			// std::cout << token << std::endl;
			s.erase(0, pos + delimiter.length());
			if (i == 0)
			{
				tmp1.push_back(std::stod(token));
			}
			else if (i == 1)
			{
				tmp1.push_back(std::stod(token));
			}
			else if (i == 2)
			{
				tmp1.push_back(std::stod(token));
			}
			else if (i == 3)
			{
				tmp1.push_back(std::stod(token));
				d_emg.push_back(tmp1);
				tmp1.clear();
			}
			else if (i == 4)
			{
				tmp2.push_back(std::stoi(token));
			}
			else if (i == 5)
			{
				tmp2.push_back(std::stoi(token));
			}
			i++;
		}

		tmp2.push_back(std::stoi(s));
		d_clicks.push_back(tmp2);
		tmp2.clear();
	}

	cout << "Reading file done" << endl;
	cout << "Raw Values ";
	for (int i = 0; i < 20; i++)
	{
		cout << d_emg.at(i).at(1) << " ";
	}
	cout << endl;

	std::vector<double> filteredValues;

	double lf = 20;
	double hf = 500;

	const static int order = 5;
	const int band = 10;

	Iir::Butterworth::BandPass<order> f_bp;
	f_bp.setup(order, GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD, (lf + hf) / 2, (hf - lf));
	for (int i = 0; i < d_emg.size(); i++)
	{
		filteredValues.push_back(f_bp.filter(d_emg.at(i).at(1)));
		// cout << filteredValues.at(i) << " ";
	}

	cout << "Band Pass Filtered Values ";
	for (int i = 0; i < 20; i++)
	{
		cout << filteredValues.at(i) << " ";
	}
	cout << endl;

	Iir::RBJ::IIRNotch f_n;
	Iir::Butterworth::BandStop<order> f_bs;
	int notchFreq = 48;
	for (int freq = notchFreq; freq < 500; freq += notchFreq)
	{
		f_n.setup(GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD, freq, 15);
		// f_bs.setup(order, GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD, freq, band);
		for (int i = 0; i < filteredValues.size(); i++)
		{
			filteredValues.at(i) = f_n.filter(filteredValues.at(i));
			// filteredValues.at(i) = f_bs.filter(filteredValues.at(i));
		}
	}

	cout << "Notch Filtered Values ";
	for (int i = 0; i < 20; i++)
	{
		cout << filteredValues.at(i) << " ";
	}
	cout << endl;

	cout << "Writing File" << endl;

	string file = "filtered.csv";
	std::ofstream myfile(file);

	if (myfile.is_open())
	{
		for (int i = 0; i < filteredValues.size(); i++)
		{
			myfile << filteredValues.at(i) << endl;
		}
		myfile.close();
	}
	cout << "File Written" << endl;

	// double test_data[] = {0.08133058, -0.02639811, -0.12893874, -0.9687953, -1.28831922, -1.02433814, -0.63309682, -0.30014496, 0.09811551, 0.54276341, 0.73990997, 0.58457313, 0.60013733, 0.5772488, 0.81345845, 1.01640345, 0.87266346, 0.48661021, 0.28244449, -0.8113222};
	// cout << endl;
}