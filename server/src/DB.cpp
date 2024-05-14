#include "DB.hpp"

//DB* DB::p_instance = nullptr;
pqxx::connection* DB::c = nullptr;

DB::DB()
{
    /*
    assert(p_instance == nullptr);
    p_instance = this;
    */
    DB::connect();
    std::cout << "[SUCCESS] DB INITIALIZED" << std::endl;
}

DB::~DB()
{
    disconnect();
    delete DB::c;
}

void DB::connect(){
    try{
        DB::c = new pqxx::connection("host=217.197.240.93 user=nyashka password=cmd dbname = chat port=5432");
        std::cout << "[SUCCESS] DB CONNECTED" << std::endl;
    }
    catch(std::exception const &e){
        std::cerr << e.what() << std::endl;
    }
}

void DB::disconnect(){
    c->close();
}

std::string DB::select_from_chat(command* cmd){
    std::cout << "Starting receive process" << std::endl;
    std::string result = "err";
    try{
        pqxx::connection* conn = DB::getConnection();
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
DB *DB::getInstance() {
    if(!DB::p_instance)           
        p_instance = new DB();
    return DB::p_instance;
}
*/

pqxx::connection* DB::getConnection(){
    return c;
}

std::vector<std::string> DB::splitMessage(std::string s, std::string delimiter) {
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

std::string DB::messageManager(std::string message){
    std::vector<std::string> temp = DB::splitMessage(message);
    command* cmd = new command;

    cmd->userID=stoi(temp[0]);
    cmd->action=temp[1];
    std::cout << cmd->userID << std::endl;
    std::cout << cmd->action << std::endl;

    std::string response = DB::select_from_chat(cmd);
    delete cmd;

    return response;
}


