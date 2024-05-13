#pragma once

#include<iostream>
#include<pqxx/pqxx>

class DB
{
private:
	pqxx::connection *c;
public:
	DB(); 
	void test();
};  




