#pragma once

#include <iostream>
#include <pqxx/pqxx>
#include <assert.h>
#include <string>
#include <vector>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

struct command{
    int userID;
    std::string action;
};

class DBManager
{
private:
    pqxx::connection *c;
    void connect();    
    void disconnect();
public:
    DBManager(); 
    ~DBManager();



    pqxx::connection* getConnection() {return c;}

    std::string selectFromChat(command* cmd);
    void registrationRequest(std::string NAVERNO_JSON);

    //tools
    std::vector<std::string> splitMessage(std::string s, std::string delimeter = ";");
    std::string messageManager(std::string message);
    std::string parseJSON_to_string(const std::string& file_name);
};

