client:
	g++  Client/Client.cpp Client/main.cpp -o client
server:
	g++ Server/Server.cpp Server/main.cpp -o server
clean:
	rm -rf client server