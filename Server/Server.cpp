#include "Server.h"

bool Server::initServer(){
    if(bindingStatus == 0){
        return true;
    }
    else{
        return false;
    }
}

bool Server::beginListening(){
    int listeningStatus = listen(serverFileDiscriptor, 2);
    if(listeningStatus == 0){
        return true;
    }
    else{
        return false;
    }
}

bool Server::acceptClientConnection(struct sockaddr_in client){
    uint32_t clientAddressSize = sizeof(client);
    int connectedClientFileDiscriptor = accept(serverFileDiscriptor, (struct sockaddr *)&client, &clientAddressSize);
    if(connectedClientFileDiscriptor == -1){
        return false;
    }
    clientFileDiscriptor = connectedClientFileDiscriptor;
    return true;
}

int Server::getConnectedClientFileDiscriptor(){
    return clientFileDiscriptor;
}

ssize_t Server::reciveMessage(){
    memset(buffer, 0, sizeof(buffer));
    ssize_t amountRecived = recv(clientFileDiscriptor, buffer, 1024, 0);
    return amountRecived;
}

std::string Server::getBuffer(){
    std::string normalStingBuffer(buffer);
    return normalStingBuffer;
}

