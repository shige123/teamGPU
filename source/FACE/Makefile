# Makefile for client and sever

all: 
	g++ -c FILE.c -o FILE.o
	g++ -c SOCKET.c -o SOCKET.o
	g++ -o ./SERVER__/server -lopencv_core -lopencv_imgproc -lopencv_highgui  -lopencv_contrib -lopencv_objdetect  -I/usr/local/include/ -L/usr/local/lib FILE.o SOCKET.o server.c
	g++ -O3 client.c SOCKET.o FILE.o  -o ./CLIENT__/client

clean: 
	-rm SOCKET.o
	-rm server
	-rm client
