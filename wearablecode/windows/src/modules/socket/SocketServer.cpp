#include "SocketServer.hpp"
#include <string.h>

using namespace std::chrono;
void logTime()
{
    cout << "\n"<< duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() << std::flush;
    // printf("\n%ld", duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
}

int __cdecl SocketServer::setupSocket()
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

    return 0;
}

void SocketServer::startListeningFromSocket()
{
    string finalSocketData;
    do
    {
        iResult = recv(ClientSocket, receivedMessageFromClient, DEFAULT_BUFLEN, 0);
        string str(receivedMessageFromClient);
        str = str.substr(0, str.find("*****"));

        if (str == "raw_real_time_data")
        {   
            // logTime();
            finalSocketData = gloveTools.getRealTimeRawData();
            send(ClientSocket, finalSocketData.c_str(), finalSocketData.length(), 0);
        }
        else if (str == "start_training")
        {
            gloveTools.startTraining();
            finalSocketData = "{\"type\":\"start_training_success\"}";
            send(ClientSocket, finalSocketData.c_str(), finalSocketData.length(), 0);
        }
        else if (str == "stop_training")
        {
            gloveTools.stopTraining();
        }
        else if (str == "debugging_real_time_data")
        {
            finalSocketData = gloveTools.getRealTimeDebuggingData();
            send(ClientSocket, finalSocketData.c_str(), finalSocketData.length(), 0);
        }
    } while (iResult > 0);
}