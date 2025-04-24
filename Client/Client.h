#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <thread>


class Client{
private:
    int connectionStatus;
    int socketFileDiscriptor;
    std::string name;
public:
    Client(){
        socketFileDiscriptor = socket(AF_INET,SOCK_STREAM, 0);
        std::string ip = "127.0.0.1";
        //std::cout << "file discriptor created\n";
        struct sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_port =  htons(2000);
        inet_pton(AF_INET, ip.c_str(), &address.sin_addr.s_addr);
        connectionStatus = connect(socketFileDiscriptor, (struct sockaddr *) &address, sizeof(address));
    }
    bool connectToServer();
    ssize_t sendMessage(std::string);
    void reciveMessage();
    void reciveMessageAndPrintOnNewThread();
    void startListeningAndPrintMessagesOnNewThread();
    void listenAndPrint();
    void setName(std::string);
    std::string getName();
    ~Client(){
        close(socketFileDiscriptor);
    }
};


#endif