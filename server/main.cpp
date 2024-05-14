#include "include/tcpserver.hpp"
#include <iostream>
#include "DB.hpp"

//testing

using namespace std;



int main()
{
    DB db;
    TCPServer<> tcpServer;

    tcpServer.onNewConnection = [&](TCPSocket<> *newClient) {
        cout << "New client: [";
        cout << newClient->remoteAddress() << ":" << newClient->remotePort() << "]" << endl;

        newClient->onMessageReceived = [newClient](string message) {
            cout << newClient->remoteAddress() << ":" << newClient->remotePort() << " => " << message << endl;
	    string send_m = DB::getInstance()->messageManager(message);
	    newClient->Send(send_m);
        };

        newClient->onSocketClosed = [newClient](int errorCode) {
            cout << "Socket closed:" << newClient->remoteAddress() << ":" << newClient->remotePort() << " -> " << errorCode << endl;
            cout << flush;
        };
    };

    tcpServer.Bind(8080, [](int errorCode, string errorMessage) {
        cout << errorCode << " : " << errorMessage << endl;
    });

    tcpServer.Listen([](int errorCode, string errorMessage) {
        cout << errorCode << " : " << errorMessage << endl;
    });

    string input;
    getline(cin, input);
    while (input != "exit")
    {
        getline(cin, input);
    }

    tcpServer.Close();

    return 0;
}
