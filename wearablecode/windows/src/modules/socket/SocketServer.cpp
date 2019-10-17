#ifndef SocketServer_CPP
#define SocketServer_CPP

#include "SocketServer.hpp"
#include <string.h>

void SocketServer::startBackend()
{
    setupSocket();
    startListeningFromSocket();
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

    if (gb_getCurrentEnvirnoment() == GB_ENV_DEVELOPMENT)
    {
        gloveTools.readDemoData();
    }
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
        Json obj = Json::parse(str);
        // cout << obj.dump(2) << endl;
        if (obj["type"] == "message" && obj["value"] == "raw_real_time_data")
        {
            finalSocketData = "";
            if (gb_getCurrentEnvirnoment() == GB_ENV_DEVELOPMENT)
            {
                finalSocketData = gloveTools.getRealTimeRawDemoData();
            }
            else
            {
                finalSocketData = gloveTools.getRealTimeRawData();
            }
            send(ClientSocket, finalSocketData.c_str(), finalSocketData.length(), 0);
        }
        else if (obj["type"] == "message" && obj["value"] == "start_training")
        {
            isTrainingRunning = true;
            gloveTools.startTraining();
            Json json;
            json["type"] = "start_training_success";
            finalSocketData = json.dump();
            send(ClientSocket, finalSocketData.c_str(), static_cast<int>(finalSocketData.length()), 0);
            std::thread newThread(&SocketServer::sendRealTimeTrainingData, this);
            newThread.detach();
        }
        else if (obj["type"] == "message" && obj["value"] == "stop_training")
        {
            isTrainingRunning = false;
            Json json = gloveTools.stopTraining();
            json["type"] = "algo_outputs";
            finalSocketData = json.dump();
            send(ClientSocket, finalSocketData.c_str(), static_cast<int>(finalSocketData.length()), 0);
        }
        else if (obj["type"] == "communication" && obj["value"] == "settings")
        {
            gloveTools.setTrainingSettings(obj["participant_name"], obj["trail_no"], obj["no_of_channels"], obj["click_type"]);
            Json json;
            json["type"] = "communication_success";
            json["value"] = "settings_set";
            finalSocketData = json.dump();
            send(ClientSocket, finalSocketData.c_str(), static_cast<int>(finalSocketData.length()), 0);
        }
        else if (obj["type"] == "message" && obj["value"] == "start_real_time")
        {
            gloveTools.startRealTime(obj["threshold_percentage"]);
            isRealTimeRunning = true;
            Json json;
            json["type"] = "start_real_time_success";
            finalSocketData = json.dump();
            send(ClientSocket, finalSocketData.c_str(), static_cast<int>(finalSocketData.length()), 0);
            std::thread newThread(&SocketServer::sendRealTimeLogs, this);
            newThread.detach();
        }
        else if (obj["type"] == "message" && obj["value"] == "stop_real_time")
        {
            gloveTools.stopRealTime();
            isRealTimeRunning = false;
            Json json;
            json["type"] = "stop_real_time_success";
            finalSocketData = json.dump();
            send(ClientSocket, finalSocketData.c_str(), static_cast<int>(finalSocketData.length()), 0);
        }
    } while (iResult > 0);
}

void SocketServer::sendRealTimeLogs()
{
    string finalSocketData;
    while (isRealTimeRunning)
    {
        Json json = gloveTools.getRealTimeGamePlayDataForDisplay();
        json["type"] = "real_time_logs_and_signals_data";
        finalSocketData = json.dump();
        // cout<<finalSocketData<<endl;
        send(ClientSocket, finalSocketData.c_str(), static_cast<int>(finalSocketData.length()), 0);
        Sleep(100);
    }
}

void SocketServer::sendRealTimeTrainingData()
{
    string finalSocketData;
    while (isTrainingRunning)
    {
        Json json = gloveTools.getRealTimeTraingDataForDisplay();
        json["type"] = "real_time_training_data";
        finalSocketData = json.dump();
        send(ClientSocket, finalSocketData.c_str(), static_cast<int>(finalSocketData.length()), 0);
        Sleep(300);
    }
}

#endif