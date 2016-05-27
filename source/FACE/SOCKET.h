#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "FILE.h"

#define HADES "160.12.172.10"
#define JOKER "160.12.172.5"

#define NUM_OF_FILE 50

#define ORIGIN 0
#define RESULT 1

extern int SendData(int DstSocket, int fnum, char file);
extern int RecvData(int DstSocket, int fnum, char file); 
extern int ClientSetConect(unsigned short port , char *IP);
extern int ServerSetConect(unsigned short port);


#endif
