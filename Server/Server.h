#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <map>
#include <vector>
#include <thread>

struct AcceptedSocket{
    int acceptedSocketFD;
    struct sockaddr_in address;
    int error;
    bool isConnected;
    char buffer[1024];
};

class Server{
private:
    int serverFileDiscriptor;
    int bindingStatus;
    int clientFileDiscriptor;
    std::vector<AcceptedSocket *> acceptedClientSockets;
    int threadcount = 0;
public:
    //char buffer[1024];
    Server(std::string passedIP, int port){
        serverFileDiscriptor = socket(AF_INET,SOCK_STREAM, 0);
        std::string ip = passedIP;
        std::cout << "file discriptor created\n";
        struct sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_port =  htons((uint16_t) port);
        inet_pton(AF_INET, ip.c_str(), &address.sin_addr.s_addr);
        bindingStatus = bind(serverFileDiscriptor, (struct sockaddr *) &address, sizeof(address));
    }
    bool initServer();
    bool beginListening();
    AcceptedSocket* acceptClientConnection(struct sockaddr_in &);
    //void reciveMessageAndRelay();
    std::string getBuffer();
    void printIncomingSocket(int senderFD);
    void printAcceptedClientOnNewThread(AcceptedSocket *);
    bool addAcceptedSocketToList(AcceptedSocket*);
    void sendMessageToOtherThreads(int senderFD, char *message,int messageSize);
    bool isAnyClientConnected();
    int threadCountRet();
    void receiveAndPrintIncomingData(int clientFD);
    ~Server(){
        //close(clientFileDiscriptor);
        shutdown(serverFileDiscriptor, SHUT_RDWR);
        for(int i = 0; i < acceptedClientSockets.size(); i++){
            delete acceptedClientSockets[i];
        }
    }
};


#endif