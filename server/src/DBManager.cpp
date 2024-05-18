#include "DBManager.hpp"


void DBManager::connect(){
    try{
        std::string json_data = JSON_to_string("server_data/serverinfo.json"); 
        Json serverJSON = Json::parse(json_data);
        std::string connection_info = "host="+serverJSON["ipAddress"].get<std::string>()+" port="+std::to_string((int)serverJSON["port"])+" user="+serverJSON["username"].get<std::string>()+" password="+serverJSON["password"].get<std::string>()+" dbname="+serverJSON["database"].get<std::string>();
        c = new pqxx::connection(connection_info);
        std::cout << "[SUCCESS] DBManager CONNECTED" << std::endl;
    }
        catch(std::exception const &e){
        std::cerr << e.what() << std::endl;
    }
}


DBManager::DBManager()
{
    connect();
}

DBManager::~DBManager(){
    std::cout << "Disconnecting..." << std::endl;
    std::cout << "DBManager_ID:" << c << std::endl;
    
    if(c != nullptr){ 
        c->close();
        c = nullptr;
    }
}

std::string DBManager::Request(std::string request)
{
    parseJson(request);
    switch(type)
    {
        case 0:
            registerRequest();
            std::cout << "registerRequest: " << login << " : " << password << std::endl;
            break;
        case 1:
            if(checkLogin())
            {
                getMessageRequest();
            }
            break;
        case 2:
            if(checkLogin())
            {
                sendMessageRequest();
            }
        default:
            break;
    }

    return "bruh";

}

void DBManager::registerRequest()
{
    std::cout << "Starting receive process" << std::endl;

    try{
        std::string result = "err";
        pqxx::work w(*c);
        pqxx::result check_login = w.exec("SELECT * FROM users WHERE login='"+login+"';");
        if(check_login.size() == 0){
            std::cout << "Starting registration process..." << std::endl;
            w.exec("INSERT INTO users VALUES ('" + login + "', '" + password + "');");
        }
        else
        {
            std::cout << "Login has been claimed, cancel..." << std::endl;
        }
        w.commit();
    }
    catch(std::exception const &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void DBManager::sendMessageRequest()
{
	std::cout << "Starting sending message..." << std::endl;
	try{
		pqxx::work w(*c);
		std::cout << message << " " << login << " " << chatID << std::endl;
		w.exec_params("INSERT INTO messages(content, author_id, chat_id) VALUES($1, $2, $3);", message, login, chatID);
		w.commit();
	}
	catch(const std::exception& e){
		std::cerr << "Failed to send message: " << e.what() << std::endl;
	}
}
void DBManager::getMessageRequest()
{

}

void DBManager::checkLoginRequest()
{
    std::cout << "Printing all users:" << std::endl;
    try{
        std::string result = "err";
        pqxx::work w(*c);
        pqxx::result result_query = w.exec("SELECT password FROM users WHERE login = '"+ login +"';");
        if(result == password) 
        {
            //return "true";
            std::cout << "password correct" << std::endl;
        }
        {
            std::cout << "password not correct" << std::endl;
        }
        
        w.commit();
    }
    catch(std::exception const &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void DBManager::printUsers()
{
    std::cout << "Printing all users:" << std::endl;
    try{
        std::string result = "err";
        pqxx::work w(*c);
        pqxx::result result_query = w.exec("SELECT * FROM users");
        for(auto res : result_query){
            for(auto r : res){
                std::cout << r << " ";
            }
            std::cout << std::endl;
        }
        w.commit();
    }
    catch(std::exception const &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void DBManager::parseJson(std::string request)
{
    std::cout << "Starting parsing..." << std::endl;
    Json json = Json::parse(request);
    try{login = json["username"].get<std::string>();}catch(std::exception& e){}
    try{password = json["password"].get<std::string>();}catch(std::exception& e){}
    try{message = json["message"].get<std::string>();}catch(std::exception& e){}
    try{chatID = (int)json["chatID"];}catch(std::exception& e){}
    try{type = (int)json["type"];}catch(std::exception& e){}
    
    
    
    std::cout << "Parsing completed" << std::endl;
    std::cout << "Login: " << login << std::endl;
    std::cout << "Password: " << password << std::endl;
    std::cout << "Message: " << message << std::endl;
    std::cout << "ChatID: " << chatID << std::endl;
    std::cout << "type: " << type << std::endl;

}
    
std::string DBManager::JSON_to_string(const std::string& file_name){
    std::ifstream file(file_name);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    std::stringstream buffer;
        buffer << file.rdbuf();
        std::string jsonData = buffer.str();

    return jsonData;
}
