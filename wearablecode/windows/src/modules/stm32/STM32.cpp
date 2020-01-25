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

    f_bp_1.setup(order, GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD, (lf + hf) / 2, (hf - lf));
    f_bp_2.setup(order, GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD, (lf + hf) / 2, (hf - lf));
    f_bp_3.setup(order, GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD, (lf + hf) / 2, (hf - lf));
    f_bp_4.setup(order, GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD, (lf + hf) / 2, (hf - lf));

    int i = 0;
    // for (int freq = notchFreq; freq < 500; freq += notchFreq)
    // {
    //     f_n_1[i].setup(GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD, freq, 15);
    //     f_n_2[i].setup(GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD, freq, 15);
    //     f_n_3[i].setup(GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD, freq, 15);
    //     f_n_4[i].setup(GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD, freq, 15);
    //     i++;
    // }

    i = 0;
    for (int freq = notchFreq; freq < 500; freq += notchFreq)
    {
        f_bs_1[i].setup(order, GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD, freq, band);
        f_bs_2[i].setup(order, GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD, freq, band);
        f_bs_3[i].setup(order, GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD, freq, band);
        f_bs_4[i].setup(order, GB_SAMPLING_RATE_OF_FILTER_AND_DAQ_CARD, freq, band);
        i++;
    }

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
                        number_1 = ((5 * number_1) / 1024.0);
                        number_2 = ((5 * number_2) / 1024.0);
                        number_3 = ((5 * number_3) / 1024.0);
                        number_4 = ((5 * number_4) / 1024.0);

                        number_1 = f_bp_1.filter(number_1);
                        number_2 = f_bp_2.filter(number_2);
                        number_3 = f_bp_3.filter(number_3);
                        number_4 = f_bp_4.filter(number_4);

                        // for (int i = 0; i < 10; i++)
                        // {
                        //     number_1 = f_n_1[i].filter(number_1);
                        //     number_2 = f_n_2[i].filter(number_2);
                        //     number_3 = f_n_3[i].filter(number_3);
                        //     number_4 = f_n_4[i].filter(number_4);
                        // }
                        int index = 0;
                        for (int freq = notchFreq; freq < 500; freq += notchFreq)
                        {
                            number_1 = f_bs_1[index].filter(number_1);
                            number_2 = f_bs_2[index].filter(number_2);
                            number_3 = f_bs_3[index].filter(number_3);
                            number_4 = f_bs_4[index].filter(number_4);
                            index++;
                        }

                        channelVoltage1[sampleIndex] = number_1;
                        channelVoltage2[sampleIndex] = number_2;
                        channelVoltage3[sampleIndex] = number_3;
                        channelVoltage4[sampleIndex] = number_4;
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