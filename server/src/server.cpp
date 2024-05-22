#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <string>
#include "nlohmann/json.hpp"
#include "../include/DBManager.hpp"
#include "version.h"

using tcp = boost::asio::ip::tcp;



std::string JSON_to_string(const std::string& file_name);
inline void startMessage();

struct ParceServerJson
{
	std::string ipAddress = "0.0.0.0";
	unsigned short port = 8080;

	ParceServerJson()
	{
		try{
			std::string json_data = JSON_to_string("server_data/serveraddress.json"); 
			Json serverJSON = Json::parse(json_data);
			
			ipAddress = serverJSON["ipAddress"].get<std::string>();
			port = (int)serverJSON["port"];
			std::cout << ipAddress << ":" << port << std::endl;
		}
			catch(std::exception const &e){
			std::cerr << "НЕ ПОЛУЧИЛОСЬ СПРАСИТЬ serveraddress.json "<< e.what() << std::endl;
		}
	}	
};


int main() {
    try {
		startMessage();
		ParceServerJson parcedServerJson; 

        auto const address = boost::asio::ip::make_address(parcedServerJson.ipAddress);
        auto const port = parcedServerJson.port;

        boost::asio::io_context ioc{1};

        tcp::acceptor acceptor{ioc, {address, port}};
        
        while(true){
			tcp::socket socket{ioc};
			acceptor.accept(socket);
			std::cout << "socket connected" << std::endl;
			try{
			std::thread{
				[socket{std::move(socket)}](){
					boost::beast::websocket::stream<tcp::socket> ws {std::move(const_cast<tcp::socket&>(socket))};
					DBManager* ClientDB = new DBManager();
					ws.accept();
					
					while(true){
						try{
							
							boost::beast::flat_buffer buffer;
							ws.read(buffer);
							auto message = boost::beast::buffers_to_string(buffer.cdata());
							std::cout << message << std::endl;
							std::string answer = ClientDB->Request(message);
							buffer.clear();
							boost::beast::ostream(buffer) << answer;
							//std::cout << boost::beast::buffers_to_string(buffer.cdata())<< "buffffer"<<std::endl;
							ws.write(buffer.data());
							/*
							for (int i = 0; i < 100; i++) {
        						std::cout << boost::beast::buffers_to_string(buffer.data()) << std::endl;
							}
							*/
						}
						catch(boost::beast::system_error const& se){
							if(se.code() != boost::beast::websocket::error::closed){
								std::cout << se.code().message() << std::endl;
								break;
							}
						}
					}
					delete ClientDB;
				} 
          	}.detach();
			}
			catch(std::exception& e){}
        }

    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}



std::string JSON_to_string(const std::string& file_name){
    std::ifstream file(file_name);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    std::stringstream buffer;
        buffer << file.rdbuf();
        std::string jsonData = buffer.str();

    return jsonData;
}


inline void startMessage()
{
	std::cout << "TCP SERVER BY CYBERCONNECT(c)  VERSION: "<< VERSION_MAJOR << '.' << VERSION_MINOR << '.' << COMMIT_COUT << std::endl;
}


