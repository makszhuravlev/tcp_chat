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
    void connect();
  
public:

    DBManager();
    ~DBManager();

    void registerRequest(Json json);
    void sendMessageRequest(Json json);
    void getMessageRequest(Json json);
    std::string Request(std::string request);
    //tools;

    bool checkLogin(const std::string &login, const std::string &password)
    {
        return true;
    }
    
    std::string JSON_to_string(const std::string& file_name);

};

