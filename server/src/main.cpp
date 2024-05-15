#include "../../include/socket/tcpserver.hpp"
#include <iostream>
#include "DBManager.hpp"

using json = nlohmann::json;

int main()
{
    TCPServer<> tcpServer;
	std::cout <<  "fasf" << std::endl;
    tcpServer.onNewConnection = [&](TCPSocket<> *newClient) {
	//DBManager* ClientDBM = new DBManager();
        std::cout << "New client: [" << newClient->remoteAddress() << ":" << newClient->remotePort() << "]" << std::endl;
	DBManager* ClientDBM = new DBManager;
        newClient->onMessageReceived = [newClient, &ClientDBM](std::string message) {
            std::cout << newClient->remoteAddress() << ":" << newClient->remotePort() << " => " << message << std::endl;
            std::string send_m = ClientDBM->messageManager(message);
            newClient->Send(send_m);
        };

        newClient->onSocketClosed = [newClient, &ClientDBM](int errorCode) {
            std::cout << "Socket closed:" << newClient->remoteAddress() << ":" << newClient->remotePort() << " -> " << errorCode << std::endl;
            std::cout << std::flush;
	    delete ClientDBM;
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

