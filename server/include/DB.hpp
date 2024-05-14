#pragma once

#include <iostream>
#include <pqxx/pqxx>
#include <assert.h>
#include <string>
#include <vector>

struct command{
	int userID;
	std::string action;
};

class DB
{
private:
	static DB *p_instance;
	pqxx::connection *c;
public:
	DB(); 
	~DB();
    DB( const DB& ) = delete;  
    DB& operator=( DB& ) = delete;

	void connect();
	void disconnect();

	static DB * getInstance();
	pqxx::connection* getConnection();
	std::string select_from_chat(command* cmd, pqxx::connection* c);
	std::string select_from_chat(command* cmd);
	void test();

	std::vector<std::string> splitMessage(std::string s, std::string delimeter = ";");
	std::string messageManager(std::string message);
};  




