// TCPClient.cpp
#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>

#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsaData;
    SOCKET clientSocket;
    sockaddr_in serverAddr;

    WSAStartup(MAKEWORD(2, 2), &wsaData);
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(54000);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr); // Use inet_pton here

    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        std::cerr << "Failed to connect to server." << std::endl;
        return 1;
    }

    std::cout << "Enter your name: ";
    std::string name;
    std::getline(std::cin, name);

    // Send the length of the name followed by the name itself
    int nameLength = static_cast<int>(name.length());
    send(clientSocket, (char*)&nameLength, sizeof(nameLength), 0);
    send(clientSocket, name.c_str(), nameLength, 0);

    // Message loop
    while (true)
    {
        std::cout << "Enter a message (type 'exit' to leave): ";
        std::string message;
        std::getline(std::cin, message);

        if (message == "exit")
        {
            send(clientSocket, message.c_str(), message.length(), 0);
            break;
        }

        send(clientSocket, message.c_str(), message.length(), 0);
    }

    std::cout << "Disconnecting from server..." << std::endl;
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
