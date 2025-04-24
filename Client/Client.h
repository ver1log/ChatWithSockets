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
    char buffer[1024];
    char readingbuffer[1024];
    char writingbuffer[1024];
public:
    Client(){
        socketFileDiscriptor = socket(AF_INET,SOCK_STREAM, 0);
        std::string ip = "127.0.0.1";
        std::cout << "file discriptor created\n";
        struct sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_port =  htons(2000);
        inet_pton(AF_INET, ip.c_str(), &address.sin_addr.s_addr);
        connectionStatus = connect(socketFileDiscriptor, (struct sockaddr *) &address, sizeof(address));
    }
    bool connectToServer();
    ssize_t sendMessage(std::string);
    void reciveMessage();
    char* getBuffer();
    void reciveMessageAndPrintOnNewThread();
    void startListeningAndPrintMessagesOnNewThread();
    void listenAndPrint();
    ~Client(){
        close(socketFileDiscriptor);
    }
};


#endif