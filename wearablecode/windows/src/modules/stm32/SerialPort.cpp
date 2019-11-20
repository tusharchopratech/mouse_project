/*
* Author: Manash Kumar Mandal
* Modified Library introduced in Arduino Playground which does not work
* This works perfectly
* LICENSE: MIT
*/

#include "SerialPort.h"

SerialPort::SerialPort()
{
    // char *portName;
    comPort += getSerialCOMport();
    this->connected = false;
    this->handler = CreateFileA(static_cast<LPCSTR>(comPort.c_str()),
                                GENERIC_READ | GENERIC_WRITE,
                                0,
                                NULL,
                                OPEN_EXISTING,
                                0,
                                NULL);

    if (this->handler == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
        {
            printf("ERROR: Handle was not attached. Reason: %s not available\n", comPort.c_str());
        }
        else
        {
            printf("ERROR!!!");
        }
    }
    else
    {

        DCB dcbSerialParameters = {0};

        if (!GetCommState(this->handler, &dcbSerialParameters))
        {
            printf("failed to get current serial parameters");
        }
        else
        {
            dcbSerialParameters.BaudRate = 256000;
            dcbSerialParameters.ByteSize = 8;
            dcbSerialParameters.StopBits = ONESTOPBIT;
            dcbSerialParameters.Parity = NOPARITY;
            // dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

            if (!SetCommState(handler, &dcbSerialParameters))
            {
                printf("ALERT: could not set Serial port parameters\n");
            }
            else
            {
                this->connected = true;
                PurgeComm(this->handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
            }
        }
    }
}

SerialPort::~SerialPort()
{
    if (this->connected)
    {
        this->connected = false;
        CloseHandle(this->handler);
    }
}

string SerialPort::getSerialCOMport()
{
    cout<<"Available serial ports :-"<<endl;
    string portName = "";
    char lpTargetPath[5000];      // buffer to store the path of the COMPORTS
    for (int i = 0; i < 255; i++) // checking ports from COM0 to COM255
    {
        std::string str = "COM" + std::to_string(i); // converting to COM0, COM1, COM2
        DWORD test = QueryDosDevice(str.c_str(), lpTargetPath, 5000);
        // Test the return value and error if any
        if (test != 0) //QueryDosDevice returns zero if it didn't find an object
        {
            std::cout << str << " : " << lpTargetPath << std::endl;
            portName = str;
        }
    }
    cout<<"Connecting to Port "<<portName<<" !"<<endl;
    return portName;
}

int SerialPort::readSerialPort(unsigned char *buffer, unsigned int buf_size)
{
    DWORD bytesRead;
    unsigned int toRead = 0;

    //ClearCommError(this->handler, &this->errors, &this->status);
    if (ReadFile(this->handler, buffer, buf_size, &bytesRead, NULL))
    {
        return bytesRead;
    }
    return 0;
}

bool SerialPort::writeSerialPort(unsigned char *buffer, unsigned int buf_size)
{
    DWORD bytesSend;

    if (!WriteFile(this->handler, (void *)buffer, buf_size, &bytesSend, 0))
    {
        ClearCommError(this->handler, &this->errors, &this->status);
        return false;
    }
    else
        return true;
}

bool SerialPort::isConnected()
{
    if (!ClearCommError(this->handler, &this->errors, &this->status))
        this->connected = false;

    return this->connected;
}
// Close Connection
void SerialPort::closeSerial()
{
    CloseHandle(this->handler);
}
