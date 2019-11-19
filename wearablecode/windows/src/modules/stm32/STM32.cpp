#ifndef STM32_CPP
#define STM32_CPP
#include "STM32.hpp"

void STM32::setupSerialPort()
{

    channelVoltage1 = new double[GB_TOTAL_NUMBER_OF_SAMPLES];
    channelVoltage2 = new double[GB_TOTAL_NUMBER_OF_SAMPLES];
    channelVoltage3 = new double[GB_TOTAL_NUMBER_OF_SAMPLES];
    channelVoltage4 = new double[GB_TOTAL_NUMBER_OF_SAMPLES];
}

void STM32::startRecordingData()
{
    serialPort = new SerialPort(portName);
    while (!serialPort->isConnected())
    {
        serialPort = new SerialPort(portName);
    }
    if (serialPort->isConnected())
    {
        std::cout << "Connection established at port " << portName << endl;
        writeToSerialPort();
    }
    while (1)
    {
        readFromSerialPort();
    }
}

void STM32::writeToSerialPort()
{
    unsigned char data[] = "0";
    serialPort->writeSerialPort(data, GB_MAX_SERIAL_DATA_BYTES_LENGTH);
}
void STM32::readFromSerialPort()
{
    try
    {
        int readResult = serialPort->readSerialPort(incomingData, GB_MAX_SERIAL_DATA_BYTES_LENGTH);
        for (int i = 0; i < GB_MAX_SERIAL_DATA_BYTES_LENGTH; i++)
        {
            vectorOfBytes.push_back(incomingData[i]);

            if (vectorOfBytes.size() > 12)
            {
                deleteChar = true;
                if ((int)vectorOfBytes.at(0) == 97 && (int)vectorOfBytes.at(1) == 101)
                {
                    double number_1 = vectorOfBytes.at(2) | vectorOfBytes.at(3) << 8;
                    double number_2 = vectorOfBytes.at(4) | vectorOfBytes.at(5) << 8;
                    double number_3 = vectorOfBytes.at(6) | vectorOfBytes.at(7) << 8;
                    double number_4 = vectorOfBytes.at(8) | vectorOfBytes.at(9) << 8;
                    double totalt = vectorOfBytes.at(10) | vectorOfBytes.at(11) << 8;
                    if (totalt == number_1 + number_2 + number_3 + number_4)
                    {
                        // cout << number_1 << " " << number_2 << " " << number_3 << " " << number_4 << " " << endl;
                        //cout <<" readFromSerialPort() "<< rawDataVector.size() << endl;
                        number_1 = 0.00087912 * number_1;
                        number_2 = 0.00087912 * number_2;
                        number_3 = 0.00087912 * number_3;
                        number_4 = 0.00087912 * number_4;
                        // cout << number_1 << " " << number_2 << " " << number_3 << " " << number_4 << endl;

                        channelVoltage1[sampleIndex] = number_1;
                        channelVoltage2[sampleIndex] = number_2;
                        channelVoltage3[sampleIndex] = number_3;
                        channelVoltage4[sampleIndex] = number_4;
                        sampleIndex++;
                        newSampleReceived++;
                        // std::vector<double> tmp;
                        // tmp.push_back(number_1);
                        // tmp.push_back(number_2);
                        // tmp.push_back(number_3);
                        // tmp.push_back(number_4);
                        // rawDataVector.push_back(tmp);

                        vectorOfBytes.erase(vectorOfBytes.begin(), vectorOfBytes.begin() + 12);
                        deleteChar = false;
                        if (sampleIndex == GB_TOTAL_NUMBER_OF_SAMPLES)
                        {
                            sampleIndex = 0;
                        }
                    }
                }
                if (deleteChar == true)
                {
                    vectorOfBytes.erase(vectorOfBytes.begin());
                }
            }
        }
    }
    catch (exception &e)
    {
        cout << e.what() << '\n';
    }
}

std::vector<std::vector<double>> STM32::getNewData()
{
    while (rawDataVector.size() < GB_TOTAL_NUMBER_OF_SAMPLES)
    {
        cout << " getNewData() " << rawDataVector.size() << endl;
    }

    std::vector<std::vector<double>> tmp = rawDataVector;
    rawDataVector.clear();
    return tmp;
}

int STM32::getHowManyNewSamples()
{
    return newSampleReceived;
}
void STM32::setNewSamplesToZero()
{
    newSampleReceived = 0;
}

double STM32::getChannelOneVoltage(int samplePosition)
{
    return channelVoltage1[samplePosition];
}

double STM32::getChannelTwoVoltage(int samplePosition)
{
    return channelVoltage2[samplePosition];
}

double STM32::getChannelThreeVoltage(int samplePosition)
{
    return channelVoltage3[samplePosition];
}

double STM32::getChannelFourVoltage(int samplePosition)
{
    return channelVoltage4[samplePosition];
}

#endif