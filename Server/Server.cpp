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
    clientFileDiscriptor = connectedClientFileDiscriptor;
    status = true;
    AcceptedSocket *acceptedClient = new AcceptedSocket;
    acceptedClient->acceptedSocketFD = connectedClientFileDiscriptor;
    acceptedClient->address = client;
    acceptedClient->acceptedSuccesfully = status;
    if (!status)
    {
        acceptedClient->error = connectedClientFileDiscriptor;
    }
    return acceptedClient;
}

int Server::getConnectedClientFileDiscriptor()
{
    return clientFileDiscriptor;
}

ssize_t Server::reciveMessage()
{
    memset(buffer, 0, sizeof(buffer));
    ssize_t amountRecived = recv(clientFileDiscriptor, buffer, 1024, 0);
    return amountRecived;
}

std::string Server::getBuffer()
{
    std::string normalStingBuffer(buffer);
    return normalStingBuffer;
}


bool Server::addAcceptedSocketToList(AcceptedSocket *client)
{
    if (client->acceptedSuccesfully)
    {
        acceptedClientSockets.push_back(client);
        return true;
    }
    return false;
}

void Server::printAcceptedClient()
{
    while (true)
    {
        ssize_t amountRecieved = this->reciveMessage();
        if (amountRecieved > 0)
            std::cout << this->getConnectedClientFileDiscriptor() << ": " << this->getBuffer() << std::endl;
        if (amountRecieved == 0)
            break;
    }
}

void Server::printAcceptedClientOnNewThread()
{
    std::thread t(&Server::printAcceptedClient, this);
    t.detach();
}
