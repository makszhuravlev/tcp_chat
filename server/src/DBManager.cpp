#include "DBManager.hpp"

//DBManager* DBManager::p_instance = nullptr;
pqxx::connection* DBManager::c = nullptr;

DBManager::DBManager()
{
    /*
    assert(p_instance == nullptr);
    p_instance = this;
    */
    DBManager::connect();
    std::cout << "[SUCCESS] DBManager INITIALIZED" << std::endl;
}

DBManager::~DBManager()
{
    disconnect();
    delete DBManager::c;
}

void DBManager::connect(){
    try{
        DBManager::c = new pqxx::connection("host=217.197.240.93 user=nyashka password=cmd dbname = chat port=5432");
        std::cout << "[SUCCESS] DBManager CONNECTED" << std::endl;
    }
    catch(std::exception const &e){
        std::cerr << e.what() << std::endl;
    }
}

void DBManager::disconnect(){
    c->close();
}

std::string DBManager::select_from_chat(command* cmd){
    std::cout << "Starting receive process" << std::endl;
    std::string result = "err";
    try{
        pqxx::connection* conn = DBManager::getConnection();
        if (conn) {
            pqxx::work w(*conn);
            pqxx::result result_query = w.exec("SELECT * FROM chats");
            w.commit();
        
            for(auto res : result_query)
            {
                for(auto r : res){
                    std::cout << r << " ";
                }
                std::cout << std::endl;
            }
            result = to_string(result_query[0][0]);
        }
        else {
            std::cerr << "Database connection is null." << std::endl;
        }
        return result;
    }
    catch(std::exception const &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return result;
}

/*
DBManager *DBManager::getInstance() {
    if(!DBManager::p_instance)           
        p_instance = new DBManager();
    return DBManager::p_instance;
}
*/

pqxx::connection* DBManager::getConnection(){
    return c;
}

std::vector<std::string> DBManager::splitMessage(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start))!= std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

std::string DBManager::messageManager(std::string message){
    std::vector<std::string> temp = DBManager::splitMessage(message);
    command* cmd = new command;

    cmd->userID=stoi(temp[0]);
    cmd->action=temp[1];
    std::cout << cmd->userID << std::endl;
    std::cout << cmd->action << std::endl;

    std::string response = DBManager::select_from_chat(cmd);
    delete cmd;

    return response;
}


