.PHONY: all clean

all: server client guard singleton pollServer selectClient

server: server.o
	gcc server.o -o server -lpthread
client: client.o 
	gcc client.o -o client
guard: 
	g++ guard.cpp -o guard -lpthread
singleton: 
	g++ singleton.cpp -o singleton 
pollServer: pollServer.o 
	gcc pollServer.o -o pollServer -lpthread
selectClient: selectClient.o
	gcc selectClient.o -o selectClient -lpthread
server.o: server.c 
	gcc -c server.c 
client.o: client.c 
	gcc -c client.c
pollServer.o: pollServer.c 
	gcc -c pollServer.c 
selectClient.o: selectClient.c 
	gcc -c selectClient.c 

clean :
	rm -f *.o client server guard singleton selectClient pollServer 