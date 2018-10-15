#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MAXSTRLEN 20 
#define MAXWORDS 25

int isValueInArray(int number, int *vector);

int main(){

  int lowerLimit = 1, upperLimit = 50;
  char array_test_asphalt[MAXWORDS][MAXSTRLEN];
  char array_training_asphalt[MAXWORDS][MAXSTRLEN];
  char array_test_grass[MAXWORDS][MAXSTRLEN];
  char array_training_grass[MAXWORDS][MAXSTRLEN];
  int vector_test[MAXWORDS] = {0};
  int vector_training[MAXWORDS] = {0};

  srand(time(NULL));

  
  for(int i=1; i<=25; i++){

        int num = 0;
        num = lowerLimit + rand() % (upperLimit - lowerLimit + 1);

        while(isValueInArray(num,vector_test) == 1){
          num = lowerLimit + rand() % (upperLimit - lowerLimit + 1);
        }
        vector_test[i]=num;
  }

  for (int i=1; i<=25; i++){
    char str[2];
    int num;
    num = vector_test[i];
    sprintf(str, "%02d", num);
    strcpy(array_test_asphalt[i], "asphalt_");
    strcat(array_test_asphalt[i], str);
    strcat(array_test_asphalt[i], ".txt");
  }

  for (int i=1; i<=25; i++){
    char str[2];
    int num;
    num = vector_test[i];
    sprintf(str, "%02d", num);
    strcpy(array_test_grass[i], "grass_");
    strcat(array_test_grass[i], str);
    strcat(array_test_grass[i], ".txt");
  }

  int pointer = 1;
  for (int num=1; num<=50; num++){
    if(isValueInArray(num, vector_test) == 0 && isValueInArray(num, vector_training) == 0){
      vector_training[pointer] = num;
      pointer++;
    }
  }

  for (int i=1; i<=25; i++){
    char str[2];
    int num;
    num = vector_training[i];
    sprintf(str, "%02d", num);
    strcpy(array_training_asphalt[i], "asphalt_");
    strcat(array_training_asphalt[i], str);
    strcat(array_training_asphalt[i], ".txt");
  }

  for (int i=1; i<=25; i++){
    char str[2];
    int num;
    num = vector_training[i];
    sprintf(str, "%02d", num);
    strcpy(array_training_grass[i], "grass_");
    strcat(array_training_grass[i], str);
    strcat(array_training_grass[i], ".txt");
  }

  printf("TESTE ASPHALT:\n");
  for(int i =1; i<=25; i++){
    printf("%s\n",array_test_asphalt[i]);
  }

  printf("TESTE GRASS:\n");
  for(int i =1; i<=25; i++){
    printf("%s\n",array_test_grass[i]);
  }

  printf("TREINAMENTO ASPHALT:\n");
  for(int i =1; i<=25; i++){
    printf("%s\n",array_training_asphalt[i]);
  }

  printf("TREINAMENTO GRASS:\n");
  for(int i =1; i<=25; i++){
    printf("%s\n",array_training_grass[i]);
  }

  return 0;
}


int isValueInArray(int number, int *vector){
  int i;
  for (i=0; i<MAXWORDS; i++){
    if(vector[i] == number)
      return 1;
  }
  return 0;
}
