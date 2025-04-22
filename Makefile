all:
	g++  Client/Client.cpp Client/main.cpp -o bin/client
	g++ Server/Server.cpp Server/main.cpp -o bin/server
client:
	g++  Client/Client.cpp Client/main.cpp -o bin/client
server:
	g++ Server/Server.cpp Server/main.cpp -o bin/server
clean:
	rm -rf bin/client bin/server
