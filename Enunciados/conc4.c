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
  char arr_teste[MAXWORD][MAXSTRLEN+1] = {0};
  char arr_treinamento[MAXWORD][MAXSTRLEN+1] = {0};
  int vetor_teste[MAXWORD]={0};
  int vetor_treinamento[50]={0};

  for(int i=1; i<=25; i++){

    int num = 0;
    char let[2];
    num = lowerLimit + rand() % (upperLimit - lowerLimit + 1);

    while(isvalueinarray(num, vetor_teste, 25) == 1){
      num = lowerLimit + rand() % (upperLimit - lowerLimit + 1);
    }
    vetor_teste[i]=num;
  //  sprintf(let, "%d", num);
  //  strncpy(arr_teste[i], let, MAXSTRLEN);
  }

  int pointer = 1;
  for(int num=1; num<=50;num++){
    if(isvalueinarray(num, vetor_teste, 25) == 0 && isvalueinarray(num, vetor_treinamento, 25) == 0){
      vetor_treinamento[pointer] = num;
      pointer++;
    }
    //else:
  }


  for (int i=1; i<=25; i++)
    //printf("numero eh %d: %s\n", i+1, arr[i]);
    printf("%d\n", vetor_teste[i] );
  //printf("%s\n",str );

  printf("TREINAMENTO\n");
  for (int i=1; i<=25; i++)
    //printf("numero eh %d: %s\n", i+1, arr[i]);
    printf("%d\n", vetor_treinamento[i] );


  return 0;
}
