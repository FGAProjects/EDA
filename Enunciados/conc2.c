#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <stdbool.h>

#define MAXSTRLEN 2
#define MAXWORD 25

int isvalueinarray(int val, int *arr, int size){
    int i;
    for (i=0; i < size; i++) {
        if (arr[i] == val)
            return 1;
    }
    return 0;
}

int main(){
  srand(time(NULL));
  char str[80];
  int lowerLimit = 1, upperLimit = 50;
  char num[2];
  char arr[MAXWORD][MAXSTRLEN+1] = {0};
  int vetor[MAXWORD]={0};

  for(int i=0; i<25; i++){


    int num = 0;
    char let[2];
    num = lowerLimit + rand() % (upperLimit - lowerLimit);
  //  if(isvalueinarray(num, vetor[i], 25)){

  //  }
    //bool var = isvalueinarray(num, vetor, 25);
    /*if(var == false){
        vetor[i]=num;
      }else  {
      num = lowerLimit + rand() % (upperLimit - lowerLimit);
      vetor[i]=num;
    }*/
    while(isvalueinarray(num, vetor, 25) == 1){
      num = lowerLimit + rand() % (upperLimit - lowerLimit);
    }
    //for(int j=0;j<25;j++){
    //  while(vetor[j]!=num)
    //    num = lowerLimit + rand() % (upperLimit - lowerLimit);
    //  if(vetor[j]==num){
    //    num = lowerLimit + rand() % (upperLimit - lowerLimit);
        //printf("Teste\n");
    //  }
    //}
    //num+=i;
    vetor[i]=num;
    //sprintf(let, "%d", num);
    //strncpy(arr[i], let, MAXSTRLEN);
  }
/*
  srand(time(NULL));

  int r =  lowerLimit + rand() % (upperLimit - lowerLimit);
  sprintf(num, "%d", r);
  printf("%s\n", num);
  //printf("%d", r);

  strcpy(str, "asphalt_");
  strcat(str, num);
*/

  for (int i=0; i<25; i++)
    //printf("numero eh %d: %s\n", i+1, arr[i]);
    printf("%d\n", vetor[i] );
  //printf("%s\n",str );


  return 0;
}
