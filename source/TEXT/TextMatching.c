#include<stdio.h>
#include<sys/time.h>

int main(){
  FILE *fp;
  int c;
  char tmp[5];
  int z = 0;
  int kiyoshi = 0;
  struct timeval s,e;

  if((fp = fopen("sample.txt","r")) == NULL){
    printf("file can`t open\n");
    exit(1);
  }

  gettimeofday(&s,NULL);
  
  while((c = getc(fp)) != EOF){
    switch(c){
    case 'z':
      z++;
      fgets(tmp,3,fp);
      break;
    case 'd':
      fgets(tmp,4,fp);
      if(z > 3){
	kiyoshi++;
      }
      z = 0;
      break;
    default:
      printf("error : %c\n",c);
      exit(1);
    }
  }
  
  gettimeofday(&e,NULL);
  printf("time    = %f\n", (e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec ) / 100000.0);
  printf("kiyoshi = %d\n",kiyoshi);

}
  
  
  
