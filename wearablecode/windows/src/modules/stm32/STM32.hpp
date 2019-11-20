#ifndef STM32_HPP
#define STM32_HPP
#include <atomic>
#include <thread>
#include "..\edata\Global.cpp"
#include "..\pubsub\pubsub.cpp"
#include "SerialPort.cpp"

class STM32
{

private:
    
    // char *portName = "COM5";

    unsigned char incomingData[GB_MAX_SERIAL_DATA_BYTES_LENGTH];
    SerialPort *serialPort;

    std::vector<unsigned char> vectorOfBytes;
    bool deleteChar = true;
    double *channelVoltage1, *channelVoltage2, *channelVoltage3, *channelVoltage4;

    int sampleIndex = 0;
    // int *newSampleReceived;
    int newSampleReceived;
    double number_1, number_2, number_3, number_4, totalt;
    std::vector<double> vectorChannel1, tmp1, tmp2;

    double dataSign = +1;

public:
    STM32()
    {
        setupSerialPort();
    }
    void setupSerialPort();
    void recordSamplesFromSTM32();
    void writeToSerialPort();
    void readFromSerialPort();

    double getChannelOneVoltage(int samplePosition);
    double getChannelTwoVoltage(int samplePosition);
    double getChannelThreeVoltage(int samplePosition);
    double getChannelFourVoltage(int samplePosition);
};

#endif