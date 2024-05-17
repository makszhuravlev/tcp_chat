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
    int chatID = 0;
    void connect();
  
public:

    DBManager();
    ~DBManager();

    void registerRequest();
    void sendMessageRequest();
    void getMessageRequest();
    std::string Request(std::string request);
    //tools;
    void parseJson(std::string request);
    bool checkLogin()
    {
        return true;
    }
    
    std::string JSON_to_string(const std::string& file_name);

};

