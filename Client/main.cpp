#include <iostream>
#include "Client.h"

int main()
{
    Client c;
    if (!c.connectToServer())
    {
        std::cerr << "Error connecting to server";
        return -1;
    }
    c.reciveMessageAndPrintOnNewThread();
    
    std::cout << "Type in an input so we can send it to the server(type exit)\n";
    std::string line;
    ssize_t received;
    
    while (true)
    {
        std::getline(std::cin, line);
        if (line.size() > 0)
        {
            if (line == "exit")
            {
                break;
            }
            received = c.sendMessage(line);
            /*
            if (received == -1)
            {
                std::cerr << "server socket has been closed";
                return -1;
            }
            */
        }
        
        
    }
    
    return 0;
}