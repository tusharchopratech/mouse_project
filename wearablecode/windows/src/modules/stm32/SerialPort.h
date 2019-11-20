/*
* Author: Manash Kumar Mandal
* Modified Library introduced in Arduino Playground which does not work
* This works perfectly
* LICENSE: MIT
*/

#ifndef SERIALPORT_H
#define SERIALPORT_H

#define ARDUINO_WAIT_TIME 0
// #define MAX_DATA_LENGTH 8

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class SerialPort
{
private:
    // char *portName = "\\\\.\\COM6";
    string comPort = "\\\\.\\";
    HANDLE handler;
    bool connected;
    COMSTAT status;
    DWORD errors;

public:
    SerialPort();
    ~SerialPort();

    string getSerialCOMport();
    int readSerialPort(unsigned char *buffer, unsigned int buf_size);
    bool writeSerialPort(unsigned char *buffer, unsigned int buf_size);
    bool isConnected();
    void closeSerial();
};

#endif // SERIALPORT_H
