#include <iostream>
#include <boost/asio.hpp>
#include <thread>

using boost::asio::ip::tcp;

void handle_client(tcp::socket& socket) {
    std::string message = "Hello, Client!\r\n";
    boost::asio::write(socket, boost::asio::buffer(message));
    socket.shutdown(tcp::socket::shutdown_both);
}

int main() {
    try {
        boost::asio::io_context io_context;

        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));

        std::cout << "Listening on port 8080..." << std::endl;

        for (;;) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            // Spawn a new thread to handle the client connection
            std::thread client_thread(handle_client, std::ref(socket));
            client_thread.join(); // Wait for the thread to finish
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

