#pragma once

#include <iostream>
#include <pqxx/pqxx>
#include <assert.h>
#include <string>
#include <vector>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

struct command{
    int userID;
    std::string action;
};

class DBManager
{
private:
    static pqxx::connection *c;
public:
    DBManager(); 
    ~DBManager();
    DBManager( const DBManager& ) = delete;  
    DBManager& operator=( DBManager& ) = delete;

    static void connect();
    static void disconnect();

    //static DBManager * getInstance();
    static pqxx::connection* getConnection();
    static std::string select_from_chat(command* cmd);
    //void test();

    static std::vector<std::string> splitMessage(std::string s, std::string delimeter = ";");
    static std::string messageManager(std::string message);
};

