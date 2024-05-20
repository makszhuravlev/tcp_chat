#pragma once

#include <iostream>
#include <pqxx/pqxx>
#include <assert.h>
#include <string>
#include <vector>
#include <fstream>
#include "nlohmann/json.hpp"

using Json = nlohmann::json;

enum operations {Register = 0, getMessage, sendMessage, chatCreate, listChats, Login};

class DBManager
{
private:
    pqxx::connection *c;
    int type = -1;
    std::string login = "";
    std::string password = "";
    std::string message = "";
    std::string name = "";
    std::string email = "";
    int chat_id = 0;
    int offset = 0;
    std::vector<std::string> members = {};
    void connect();
  
public:

    DBManager();
    ~DBManager();

    std::string Request(std::string request);
    std::string registerRequest();
    std::string sendMessageRequest();
    std::string getMessageRequest();
    std::string checkLoginRequest();
    std::string createChat();
    std::string getChats();

    //tools;
    void printUsers();
    void parseJson(std::string request);
    bool checkLogin();
    
    std::string JSON_to_string(const std::string& file_name);

};







/*


    [
        {"content": "asdfasdf", "chat_id": 4, "author_id": "фыва", "message_id": 44},
        {"content": "asdfasdf", "chat_id": 4, "author_id": "фыва", "message_id": 43},
        {"content": "asdfasdf", "chat_id": 4, "author_id": "фыва", "message_id": 42}
    ]


*/
/*

// create an empty structure (null)
json j;

// add a number that is stored as double (note the implicit conversion of j to an object)
j["pi"] = 3.141;

// add a Boolean that is stored as bool
j["happy"] = true;
*/