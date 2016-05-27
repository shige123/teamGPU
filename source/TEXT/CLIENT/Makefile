# Makefile for client and sever

default: 
	@echo select TM_server or TM_client
	@echo ex. make TM_server

TM_server: SOCKET.o TM_server.c

TM_client: SOCKET.o TM_client.c

SOCKET.o:
	gcc -c SOCKET.c -o SOCKET.o

TM_server.c:
	gcc TM_server.c SOCKET.o -o TM_server

TM_client.c:
	gcc TM_client.c SOCKET.o -o TM_client

clean: 
	rm SOCKET.o
	rm TM_server
	rm TM_client
