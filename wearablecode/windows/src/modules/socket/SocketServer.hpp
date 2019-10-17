#ifndef SocketServer_HPP
#define SocketServer_HPP

#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "..\glove_tools\GloveTools.cpp"
#include "..\edata\Global.cpp"
#include "..\edata\json\json.hpp"

using Json = nlohmann::json;
using namespace std;

// Need to link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

class SocketServer 
{
private:
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket;
    SOCKET ClientSocket;

    struct addrinfo *result;
    struct addrinfo hints;

    int iSendResult;
    char receivedMessageFromClient[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    
    bool isRealTimeRunning = false; 
    bool isTrainingRunning = false;
    GloveTools gloveTools;

public:

    SocketServer()
    {     
        setupSocket();
        startListeningFromSocket();
    }
    void startBackend();
    int __cdecl setupSocket();
    void startListeningFromSocket();
    void sendRealTimeLogs();
    void sendRealTimeTrainingData();
};

#endif