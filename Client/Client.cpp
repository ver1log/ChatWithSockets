#include "Client.h"

bool Client::connectToServer(){
    if(connectionStatus == 0){
        std::cout<<"inside connectTOsever\n";
        return true;
    }
    else{
        return false;
    }
}

ssize_t Client::sendMessage(std::string line){
    std::string message = line;
    ssize_t amountSent = send(socketFileDiscriptor, message.c_str(), strlen(message.c_str()),0);
    return amountSent;
}

void Client::reciveMessage(){
    memset(buffer, 0, sizeof(buffer));
    recv(socketFileDiscriptor,buffer, 1024, 0);
}

char* Client::getBuffer(){
    return buffer;
}