#include "DBManager.hpp"


using json = nlohmann::json;


DBManager::DBManager()
{
	connect();
}

DBManager::~DBManager()
{
    c->close();
    //disconnect();
}


void DBManager::connect(){
    try{
	std::string json_data = parseJSON_to_string(SERVERINFOJSON_PATH); 
	json serverJSON = json::parse(json_data);
	std::string connection_info = "host="+serverJSON["ipAddress"].get<std::string>()+" port="+std::to_string((int)serverJSON["port"])+" user="+serverJSON["username"].get<std::string>()+" password="+serverJSON["password"].get<std::string>()+" dbname="+serverJSON["database"].get<std::string>();
        c = new pqxx::connection(connection_info);
        std::cout << "[SUCCESS] DBManager CONNECTED" << std::endl;
    }
    catch(std::exception const &e){
        std::cerr << e.what() << std::endl;
    }
}

void DBManager::disconnect(){
    try{
    //c->close();
    }
    catch(std::exception const &e){
	std::cerr << e.what() << std::endl;
    }
    std::cout << "[SUCCESS] DBManager DISCONNECTED" << std::endl;
}


std::string DBManager::selectFromChat(command* cmd){
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
    json recieved_json = json::parse(message);
    double pi = recieved_json["pi"];
    std::string response = std::to_string((double)recieved_json["pi"]);
    //std::to_string(pi);
    return response;
}


std::string DBManager::parseJSON_to_string(const std::string& file_name){
	std::ifstream file(file_name);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file");
        }

	std::stringstream buffer;
        buffer << file.rdbuf();
        std::string jsonData = buffer.str();

	return jsonData;
}
