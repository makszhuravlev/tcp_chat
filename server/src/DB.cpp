#include "DB.hpp"

DB* DB::p_instance = nullptr;

DB::DB()
{
	assert(p_instance == nullptr);
    p_instance = this;
	std::cout << "[SUCCESS] DB INITIALIZED" << std::endl;
}

DB::~DB()
{
	disconnect();
	delete c;
}




void DB::connect(){
	try{
		c = new pqxx::connection("host=217.197.240.93 user=nyashka password=cmd dbname = chat port=5432");
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
	std::cout << "Starting recieve process" << std::endl;
	{
		try{
			pqxx::work w(*c);
			pqxx::result result = w.exec("SELECT * FROM chats");
			w.commit();
			for(auto res : result)
			{
				for(auto r : res){
						std::cout << r << " ";
				}
				std::cout << std::endl;
			}
			return to_string(result[0][0]);
		}
		catch(std::exception const &e)
		{
			std::cerr << e.what() << std::endl;
			return "err";
		}

	}
}

DB *DB::getInstance() {
	// if(!DB::p_instance)           
		p_instance = new DB();
	return DB::p_instance;
}

pqxx::connection* DB::getConnection(){
	return c;
}

std::string select_from_chat(command* cmd, pqxx::connection* c)
{
	return "SVO!!!";
}

void DB::test(){
	std::cout << "test" << std::endl;
	{
		try
		{
			pqxx::work w(*c);
			pqxx::result result = w.exec("SELECT * FROM chats");
			w.commit();
			for(auto res : result){
				for(auto r : res){
					std::cout << r << " ";
				}
				std::cout << std::endl;
			}
		}
		catch (std::exception const &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}

}

std::vector<std::string> DB::splitMessage(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}


std::string DB::messageManager(std::string message){
	DB *db = DB::getInstance();

	//std::string delimeter = ";";
	std::vector<std::string> temp = db->splitMessage(message/*, delimeter*/);
	command* cmd = new command;	//	Удалить 

	cmd->userID=stoi(temp[0]);
	cmd->action=temp[1];
	std::cout << cmd->userID << std::endl;
	std::cout << cmd->action << std::endl;

	return db->select_from_chat(cmd);
}
