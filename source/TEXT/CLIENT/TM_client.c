//クライアント

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SOCKET.h"
#include <unistd.h>


#define BUFFER_SIZE 256
#//define PROCESS_NUM 4

int main(int argc, char *argv[]){


  unsigned short port;
  char s_fname[15] = "zundoko.txt";
   if(argc == 3){
    port = atoi(argv[1]);
    //  s_fname = argv[2];
  }else{
    port = 51000;
    //s_fname = "sample.txt";
  }
    char buf[BUFFER_SIZE];

  FILE* fp;

    int DstSocket;
  char *ans;

  DstSocket = ClientSetConect(port , JOKER);
  SendData(DstSocket, s_fname);
  //RecvData(DstSocket, r_fname);

  recv(DstSocket, buf, 4096, 0);

  fprintf(stderr , "%s\n" , buf);
  
  close(DstSocket);

  return 0;

}

  
