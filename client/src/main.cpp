// C++ program to illustrate the client application in the 
// socket programming 
#include <cstring> 
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h> 


std::string receiveDataFromServer(int sockfd) {
    std::string receivedData;

    // Buffer to store the received data
    char buffer[1024] = {0};

    // Receive data from the server
    ssize_t bytesRead = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead > 0) {
        // Append the received data to the string
        receivedData.append(buffer, bytesRead);
    } else {
        std::cerr << "Failed to receive data" << std::endl;
    }

    return receivedData;
}


int main() 
{ 
	// creating socket 
	int clientSocket = socket(AF_INET, SOCK_STREAM, 0); 

	// specifying address 
	sockaddr_in serverAddress; 
	serverAddress.sin_family = AF_INET; 
	serverAddress.sin_port = htons(8080); 
	serverAddress.sin_addr.s_addr = INADDR_ANY; 

	// sending connection request 
	connect(clientSocket, (struct sockaddr*)&serverAddress, 
			sizeof(serverAddress)); 

	// sending data 
	const char* message = "1;read"; 
	send(clientSocket, message, strlen(message), 0); 

	
	std::string rec_message = receiveDataFromServer(clientSocket);
	std::cout << rec_message << std::endl;
	
	// closing socket 
	close(clientSocket);

	return 0; 
}
