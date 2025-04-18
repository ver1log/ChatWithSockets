#include <iostream>
#include "Server.h"


int main(int argc, char* argv[]){
    if(argc < 3){
        std::cerr<< "Not enough arguments passed in\n";
    }
    std::string serverAddress = argv[1];
    int serverPort = atoi(argv[2]);

    Server s(serverAddress, serverPort);
    if(!s.initServer()){
        std::cerr << "Error initializing server";
        return -1;
    }
    std:: cout << "server initialized\n";
    if(!s.beginListening()){
        std::cerr << "Server could not begin listening to incoming connections";
        return -1;
    }

    std:: cout << "server listening\n";

    while(true){
        struct sockaddr_in clientAddress;
        AcceptedSocket* client = s.acceptClientConnection(clientAddress);
        //will not add a socket to list if the client could not be connected
        if(!s.addAcceptedSocketToList(client)){
            std::cerr << "Server could not accept incomming socket: " << client->acceptedSocketFD << std::endl; 
            return -1;
        }
        s.printAcceptedClientOnNewThread();
    }

    return 0;
}