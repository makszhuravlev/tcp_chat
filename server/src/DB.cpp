#include "../include/DB.hpp"

DB::DB()
{
	c = new pqxx::connection("host=217.197.240.93 user=nyashka password=cmd dbname = chat port=5432");
	std::cout << "[SUCCESS] DB CONNECTION" << std::endl;
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
