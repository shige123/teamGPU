#include<stdlib.h>
#include<stdio.h>

#define N 10000000

int main(){
  
  int i;
  char *ZD[2] = {"zun","doko"};
  
  srand(1);

  for(i = 0; i < N;i++){
    printf("%s",ZD[rand()%2]);
  }
}
