#pragma once

#include <iostream>
#include <pqxx/pqxx>
#include <assert.h>
#include <string>
#include <vector>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class DBManager
{
private:
    pqxx::connection *c;
    void connect(){
      try{
        std::string json_data = parseJSON_to_string("serverinfo.json"); 
        json serverJSON = json::parse(json_data);
        std::string connection_info = "host="+serverJSON["ipAddress"].get<std::string>()+" port="+std::to_string((int)serverJSON["port"])+" user="+serverJSON["username"].get<std::string>()+" password="+serverJSON["password"].get<std::string>()+" dbname="+serverJSON["database"].get<std::string>();
        c = new pqxx::connection(connection_info);
        std::cout << "[SUCCESS] DBManager CONNECTED" << std::endl;
      }
        catch(std::exception const &e){
        std::cerr << e.what() << std::endl;
      }
    }    
public:
    DBManager()
    {
	    connect();
    }
    ~DBManager(){
        std::cout << c << std::endl;
        if(c != nullptr){
            c->close();
        }
    }
    
    std::string parseJSON_to_string(const std::string& file_name){
        std::ifstream file(file_name);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file");
        }

        std::stringstream buffer;
            buffer << file.rdbuf();
            std::string jsonData = buffer.str();

        return jsonData;
    }
};

