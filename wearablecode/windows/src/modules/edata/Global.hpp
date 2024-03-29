#ifndef Global_H
#define Global_H
#include <iostream>
#include <iterator>
#include <algorithm>
#include "..\..\..\lib\dlib\all\source.cpp"

using namespace std;

static const int N = 4;

// Global Configurations
static const double GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD = 2048.0;
static const int GB_TOTAL_NUMBER_OF_SAMPLES = 10;

// DAQ card configurations
static const int GB_DAQ_LOWER_CHANNEL_NUMBER = 11;
static const int GB_DAQ_HIGHER_CHANNEL_NUMBER = 14;

// Filter Configurations
static const double GB_FILTER_LOW_FREQUENCY = 110;
static const double GB_FILTER_HIGH_FREQUENCY = 250;
static const int GB_FILTER_ORDER = 3;

//DEBUGGING STAGE, No Hardware, Using Simulated Recordings
static const string GB_ENV_DEVELOPMENT = "development";
//DEBUGGING STAGE, Using Hardware
static const string GB_ENV_STAGING = "staging";
//PRODUCTION STAGE, Using Hardware
static const string GB_ENV_PRODUCTION = "production";

static const string GB_HARDWARE_MDAQ = "mdaq";
static const string GB_HARDWARE_STM32 = "stm32";



static const string GB_IMPULSE_DIRECTORY = "C:/impulse_data_2";
static const string GB_IMPULSE_DEV_DIRECTORY = "./../debug/dataset";

static const double TRUE_POSTIVE_MILLISECONDS_CHECK = 100;
static const double GB_NEXT_SAMPLE_CHECK_AFTER_TRUE_POSITIVE = 100;

static const double GB_DEFAULT_REFRACTORY_PERIOD_IN_MS = 100;
static const double GB_DEFAULT_MAX_LEAD_IN_MS = 200;

static const double GB_TRAINING_WINDOW_INTERVAL_STARTING = 0.75;
static const double GB_TRAINING_WINDOW_INTERVAL_ENDING = 0.35;
static const double GB_CLICK_DETECTION_INTERVAL_STARTING = 0.1;

static const double GB_TRAINING_SAMPLE_TAKEN_FROM_CLASSIFICATION = 0.50;

static const int GB_MAX_SERIAL_DATA_BYTES_LENGTH = 12;

string currentEnvirnoment;
string currentHardwareType;

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