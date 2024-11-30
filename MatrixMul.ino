#include <stdio.h>
void setup() {
  Serial.begin(115200);
  Serial.println("ON");
float matrizA[8][8];
float matrizB[8][8];
float matrizResultante[8][8];
float x;
 for(int l=0;l<8;l++){
  for(int c=0;c<8;c++){
  x=x+0.1;
  matrizA[l][c]=1+x;
  }
  }
for(int l=0;l<8;l++){
  for(int c=0;c<8;c++){
  x=x+0.1;
  matrizB[l][c]=5+x;
  }
  }
 for(int l2=0;l2<8;l2++){
  for(int l=0;l<8;l++){
  matrizResultante[l2][l]=0;
  for(int c=0;c<8;c++){
  matrizResultante[l2][l]+=matrizA[l2][c]*matrizB[c][l];
  }
  
  }
 }
   for(int l=0;l<8;l++){
  for(int c=0;c<8;c++){
  printf("%f ",matrizResultante[l][c]);             
  }
  printf("\n");
   }
}

void loop() {
}
