#pragma once

#include <iostream>
#include <pqxx/pqxx>
#include <assert.h>
#include <string>
#include <vector>
#include <fstream>
#include "nlohmann/json.hpp"

using Json = nlohmann::json;

class DBManager
{
private:
    pqxx::connection *c;
    int type = -1;
    std::string login = "";
    std::string password = "";
    std::string message = "";
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
    

    //tools;
    void printUsers();
    void parseJson(std::string request);
    bool checkLogin();
    
    std::string JSON_to_string(const std::string& file_name);

};

