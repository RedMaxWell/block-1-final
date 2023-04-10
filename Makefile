main: main.o message.o user.o server.o
	g++ main.o message.o user.o server.o -g -o main
message.o: message.cpp
	g++ -c -g message.cpp
user.o: user.cpp
	g++ -c -g user.cpp
main.o: main.cpp
	g++ -c -g main.cpp
server.o: server.cpp
	g++ -c -g server.cpp
