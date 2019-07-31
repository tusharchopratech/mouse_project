#ifndef Global_H
#define Global_H


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



// Training
/*
0 :RAW Signal
1 :TKEO 
2 :Powered 3 TKEO
3 :Filtered TKEO
4 :Powered 3, Filtered, TKEO
 */
static const int ALGO_MODE = 0;

/*
1 : consider positive phase
0 : consider both phase
-1 : consider negative phase
 */
static const int SIGN_FLAG = 1;

#endif