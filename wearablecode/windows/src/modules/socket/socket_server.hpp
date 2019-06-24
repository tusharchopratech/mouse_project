#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

#include "..\filter\Filter.hpp"
using namespace std;
// Need to link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;
void logTime()
{
    cout << "\n"
         << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() << std::flush;
    // printf("\n%ld", duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
}

WSADATA wsaData;
int iResult;

SOCKET ListenSocket;
SOCKET ClientSocket;

struct addrinfo *result;
struct addrinfo hints;

int iSendResult;
char receivedMessageFromClient[DEFAULT_BUFLEN];
int recvbuflen = DEFAULT_BUFLEN;

double *chV1, *chV2, *chV3, *chV4;
int *lC, *rC;
int totalNumberOfSamplesForSocketData;
string finalSocketData;

double getTkeoValue(double sample1, double sample2, double sample3)
{
    double v1 = sample1 * sample1 * sample1;
    double v2 = sample2 * sample2 * sample2;
    double v3 = sample3 * sample3 * sample3;
    double result = v2 * v2 - v1 * v3;
    return result;
}

string getSocketData()
{
    if (chV1[0] == 0.0 || chV2[0] == 0.0 || chV3[0] == 0.0 || chV4[0] == 0.0)
    {
    }
    else
    {
        while (chV1[0] == getChannelOneVoltage(0) || chV2[0] == getChannelTwoVoltage(0) || chV3[0] == getChannelThreeVoltage(0) || chV4[0] == getChannelFourVoltage(0))
        {
        }
    }

    string chV1String = "", chV2String = "", chV3String = "", chV4String = "";
    string chV1TkeoString = "", chV2TkeoString = "", chV3TkeoString = "", chV4TkeoString = "";
    string lCString = "", rCString = "";
    double ch1Tkeo, ch2Tkeo, ch3Tkeo, ch4Tkeo;
    for (int i = 0; i < totalNumberOfSamplesForSocketData; i++)
    {
        chV1[i] = getChannelOneVoltage(i);
        chV2[i] = getChannelTwoVoltage(i);
        chV3[i] = getChannelThreeVoltage(i);
        chV4[i] = getChannelFourVoltage(i);
        lC[i] = getLeftMouseStatusAtIndex(i);
        rC[i] = getRightMouseStatusAtIndex(i);

        if (i == totalNumberOfSamplesForSocketData - 1)
        {
            ch1Tkeo = getTkeoValue(chV1[i - 2], chV1[i - 1], chV1[i]);
            ch2Tkeo = getTkeoValue(chV2[i - 2], chV2[i - 1], chV2[i]);
            ch3Tkeo = getTkeoValue(chV3[i - 2], chV3[i - 1], chV3[i]);
            ch4Tkeo = getTkeoValue(chV4[i - 2], chV4[i - 1], chV4[i]);
            chV1TkeoString = chV1TkeoString + "," + to_string(ch1Tkeo) + "," + to_string(ch1Tkeo) + "," + to_string(ch1Tkeo);
            chV2TkeoString = chV2TkeoString + "," + to_string(ch2Tkeo) + "," + to_string(ch2Tkeo) + "," + to_string(ch2Tkeo);
            chV3TkeoString = chV3TkeoString + "," + to_string(ch3Tkeo) + "," + to_string(ch3Tkeo) + "," + to_string(ch3Tkeo);
            chV4TkeoString = chV4TkeoString + "," + to_string(ch4Tkeo) + "," + to_string(ch4Tkeo) + "," + to_string(ch4Tkeo);
        }
        else if (i == 2)
        {
            ch1Tkeo = getTkeoValue(chV1[i - 2], chV1[i - 1], chV1[i]);
            ch2Tkeo = getTkeoValue(chV2[i - 2], chV2[i - 1], chV2[i]);
            ch3Tkeo = getTkeoValue(chV3[i - 2], chV3[i - 1], chV3[i]);
            ch4Tkeo = getTkeoValue(chV4[i - 2], chV4[i - 1], chV4[i]);
            chV1TkeoString = to_string(ch1Tkeo);
            chV2TkeoString = to_string(ch2Tkeo);
            chV3TkeoString = to_string(ch3Tkeo);
            chV4TkeoString = to_string(ch4Tkeo);
        } else  if (i > 2){
            ch1Tkeo = getTkeoValue(chV1[i - 2], chV1[i - 1], chV1[i]);
            ch2Tkeo = getTkeoValue(chV2[i - 2], chV2[i - 1], chV2[i]);
            ch3Tkeo = getTkeoValue(chV3[i - 2], chV3[i - 1], chV3[i]);
            ch4Tkeo = getTkeoValue(chV4[i - 2], chV4[i - 1], chV4[i]);
            chV1TkeoString = chV1TkeoString + "," + to_string(ch1Tkeo);
            chV2TkeoString = chV2TkeoString + "," + to_string(ch2Tkeo);
            chV3TkeoString = chV3TkeoString + "," + to_string(ch3Tkeo);
            chV4TkeoString = chV4TkeoString + "," + to_string(ch4Tkeo);
        }

        if (i == 0)
        {
            chV1String = to_string(chV1[i]);
            chV2String = to_string(chV2[i]);
            chV3String = to_string(chV3[i]);
            chV4String = to_string(chV4[i]);
            lCString = to_string(lC[i]);
            rCString = to_string(rC[i]);
        }
        else
        {
            chV1String = chV1String + "," + to_string(chV1[i]);
            chV2String = chV2String + "," + to_string(chV2[i]);
            chV3String = chV3String + "," + to_string(chV3[i]);
            chV4String = chV4String + "," + to_string(chV4[i]);
            lCString = lCString + "," + to_string(lC[i]);
            rCString = rCString + "," + to_string(rC[i]);
        }
    }

    string l = to_string(getLeftMouseStatus());
    string r = to_string(getRightMouseStatus());
    string data = "{\"type\":\"real_time_data\", \"ch_v1\": [" + chV1String + "]" + ", \"ch_v2\":[" + chV2String + "]" + ", \"ch_v3\":[" + chV3String + "]" + ", \"ch_v4\":[" + chV4String + "]" + ", \"ch_v1_tkeo\": [" + chV1TkeoString + "]" + ", \"ch_v2_tkeo\":[" + chV2TkeoString + "]" + ", \"ch_v3_tkeo\":[" + chV3TkeoString + "]" + ", \"ch_v4_tkeo\":[" + chV4TkeoString + "]" + ", \"left_click\": [" + lCString + "]" + ", \"right_click\": [" + rCString + "]" + "}";
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
            // cout << "\n\n"
                //  << finalSocketData;
            iSendResult = send(ClientSocket, finalSocketData.c_str(), finalSocketData.length(), 0);
            // logTime();
        }
    } while (iResult > 0);
}

int __cdecl setupSocket(int totalSamples)
{
    totalNumberOfSamplesForSocketData = totalSamples;
    chV1 = new double[totalNumberOfSamplesForSocketData];
    chV2 = new double[totalNumberOfSamplesForSocketData];
    chV3 = new double[totalNumberOfSamplesForSocketData];
    chV4 = new double[totalNumberOfSamplesForSocketData];
    lC = new int[totalNumberOfSamplesForSocketData];
    rC = new int[totalNumberOfSamplesForSocketData];

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
    iResult = ::bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
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
