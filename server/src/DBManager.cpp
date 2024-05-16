#include "DBManager.hpp"


void DBManager::connect(){
    try{
        std::string json_data = JSON_to_string("serverinfo.json"); 
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
    std::cout << "DBManager_ID:" << c << std::endl;
    if(c != nullptr){
        c->close();
    }
}

std::string DBManager::Request(std::string request)
{
    Json json = Json::parse(request);
    std::string login = json["login"].get<std::string>();
    std::string password = json["password"].get<std::string>();
    switch((int)json["type"])
    {
        case 0:
            registerRequest(json);
            std::cout << "registerRequest: " << login << " : " << password << std::endl;
            break;
        case 1:
            if(checkLogin(login,  password))
            {
                void getMessageRequest(Json json);
            }
            break;
        case 2:
            if(checkLogin(login,  password))
            {
                void sendMessageRequest(Json json);
            }
        default:
            break;
    }

    return "brah";

}

void DBManager::registerRequest(Json json)
{

}
void DBManager::sendMessageRequest(Json json)
{

}
void DBManager::getMessageRequest(Json json)
{

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
