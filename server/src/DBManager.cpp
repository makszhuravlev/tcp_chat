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
    std::string answer="empty";
    switch(type)
    {
        case Register:		// 0
            answer = registerRequest();
            std::cout << "registerRequest: " << login << " : " << password << std::endl;
            break;
        case getMessage:	// 1
            if(checkLogin())
            {
                answer = getMessageRequest();
            }
            break;
        case sendMessage: 	// 2
            if(checkLogin())
            {
                answer = sendMessageRequest();
            }
	    break;
        case chatCreate:   // 3
            if(checkLogin())
            {
                answer = createChat();
            }
            break;
        case listChats:     // 4
            if(checkLogin())
            {
                answer = getChats();
            }
        case Login:         // 5
            std::cout << "Login request: " << login << " : " << password << std::endl;
            return checkLoginRequest();

            default:
                return "Инвалид-запрос;(";
                break;
    }

    return answer;

}

std::string DBManager::getChats(){
	std::cout << "Starting getting chats by id..." << std::endl;
	try{
		pqxx::work w(*c);
		pqxx::result chats = w.exec_params("SELECT * FROM chats WHERE $1 = ANY(members)", login);
		for(auto row : chats){
			for(auto r : row){
				std::cout << r << " ";
			}
			std::cout << std::endl;
		}
	}
	catch(std::exception& e){
		std::cerr << e.what() << std::endl;
	}
	return "null";
}

std::string DBManager::registerRequest()
{
    std::cout << "Starting receive process" << std::endl;

    try{
        std::string result = "err";
        pqxx::work w(*c);
        pqxx::result check_login = w.exec("SELECT * FROM users WHERE login='"+login+"';");
        if(check_login.size() == 0){
            std::cout << "Starting registration process..." << std::endl;
            w.exec("INSERT INTO users VALUES ('" + login + "', '" + password + "');");
            return "true";
        }
        else
        {
            std::cout << "Login has been claimed, cancel..." << std::endl;
            return "false";
        }
        w.commit();
    }
    catch(std::exception const &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return "BRUH";
}

std::string DBManager::sendMessageRequest()
{
	std::cout << "Starting sending message..." << std::endl;
	try{
		pqxx::work w(*c);
		std::cout << message << " " << login << " " << chat_id << std::endl;
		w.exec_params("INSERT INTO messages(content, author_id, chat_id) VALUES($1, $2, $3);", message, login, chat_id);
		w.commit();
	}
	catch(const std::exception& e){
		std::cerr << "Failed to send message: " << e.what() << std::endl;
	}
    return "NOT READY";
    
}
std::string DBManager::getMessageRequest()
{   
    std::cout << "Starting getting messages..." << std::endl;
    try{
    pqxx::work w(*c);
    pqxx::result chat_messages = w.exec_params("SELECT content FROM messages WHERE chat_id = $1 LIMIT 100 OFFSET $2;", chat_id, offset * 100);

    for(auto row : chat_messages){
        Json jsonmessage;
	    std::cout << row[0] << std::endl;
    }

    w.commit();
    }catch(std::exception& e){}
    return "NOT READY";
}

std::string DBManager::createChat()
{
	std::cout << "Creating chat..." << std::endl;
	try{
		pqxx::work w(*c);
		std::string members_to_str = "";
		for(auto member : members){
			members_to_str += "'" + member + "', ";
		}
		members_to_str.pop_back();
		members_to_str.pop_back();
		std::cout << members_to_str << std::endl;
		w.exec("INSERT INTO chats(members) VALUES(ARRAY[ " + members_to_str + "]);");
		w.commit();
	}catch(std::exception& e){}
	return "null";
}

std::string DBManager::checkLoginRequest()
{
    std::cout << "CheckLoginRequest:" << std::endl;
    try{
        std::string result = "err";
        pqxx::work w(*c);
        pqxx::result result_query = w.exec("SELECT password FROM users WHERE login = '"+ login +"';");
        if(result == password) 
        {
            std::cout << "password correct" << std::endl;
            return "true";
        }
        {
            std::cout << "password not correct" << std::endl;
            return "false";
        }
        
        w.commit();
    }
    catch(std::exception const &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return "BRUH";
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
    try{chat_id = (int)json["chatID"];}catch(std::exception& e){}
    try{type = (int)json["type"];}catch(std::exception& e){}
    try{offset = (int)json["offset"];}catch(std::exception& e){}
    try{
        members = {};
        if (json.contains("members") && json["members"].is_array()) {
        const Json& membersArray = json["members"];

        for (const auto& member : membersArray) {
            members.push_back(member.get<std::string>());
        }
        }
    }catch(std::exception& e){}
    
    
    std::cout << "Parsing completed" << std::endl;
    std::cout << "Login: " << login << std::endl;
    std::cout << "Password: " << password << std::endl;
    std::cout << "Message: " << message << std::endl;
    std::cout << "ChatID: " << chat_id << std::endl;
    std::cout << "type: " << type << std::endl;
    std::cout << "offset: " << offset << std::endl;
}

bool DBManager::checkLogin()
{
    return true;
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
