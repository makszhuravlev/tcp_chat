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
	pqxx::connection* connect();
	void disconnect(pqxx::connection* c);
	std::string select_from_chat(command* cmd, pqxx::connection* c);
	std::string select_from_chat(command* cmd);
};  




