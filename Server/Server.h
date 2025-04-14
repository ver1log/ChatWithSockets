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

class Server{
private:
    int serverFileDiscriptor;
    int bindingStatus;
    int clientFileDiscriptor;
    std::map<int, std::string> FDtoName;
public:
    char buffer[1024];
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
    bool acceptClientConnection(struct sockaddr_in);
    int getConnectedClientFileDiscriptor();
    ssize_t reciveMessage();
    std::string getBuffer();
    void endServer(){
        close(clientFileDiscriptor);
        shutdown(serverFileDiscriptor, SHUT_RDWR);
    }
};


#endif