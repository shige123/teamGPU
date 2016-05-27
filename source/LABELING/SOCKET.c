#include "SOCKET.h"
#define BUFSIZE 1460
//#define BUFSIZE 4096
int SendData(int DstSocket, int fnum, char file){ 
  FILE *r_Fp;
  int size =1;
  char buf[BUFSIZE];
  fpos_t fsize;

  if(file == ORIGIN){
    if((r_Fp = OriginalFileDescriptor(fnum,FILE_READ)) == NULL){
      fprintf(stderr," file not found. \n");
      return -1;
    }
  }else if(file == RESULT) {
    if((r_Fp = ResultFileDescriptor(fnum,FILE_READ)) == NULL){
      fprintf(stderr," file not found. \n");
      return -1;
    }
  }
  //printf("send start\n");
  fseek ( r_Fp , 0 , SEEK_END );
  sprintf(buf, "%ld" ,ftell(r_Fp));
  fseek(r_Fp, 0, SEEK_SET);
  //printf("%s\n", buf);
  send(DstSocket, buf, sizeof(buf), 0);
  
  while(size != 0){
    size = fread(buf, 1, BUFSIZE, r_Fp);
    send(DstSocket, buf, size, 0);
  }
  //printf("send end\n\n");
  
  fclose(r_Fp);
  return 1;
}

int RecvData(int DstSocket , int fnum, char file){
  FILE *w_Fp;
  int size = 0; 
  int RecvBufSize;
  char RecvBuf[BUFSIZE];
  int TotalBufSize = 0;
  int TempBufSize;

  //printf("recv start\n");
  
  recv(DstSocket , RecvBuf , BUFSIZE , 0);
  RecvBufSize = atoi(RecvBuf);

  if(file == ORIGIN){
    if((w_Fp = OriginalFileDescriptor(fnum,FILE_WRITE)) == NULL){
      fprintf(stderr, "file not open.");
      return -1;
    }
  }else if(file == RESULT){
    if((w_Fp = ResultFileDescriptor(fnum,FILE_WRITE)) == NULL){
      fprintf(stderr, "file not open.");
      return -1;
    }
  }
    
  while ( TotalBufSize != RecvBufSize){
    
    TempBufSize = recv(DstSocket , RecvBuf , BUFSIZE , 0);
    TotalBufSize += TempBufSize;
    fwrite(RecvBuf, 1, TempBufSize , w_Fp);
    //printf("size = %d\n", TotalBufSize);
  }

  //printf("Recv end\n\n");
  // バッファ内容をフラッシュ
  fflush(w_Fp);
  // ファイルクローズ
  fclose(w_Fp);

  return 1;
}

int ClientSetConect(unsigned short port , char *IP){
  int DstSocket;
  struct sockaddr_in dstAddr;
  
  memset(&dstAddr, 0 ,sizeof(dstAddr));
  dstAddr.sin_port = htons(port);
  dstAddr.sin_family = AF_INET;
  dstAddr.sin_addr.s_addr = inet_addr(IP);

  DstSocket = socket(AF_INET , SOCK_STREAM , 0);
  fprintf(stderr,"Trying to connect to %s \n", IP);
  if(connect(DstSocket, (struct sockaddr *) &dstAddr, sizeof(dstAddr)) == -1){
    fprintf(stderr, "Conection failed \n");
    exit(1);
  }
	    
  return DstSocket;
}

int ServerSetConect(unsigned short port){
  int DstSocket, SrcSocket;
  struct sockaddr_in SrcAddr,DstAddr;
  socklen_t DstAddrSize = sizeof(DstAddr);
  
  memset(&SrcAddr, 0 ,sizeof(SrcAddr));
  SrcAddr.sin_port = htons(port);
  SrcAddr.sin_family = AF_INET;
  SrcAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  
  SrcSocket = socket(AF_INET, SOCK_STREAM , 0);
  bind(SrcSocket, (struct sockaddr *) &SrcAddr, sizeof(SrcAddr));
  listen(SrcSocket, 1);
  fprintf(stderr,"Waiting for connection ...\n");
  DstSocket = accept(SrcSocket, (struct sockaddr *) &DstAddr, &DstAddrSize);
  fprintf(stderr,"Connected from %s\n", inet_ntoa(DstAddr.sin_addr));
  
  //fclose(SrcSocket);
  
  return DstSocket;
}

