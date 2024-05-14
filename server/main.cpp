#include "include/tcpserver.hpp"
#include <iostream>
#include "DBManager.hpp"


int main()
{
    //DBManager db;
    DBManager::connect();
    TCPServer<> tcpServer;

    tcpServer.onNewConnection = [&](TCPSocket<> *newClient) {
        std::cout << "New client: [" << newClient->remoteAddress() << ":" << newClient->remotePort() << "]" << std::endl;

        newClient->onMessageReceived = [newClient](std::string message) {
            std::cout << newClient->remoteAddress() << ":" << newClient->remotePort() << " => " << message << std::endl;
            std::string send_m = DBManager::messageManager(message);
            newClient->Send(send_m);
        };

        newClient->onSocketClosed = [newClient](int errorCode) {
            std::cout << "Socket closed:" << newClient->remoteAddress() << ":" << newClient->remotePort() << " -> " << errorCode << std::endl;
            std::cout << std::flush;
        };
    };

    tcpServer.Bind(8080, [](int errorCode, std::string errorMessage) {
        std::cout << errorCode << " : " << errorMessage << std::endl;
    });

    tcpServer.Listen([](int errorCode, std::string errorMessage) {
        std::cout << errorCode << " : " << errorMessage << std::endl;
    });

    std::string input;
    getline(std::cin, input);
    while (input!= "exit")
    {
        getline(std::cin, input);
    }

    tcpServer.Close();

    return 0;
}

