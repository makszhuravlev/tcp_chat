#include "../include/DB.hpp"
#include <string>


DB::DB()
{
//	c = new pqxx::connection("host=217.197.240.93 user=nyashka password=cmd dbname = chat port=5432");
	std::cout << "[SUCCESS] DB INITIALIZED" << std::endl;
}

pqxx::connection* DB::getCon(){
	return c;
}


pqxx::connection* DB::connect(){
	try{
	pqxx::connection* con = new pqxx::connection("host=217.197.240.93 user=nyashka password=cmd dbname = chat port=5432");
	std::cout << "[SUCCESS] DB CONNECTED" << std::endl;
	return con;
	}
	catch(std::exception const &e){
		std::cerr << e.what() << std::endl;
		return nullptr;
	}
}

/*
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
*/

void DB::disconnect(pqxx::connection* c){
	c->close();
}

std::string DB::select_from_chat(command* cmd){
	pqxx::connection *c = this->connect();
	std::cout << "Starting recieve process" << std::endl;
	{
		try{
		pqxx::work w(*c);
		pqxx::result result = w.exec("SELECT * FROM chats");
		w.commit();
		for(auto res : result){
                                for(auto r : res){
                                        std::cout << r << " ";
                                }
                                std::cout << std::endl;
                        }
		return to_string(result[0][0]);
		}
		catch(std::exception const &e){
			std::cerr << e.what() << std::endl;
			return "err";
		}

	}
	this->disconnect(c);
}
