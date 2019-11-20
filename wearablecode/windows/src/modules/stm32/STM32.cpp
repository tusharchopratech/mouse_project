#ifndef STM32_CPP
#define STM32_CPP
#include "STM32.hpp"

void STM32::setupSerialPort()
{

    newSampleReceived = 0;
    channelVoltage1 = new double[GB_TOTAL_NUMBER_OF_SAMPLES];
    channelVoltage2 = new double[GB_TOTAL_NUMBER_OF_SAMPLES];
    channelVoltage3 = new double[GB_TOTAL_NUMBER_OF_SAMPLES];
    channelVoltage4 = new double[GB_TOTAL_NUMBER_OF_SAMPLES];

    if (gb_getCurrentHardwareType() == GB_HARDWARE_STM32)
    {
        serialPort = new SerialPort();
        while (!serialPort->isConnected())
        {
            serialPort = new SerialPort();
        }
        if (serialPort->isConnected())
        {
            std::cout << "Serial port connection done !" << endl;
            // writeToSerialPort();
        }
    }
}

void STM32::recordSamplesFromSTM32()
{
    sampleIndex = 0;
    while (sampleIndex < GB_TOTAL_NUMBER_OF_SAMPLES)
    {
        readFromSerialPort();
    }
    Sleep(3);
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
                        channelVoltage1[sampleIndex] = ((5 * number_1) / 1024.0);
                        channelVoltage2[sampleIndex] = ((5 * number_2) / 1024.0);
                        channelVoltage3[sampleIndex] = ((5 * number_3) / 1024.0);
                        channelVoltage4[sampleIndex] = ((5 * number_4) / 1024.0);
                        sampleIndex++;
                        vectorOfBytes.erase(vectorOfBytes.begin(), vectorOfBytes.begin() + 12);
                        deleteChar = false;
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

double STM32::getChannelOneVoltage(int samplePosition)
{
    // return vectorChannel1.at(samplePosition);
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