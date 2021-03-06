#include "FILE.h"

void OriginalFileName(int fnum, char *fname){
  sprintf(fname , "img_%d.jpg", fnum);
}

void ResultFileName(int fnum, char *fname){
  sprintf(fname , "done_%d.jpg", fnum);
}


// filename ex. img_0.png
//mode  1:wb
//      0:rb
FILE* OriginalFileDescriptor(int fnum, int mode){
  FILE *fp;
  char fname[11];
  char fmode[3];
  OriginalFileName(fnum, fname);

  //printf("%s\n", fname);
  
  if(mode){
    strcpy(fmode, "wb");
  }else{
    strcpy(fmode, "rb");
  }
  
  if((fp = fopen(fname, fmode)) == NULL){
    fprintf(stderr, "%s not open.", fname);
    return NULL;
  }

  return fp;
}

//filename ex. done_0.png
//mode 1:wb
//     0:rb
FILE* ResultFileDescriptor(int fnum, int mode){
  FILE *fp;
  char fname[12];
  char fmode[3];
  ResultFileName(fnum, fname);
  //printf("%s\n", fname);
 
  if(mode){
    strcpy(fmode, "wb");
  }else{
    strcpy(fmode, "rb");
  }
  
  if((fp = fopen(fname, fmode)) == NULL){
    fprintf(stderr, "%s not open.", fname);
    return NULL;
  }

  return fp;
}
