//server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"SOCKET.h"
#include <unistd.h>

#define BUFFER_SIZE 256

int main(){
  unsigned short port = 51000;
  int DstSocket;
  char buf[BUFFER_SIZE];

  char r_fname[15] = "zundoko.txt";
  //  char s_fname[10] = "ans.txt";
  char ans[30];
  FILE *w_fp, *r_fp;

  int kiyoshi = 0;
  int c, z = 0;
  char tmp[5];


  DstSocket = ServerSetConect (port );

  RecvData(DstSocket,r_fname);

  //////////////////

  if((w_fp = fopen("Text.txt","r")) == NULL){
      printf("file can`t open\n");
      exit(1);
  }

  while((c = getc(w_fp)) != EOF){
    switch(c){
    case 'z':
      z++;
      fgets(tmp,3,w_fp);
      break;
    case 'd':
      fgets(tmp,4,w_fp);
      if(z > 3){
	kiyoshi++;
      }
      z = 0;
      break;
    default:
      fprintf(stderr, "error : %c\n",c);
      exit(1);
    }
  }

  fprintf(stderr, "kiyoshi = %d \n",kiyoshi);

  sprintf(ans,"kiyoshi = %d",kiyoshi);

  send(DstSocket, ans , 100, 0);

  close(DstSocket);


  return 0;

}
  

  
