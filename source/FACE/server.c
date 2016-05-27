//server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SOCKET.h"
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/types_c.h>
#include <string>
#include <unistd.h>

#define BUFFER_SIZE 256
#define PHOTO_NUM 20
#define PROCCESS_NUM 4

using namespace std;
using namespace cv;

void FaceDetection(char* infname, char* outfname);

int main(int argc, char *argv[]){
  /* IP アドレス、ポート番号、ソケット */
  // char destination[80];
  unsigned short port;
  if(argc == 2){
    port = atoi(argv[1]);
  }else{
    port = 50995;
  }
  /* 各種パラメータ */
  int DstSocket;
  int i;
  int p_count = 0;
  pid_t p_id;
  char infname[11], outfname[12];

 while( p_count < PROCCESS_NUM - 1 ){
    
   if((p_id = fork()) != 0){
     //p_count++;
      continue;
  }
   
   p_count = getpid() % PROCCESS_NUM;

   //sleep(0.1);

  DstSocket = ServerSetConect ( port + (5 * p_count) );
  
  for(i = (PHOTO_NUM / PROCCESS_NUM) * p_count; i < (PHOTO_NUM / PROCCESS_NUM) * ( p_count + 1 ); i++){ 
    RecvData(DstSocket,i,ORIGIN);
    OriginalFileName(i, infname);
    ResultFileName(i, outfname);
    FaceDetection(infname, outfname);
    SendData(DstSocket,i,RESULT);
    //p_count++;
  }
  
  close(DstSocket);
  return 0;
 }

  DstSocket = ServerSetConect(port + ( 5 * (PROCCESS_NUM -1) ));
  for(i = (PHOTO_NUM / PROCCESS_NUM) * (PROCCESS_NUM - 1) ; i < PHOTO_NUM ;i++){
    RecvData(DstSocket, i, ORIGIN);
    OriginalFileName(i, infname);
    ResultFileName(i, outfname);
    FaceDetection(infname, outfname);
    SendData(DstSocket, i, RESULT);
    //SendData(DstSocket, i, ORIGIN);
  }

//wait(NULL);
  close(DstSocket);
  printf("connection closed\n");
  return 0;   
 }


void FaceDetection(char* infname, char* outfname){
  Mat image = imread(infname);
  Mat frame_gray;
  cvtColor(image, frame_gray, COLOR_BGR2GRAY);
  equalizeHist(frame_gray, frame_gray);
  CascadeClassifier cascade;
  cascade.load("haarcascade_frontalface_alt2.xml");

  vector<Rect> faces;
  cascade.detectMultiScale(image, faces , 1.1,3,0,Size(20,20));
  printf("%d\n",faces.size());
  for( int i = 0; i < faces.size(); i++){
    rectangle(image, Point(faces[i].x,faces[i].y),Point(faces[i].x + faces[i].width,faces[i].y + faces[i].height),Scalar(0,0,200),3,CV_AA);
  }
  
  imwrite(outfname, image);
}
