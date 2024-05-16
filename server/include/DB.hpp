#pragma once

#include<iostream>
#include<pqxx/pqxx>

struct command{
        int userID;
        std::string action;
};


class DB
{
private:
	pqxx::connection *c;
public:
	DB(); 
	void test();
	pqxx::connection* getCon();
	static std::string select_from_chat(command* cmd, pqxx::connection* c);
};  




