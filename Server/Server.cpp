#include "Server.h"

bool Server::initServer()
{
    if (bindingStatus == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Server::beginListening()
{
    int listeningStatus = listen(serverFileDiscriptor, 2);
    if (listeningStatus == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

AcceptedSocket *Server::acceptClientConnection(struct sockaddr_in &client)
{
    uint32_t clientAddressSize = sizeof(client);
    int connectedClientFileDiscriptor = accept(serverFileDiscriptor, (struct sockaddr *)&client, &clientAddressSize);
    bool status;
    if (connectedClientFileDiscriptor == -1)
    {
        status = false;
    }
    status = true;
    AcceptedSocket *acceptedClient = new AcceptedSocket;
    acceptedClient->acceptedSocketFD = connectedClientFileDiscriptor;
    acceptedClient->address = client;
    acceptedClient->isConnected = status;
    if (!status)
    {
        acceptedClient->error = connectedClientFileDiscriptor;
    }
    return acceptedClient;
}
/*
void Server::reciveMessageAndRelay()
{
    while (true)
    {
        if(!isAnyClientConnected())
            break;
        for (int i = 0; i < acceptedClientSockets.size(); i++)
        {
            memset(acceptedClientSockets[i]->buffer, 0, sizeof(acceptedClientSockets[i]->buffer));
            ssize_t amountRecived = recv(acceptedClientSockets[i]->acceptedSocketFD, acceptedClientSockets[i]->buffer, 1024, 0);
            if (amountRecived > 0)
            {
                clientFileDiscriptor = acceptedClientSockets[i]->acceptedSocketFD;
                acceptedClientSockets[i]->buffer[amountRecived] = '\0';
                printIncomingSocket(acceptedClientSockets[i]->acceptedSocketFD);
                //sendMessageToOtherThreads(acceptedClientSockets[i]->acceptedSocketFD, amountRecived);
            }
            if (amountRecived == 0)
            {
                memset(acceptedClientSockets[i]->buffer, 0, sizeof(acceptedClientSockets[i]->buffer));
                acceptedClientSockets[i]->isConnected = false;
            }
        }
    }
}
*/
bool Server::addAcceptedSocketToList(AcceptedSocket *client)
{
    if (client->isConnected)
    {
        acceptedClientSockets.push_back(client);
        return true;
    }
    return false;
}
void Server::receiveAndPrintIncomingData(int socketFD) {
    char buffer[1024];

    while (true)
    {
        ssize_t  amountReceived = recv(socketFD,buffer,1024,0);

        if(amountReceived>0)
        {
            buffer[amountReceived] = 0;
            std::cout << socketFD << ": " << buffer << std::endl;
            sendMessageToOtherThreads(socketFD, buffer ,sizeof(buffer));
        }

        if(amountReceived==0)
            break;
    }

    close(socketFD);
}
void Server::printAcceptedClientOnNewThread(AcceptedSocket* client)
{
    std::thread t(&Server::receiveAndPrintIncomingData, this,client->acceptedSocketFD);
    t.detach();
    threadcount++;
}

void Server::printIncomingSocket(int senderFD)
{

    // ssize_t amountRecieved = this->reciveMessageAndRelay();
    int index;
    for (int i = 0; i < acceptedClientSockets.size(); i++)
    {
        if (acceptedClientSockets[i]->acceptedSocketFD == senderFD)
            index = i;
    }
    std::cout << acceptedClientSockets[index]->acceptedSocketFD << ": " << acceptedClientSockets[index]->buffer << std::endl;
}

void Server::sendMessageToOtherThreads(int senderFD, char *message, int messageSize)
{
    //char sentMessage[1024];
    std::cout << "Message: " << message << std::endl;
    for (int i = 0; i < acceptedClientSockets.size(); i++)
    {
        
        if (senderFD != acceptedClientSockets[i]->acceptedSocketFD)
        {
            std::cout << "FD to be sent to : " << acceptedClientSockets[i]->acceptedSocketFD << std::endl;
            ssize_t amountSent = send(acceptedClientSockets[i]->acceptedSocketFD, message, strlen(message), 0);
            std::cout << "Amount that was sent: " << amountSent << std::endl;
        }
    }
}


bool Server::isAnyClientConnected()
{
    for (int i = 0; i < acceptedClientSockets.size(); i++)
    {
        std::cout << acceptedClientSockets[i]->acceptedSocketFD << " " << acceptedClientSockets[i]->isConnected;
        if (acceptedClientSockets[i]->isConnected)
            return true;
    }
    return false;
}

int Server::threadCountRet(){
    return threadcount;
}