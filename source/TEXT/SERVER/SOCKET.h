#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>


#define HADES "160.12.172.10"
#define JOKER "160.12.172.5"


extern int SendData(int DstSocket, char *R_FileName);
extern int RecvData(int DstSocket, char *W_FileName); 
extern int ClientSetConect(unsigned short port , char *IP);
extern int ServerSetConect(unsigned short port);


#endif
