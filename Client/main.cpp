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
    std::string name;
    std::cout << "Enter the name for this client: ";
    std::cin >> name;
    c.setName(name);
    std::cout << std::endl;
    
    std::cout << "Type in an input so we can send it to the server(type exit to end connection)\n";
    std::string line;
    ssize_t received;
    
    while (true)
    {
        //std::cout << c.getName() + ": ";
        std::getline(std::cin, line);
        if (line.size() > 0)
        {
            if (line == "exit")
            {
                break;
            }
            std::string fullMessage = c.getName() + ": " + line;
            received = c.sendMessage(fullMessage);
        }
        
        
    }
    
    return 0;
}