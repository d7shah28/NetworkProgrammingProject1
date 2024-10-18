// TCPServer.cpp
#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>

#pragma comment(lib, "ws2_32.lib")

void handleClient(SOCKET clientSocket)
{
    char buffer[1024];
    std::string clientName;

    // Get client name
    int nameLength;
    recv(clientSocket, (char*)&nameLength, sizeof(nameLength), 0);
    clientName.resize(nameLength);
    recv(clientSocket, &clientName[0], nameLength, 0);

    std::cout << clientName << " connected!" << std::endl;

    while (true)
    {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

        if (bytesReceived <= 0)
        {
            std::cout << clientName << " has left the chat." << std::endl;
            break;
        }

        buffer[bytesReceived] = '\0'; // Null-terminate the received data
        std::cout << clientName << ": " << buffer << std::endl;

        if (strcmp(buffer, "exit") == 0)
        {
            std::cout << clientName << " has left the chat." << std::endl;
            break;
        }
    }

    closesocket(clientSocket);
}

int main()
{
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    sockaddr_in serverAddr, clientAddr;
    int clientAddrSize = sizeof(clientAddr);

    WSAStartup(MAKEWORD(2, 2), &wsaData);
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(54000);

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, SOMAXCONN);

    std::cout << "Server is listening on port 54000..." << std::endl;

    while (true)
    {
        clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
        if (clientSocket != INVALID_SOCKET)
        {
            std::thread(handleClient, clientSocket).detach(); // Handle client in a new thread
        }
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
