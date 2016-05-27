//server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SOCKET.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Labeling.h"
#include <string>
#include <unistd.h>

#define BUFFER_SIZE 256
#define PHOTO_NUM 50
#define PROCCESS_NUM 4

cv::RNG rnd(1192);
cv::Scalar randomColor();
void labelingh(char* infname, char* outfname);

int main(int argc, char *argv[]){
  /* IP アドレス、ポート番号、ソケット */
  // char destination[80];
  unsigned short port;
  if(argc == 2){
    port = atoi(argv[1]);
  }else{
    port = 51000;
  }
  /* 各種パラメータ */
  int DstSocket;
  int i;
  int p_count = 0;
  pid_t p_id;
  char infname[11], outfname[12];

  for( p_count = 0; p_count < PROCCESS_NUM - 1; p_count++ ){

    
   if((p_id = fork()) != 0){
     //p_count++;
      continue;
  }

   // p_count = getpid() % PROCCESS_NUM;
    
  DstSocket = ServerSetConect ( port + (5 * p_count) );
  


  for(i = (PHOTO_NUM / PROCCESS_NUM) * p_count; i < (PHOTO_NUM / PROCCESS_NUM) * ( p_count + 1 ); i++){ 
    RecvData(DstSocket,i,ORIGIN);
    OriginalFileName(i, infname);
    ResultFileName(i, outfname);
    labelingh(infname, outfname);
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
    labelingh(infname, outfname);
    SendData(DstSocket, i, RESULT);
    //SendData(DstSocket, i, ORIGIN);
  }

//wait(NULL);
  close(DstSocket);
  printf("connection closed\n");
  return 0;   
 }


cv::Scalar randomColor(){
  return cv::Scalar(rnd.next() & 0xFF, rnd.next() & 0xFF, rnd.next() & 0xFF);
}

void labelingh(char* infname, char* outfname){
  struct timeval s,e;

  //gettimeofday(&s,NULL);
  printf("label_readfile: %s\n", infname);
  cv::Mat img = cv::imread(infname);
  
  // グレイスケール化(3チャンネル→1チャンネル化)
  cv::Mat gryimg;
  cv::cvtColor(img, gryimg, CV_BGR2GRAY);
  // 二値化
  cv::Mat binimg;
  cv::threshold(gryimg, binimg, 0, 255, CV_THRESH_BINARY);

  // Lblingの結果を受け取る
  cv::Mat lbl(img.size(), CV_16SC1);

  // ラベリングを実施 ２値化した画像に対して実行する
  LabelingBS	lbling;
  lbling.Exec(binimg.data, (short *)lbl.data, img.cols, img.rows, false, 0);	
	
  // ラベリング結果を出力する、真っ白な状態で初期化
  cv::Mat outimg(img.size(), CV_8UC3, cv::Scalar(0));
	
  // ラベルされた領域をひとつずつ描画
  for( int i = 0; i < lbling.GetNumOfRegions(); i++){
      // ラベリング結果の領域を抽出する
      cv::Mat lblarea;
      cv::compare(lbl, i + 1, lblarea, CV_CMP_EQ);
      // 抽出した領域にランダムな色を設定して出力画像に追加
      cv::Mat color(img.size(), CV_8UC3, randomColor());
      color.copyTo(outimg, lblarea);
    }

  // ラベルされた出力画像を保存
  cv::imwrite(outfname, outimg);
  //gettimeofday(&e,NULL);

  //時間を計測
  // std::cout << "time =" << (e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec ) / 100000.0 << std::endl;

}

