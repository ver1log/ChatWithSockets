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

    struct sockaddr_in clientAddress;
    if(!s.acceptClientConnection(clientAddress)){
        std::cerr << "Server could not accept incoming client";
        return -1;
    }

    std:: cout << "server accpeting clients\n";
    
    
    while(true){
        ssize_t amountRecieved = s.reciveMessage();
        if(amountRecieved > 0)
            std::cout << s.getConnectedClientFileDiscriptor() << ": " << s.getBuffer() << std::endl;
        if(amountRecieved < 0)
            break;
    }


    s.endServer();
    return 0;
}