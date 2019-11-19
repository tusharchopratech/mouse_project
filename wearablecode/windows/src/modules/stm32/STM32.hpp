#ifndef STM32_H
#define STM32_H
#include "..\edata\Global.cpp"
#include "SerialPort.cpp"

class STM32
{

private:
    char *portName = "\\\\.\\COM3";
    // char *portName = "COM5";

    unsigned char incomingData[GB_MAX_SERIAL_DATA_BYTES_LENGTH];
    SerialPort *serialPort;

    std::vector<unsigned char> vectorOfBytes;
    bool deleteChar = true;
    double *channelVoltage1, *channelVoltage2, *channelVoltage3, *channelVoltage4;
    std::vector<std::vector<double>> rawDataVector;
    int sampleIndex = 0;
    int newSampleReceived = 0;
public:
    STM32()
    {
        setupSerialPort();
    }
    void setupSerialPort();
    void startRecordingData();
    void writeToSerialPort();
    void readFromSerialPort();

     std::vector<std::vector<double>> getNewData();
    int getHowManyNewSamples();
    void setNewSamplesToZero();

    double getChannelOneVoltage(int samplePosition);
    double getChannelTwoVoltage(int samplePosition);
    double getChannelThreeVoltage(int samplePosition);
    double getChannelFourVoltage(int samplePosition);
};

#endif