#include "include/tcpserver.hpp"
#include <iostream>
#include "DB.hpp"

//testing

using namespace std;

std::vector<string> split(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}


string messageManager(string message){
	DB db;
	string delimeter = ";";
	vector<string> temp = split(message, delimeter);
	command* cmd = new command;
	cmd->userID=stoi(temp[0]);
	cmd->action=temp[1];
	cout << cmd->userID << endl;
	cout << cmd->action << endl;
	return db.select_from_chat(cmd, db.getCon());
}


int main()
{
    TCPServer<> tcpServer;

    tcpServer.onNewConnection = [&](TCPSocket<> *newClient) {
        cout << "New client: [";
        cout << newClient->remoteAddress() << ":" << newClient->remotePort() << "]" << endl;

        newClient->onMessageReceived = [newClient](string message) {
            cout << newClient->remoteAddress() << ":" << newClient->remotePort() << " => " << message << endl;
	    string send_m = messageManager(message);
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
