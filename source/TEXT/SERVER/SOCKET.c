#include "SOCKET.h"

int SendData(int DstSocket,char *R_FileName){ 
  FILE *r_Fp;
  int size;
  char buf[4096];
  fpos_t fsize;

  fprintf(stderr,"Start Send : %s\n",R_FileName);

  if((r_Fp = fopen ( R_FileName , "rb")) == NULL){
    fprintf(stderr," %s not found. \n",R_FileName);
    return -1;
  }

  fseek ( r_Fp , 0 , SEEK_END );
  sprintf(buf, "%ld" ,ftell(r_Fp)); 
  fseek(r_Fp, 0, SEEK_SET);

  send(DstSocket, buf, sizeof(buf), 0);

  while(size != 0){
      size = fread(buf, 1, 4096, r_Fp);
      send(DstSocket, buf, size, 0);
    }

  fprintf(stderr,"End Send : %s\n",R_FileName);

  fclose(r_Fp);
  return 1;
}

int RecvData(int DstSocket , char *W_FileName){
  FILE *w_Fp;
  int size = 0; 
  int RecvBufSize;
  char RecvBuf[4096];
  int TotalBufSize = 0;
  int TempBufSize;
  
  fprintf(stderr,"Start Recv : %s\n",W_FileName);

  recv(DstSocket , RecvBuf , 4096 , 0);
  RecvBufSize = atoi(RecvBuf);

  if((w_Fp = fopen( W_FileName , "wb")) == NULL){
    fprintf(stderr, "%s not open.", W_FileName);
    return -1;
  }
  fprintf(stderr, "%d \n", RecvBufSize);
  while ( TotalBufSize != RecvBufSize){    
    TempBufSize = recv(DstSocket, RecvBuf, 4096, 0);
    fprintf(stderr,"TempBufSize = %d , RecvBufSize = %d\n",TotalBufSize,RecvBufSize);
    TotalBufSize += TempBufSize; 
    fwrite(RecvBuf, 1, TempBufSize , w_Fp);
 
  }

  fprintf(stderr,"End Recv : %s\n",W_FileName);

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
	    
  fprintf(stderr,"Connection Success : %s\n", IP);
  return DstSocket;
}

int ServerSetConect(unsigned short port){
  int DstSocket, SrcSocket;
  struct sockaddr_in SrcAddr,DstAddr;
  socklen_t DstAddrSize = sizeof(DstAddr);
  char yes = 1;
  
  fprintf(stderr,"Start Conect : %d \n",port);
  
  memset(&SrcAddr, 0 ,sizeof(SrcAddr));
  SrcAddr.sin_port = htons(port);
  SrcAddr.sin_family = AF_INET;
  SrcAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  
  SrcSocket = socket(AF_INET, SOCK_STREAM , 0);
  
  setsockopt(SrcSocket,SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes));

  bind(SrcSocket, (struct sockaddr *) &SrcAddr, sizeof(SrcAddr));
  listen(SrcSocket, 1);
  fprintf(stderr,"Waiting for connection ...\n");
  DstSocket = accept(SrcSocket, (struct sockaddr *) &DstAddr, &DstAddrSize);
  fprintf(stderr,"Connected from %s\n", inet_ntoa(DstAddr.sin_addr));
  
  
  fprintf(stderr,"End Conect : %d \n",port);

  //fclose(SrcSocket);
  
  return DstSocket;
}

