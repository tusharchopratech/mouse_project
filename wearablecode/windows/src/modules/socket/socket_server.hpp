#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;
// Need to link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

// using namespace std;

WSADATA wsaData;
int iResult;

SOCKET ListenSocket;
SOCKET ClientSocket;

struct addrinfo *result;
struct addrinfo hints;

int iSendResult;
char receivedMessageFromClient[DEFAULT_BUFLEN];
int recvbuflen = DEFAULT_BUFLEN;

float chV1 = 0.0;
float chV2 = 0.0;
float chV3 = 0.0;
float chV4 = 0.0;

string finalSocketData;

string getSocketData()
{

    if (chV1 == 0.0 || chV2 == 0.0 || chV3 == 0.0 || chV4 == 0.0)
    {
        chV1 = getChannelOneVoltage();
        chV2 = getChannelTwoVoltage();
        chV3 = getChannelThreeVoltage();
        chV4 = getChannelFourVoltage();
    }
    else
    {
        while (chV1 == getChannelOneVoltage() || chV2 == getChannelTwoVoltage() || chV3 == getChannelThreeVoltage() || chV4 == getChannelFourVoltage())
        {
        }
        chV1 = getChannelOneVoltage();
        chV2 = getChannelTwoVoltage();
        chV3 = getChannelThreeVoltage();
        chV4 = getChannelFourVoltage();
    }

    string data;
    string chV1S = to_string(chV1);
    string chV2S = to_string(chV2);
    string chV3S = to_string(chV3);
    string chV4S = to_string(chV4);
    string l = to_string(getLeftMouseStatus());
    string r = to_string(getRightMouseStatus());
    data = "{\"type\":\"real_time_data\", \"ch_v1\":" + chV1S + ", \"ch_v2\":" + chV2S + ", \"ch_v3\":" + chV3S + ", \"ch_v4\":" + chV4S + ", \"left_click\":" + l + ", \"right_click\":" + r + "}";
    return data;
}

void startListeningFromSocket()
{
    do
    {
        iResult = recv(ClientSocket, receivedMessageFromClient, DEFAULT_BUFLEN, 0);
        string str(receivedMessageFromClient);
        if (str == "real_time_data")
        {   
            finalSocketData = getSocketData();
            iSendResult = send(ClientSocket, finalSocketData.c_str(), finalSocketData.length(), 0);
        }
    } while (iResult > 0);
}

int __cdecl setupSocket(void)
{

    ListenSocket = INVALID_SOCKET;
    ClientSocket = INVALID_SOCKET;

    result = NULL;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0)
    {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET)
    {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR)
    {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    printf("\n\nReady to connect Socket on port : %s", DEFAULT_PORT);
    printf("\nPlease send connect request and data!!\n\n");
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET)
    {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    // No longer need server socket
    closesocket(ListenSocket);
    startListeningFromSocket();

    return 0;
}
