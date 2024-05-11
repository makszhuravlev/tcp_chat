#include<iostream>
#include<pqxx/pqxx>


int main()
{
    try
    {
        pqxx::connection c;
        pqxx::work w(c);

        pqxx::row r = w.exec1("SELECT 1");

        w.commit();

        std::cout << r[0].as<int>() << std::endl;
    }
    catch (std::exception const &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}