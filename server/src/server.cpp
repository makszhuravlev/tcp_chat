#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <iostream>
#include <thread>
#include <string>
#include "../include/DBManager.hpp"

using tcp = boost::asio::ip::tcp;

int main() {
    try {
        auto const address = boost::asio::ip::make_address("127.0.0.1");
        auto const port = static_cast<unsigned short>(std::atoi("8080"));

        boost::asio::io_context ioc{1};

        tcp::acceptor acceptor{ioc, {address, port}};
        
        while(true){
			tcp::socket socket{ioc};
			acceptor.accept(socket);
			std::cout << "socket connected" << std::endl;
			DBManager* ClientDB = new DBManager();
			std::thread{
				[socket{std::move(socket)}, &ClientDB](){
					boost::beast::websocket::stream<tcp::socket> ws {std::move(const_cast<tcp::socket&>(socket))};
					
					ws.accept();
					
					while(true){
						try{
							boost::beast::flat_buffer buffer;
							ws.read(buffer);
							auto message = boost::beast::buffers_to_string(buffer.cdata());
							std::cout << message << std::endl;
							ClientDB->Request(message);
							ws.write(buffer.data());
							std::cout << "Disconnecting..." << std::endl;
						}
						catch(boost::beast::system_error const& se){
							if(se.code() != boost::beast::websocket::error::closed){
								std::cout << se.code().message() << std::endl;
								break;
							}
						}
					}
				} 
          	}.detach();
        }

    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

