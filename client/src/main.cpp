#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fstream>
#include <arpa/inet.h> // Added for inet_addr and htonl
#include "nlohmann/json.hpp"

using json = nlohmann::json;

std::string receiveDataFromServer(int sockfd) {
    std::string receivedData;

    // Buffer to store the received data
    char buffer[1024] = {0};

    // Receive data from the server
    ssize_t bytesRead = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead > 0) {
        // Null-terminate the received data
        buffer[bytesRead] = '\0';
        receivedData = buffer;
    } else {
        std::cerr << "Failed to receive data" << std::endl;
    }

    return receivedData;
}

std::string parseJSON_to_string(){
    std::ifstream file("client_data/string.json");
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string jsonData = buffer.str();

    return jsonData;
}

int main() 
{ 
    // creating socket 
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0); 

    if (clientSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // specifying address 
    sockaddr_in serverAddress; 
    serverAddress.sin_family = AF_INET; 
    serverAddress.sin_port = htons(8080); 

    // Convert IP address string to network byte order
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0) {
        std::cerr << "Invalid address / Address not supported" << std::endl;
        return 1;
    }

    // sending connection request 
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Failed to connect to server" << std::endl;
        return 1;
    }

    // sending data 
    std::string jsonData = parseJSON_to_string();
    ssize_t bytes_sent = send(clientSocket, jsonData.c_str(), jsonData.length(), 0);
    if (bytes_sent < 0) {
        std::cerr << "Failed to send data" << std::endl;
        return 1;
    } 

    std::string rec_message = receiveDataFromServer(clientSocket);
    std::cout << rec_message << std::endl;
    
	int x;
	std::cin >> x;
    // closing socket 
    close(clientSocket);

    return 0; 
}

