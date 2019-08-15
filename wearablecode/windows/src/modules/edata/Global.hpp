#ifndef Global_H
#define Global_H
#include <iostream>
#include "..\..\..\lib\dlib\all\source.cpp"
using namespace dlib;

using namespace std;

static const int N=4;

// Global Configurations
static const double GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD = 2048;
static const int GB_TOTAL_NUMBER_OF_SAMPLES = 10;

// DAQ card configurations
static const int GB_DAQ_LOWER_CHANNEL_NUMBER = 11;
static const int GB_DAQ_HIGHER_CHANNEL_NUMBER = 14;

// Filter Configurations
static const double GB_FILTER_LOW_FREQUENCY = 110;
static const double GB_FILTER_HIGH_FREQUENCY = 250;
static const int GB_FILTER_ORDER = 5;

static const string GB_ENV_DEVELOPMENT = "development";
static const string GB_ENV_STAGING = "staging";
static const string GB_ENV_PRODUCTION = "production";

static const string GB_IMPULSE_DIRECTORY = "C:/impluse_data";

string currentEnvirnoment; 


// Training
/*
0 :RAW Signal
1 :TKEO 
2 :Powered 3 TKEO
3 :Filtered TKEO
4 :Powered 3, Filtered, TKEO
 */
static const int ALGO_MODE_RAW = 0;
static const int ALGO_MODE_TKEO = 1;
static const int ALGO_MODE_P3_TKEO = 2;
static const int ALGO_MODE_F_TKEO = 3;
static const int ALGO_MODE_P3_F_TKEO = 4;

/*
1 : consider positive phase
0 : consider both phase
-1 : consider negative phase
 */
static const int ALGO_SIGN_FLAG_POS = 1;
static const int ALGO_SIGN_FLAG_BOTH = 0;
static const int ALGO_SIGN_FLAG_NEG = -1;

#endif