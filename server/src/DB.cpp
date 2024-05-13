#include "../include/DB.hpp"

DB::DB()
{
	c = new pqxx::connection("host=217.197.240.93 user=nyashka password=cmd dbname = chat port=5432");
}