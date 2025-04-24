#include "Client.h"

bool Client::connectToServer()
{
    if (connectionStatus == 0)
    {
        //std::cout << "inside connectTOsever\n";
        return true;
    }
    else
    {
        return false;
    }
}

ssize_t Client::sendMessage(std::string line)
{
    std::string message = line;
    ssize_t amountSent = send(socketFileDiscriptor, message.c_str(), strlen(message.c_str()), 0);
    return amountSent;
}


void Client::reciveMessage()
{
    //memset(buffer, 0, sizeof(buffer));
    char buffer[1024];
    while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        ssize_t amountRecieved = recv(socketFileDiscriptor, buffer, 1024, 0);
        if (amountRecieved > 0)
            std::cout << buffer << std::endl;
        else if (amountRecieved == 0)
            break;
    }
}

void Client::reciveMessageAndPrintOnNewThread()
{
    std::thread t(&Client::reciveMessage, this);
    t.detach();
}

void Client::setName(std::string name ){
    this->name = name;
}

std::string Client::getName(){
    return name;
}