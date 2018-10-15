#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <time.h>
#define MAXSTRLEN 20 //PRECISA DEFINIR POR ALOCAÇÃO DIMANICA?
#define MAXWORDS 25

int isValueInArray(int number, int *vector);


int main (){


  int lowerLimit = 1, upperLimit = 50;
  char array_test_asphalt[MAXWORDS][MAXSTRLEN];// = {0};
  char array_training_asphalt[MAXWORDS][MAXSTRLEN];// = {0};
  char array_test_grass[MAXWORDS][MAXSTRLEN];// = {0};
  char array_training_grass[MAXWORDS][MAXSTRLEN];// = {0};
  int vector_test[MAXWORDS] = {0};
  int vector_training[MAXWORDS] = {0};

  srand(time(NULL));

  // 25 first numbers random for test
  for(int i=1; i<=25; i++){
    int num = 0;
    num = lowerLimit + rand() % (upperLimit - lowerLimit + 1);

    while(isValueInArray(num,vector_test) == 1){
      num = lowerLimit + rand() % (upperLimit - lowerLimit + 1);
    }
    vector_test[i]=num;
  }

  // pass int vector to string "ASPHALT"
  for (int i=1; i<=25; i++){
    char str[2];
    int num;
    num = vector_test[i];
    sprintf(str, "%02d", num);
    strcpy(array_test_asphalt[i], "asphalt/asphalt_");
    strcat(array_test_asphalt[i], str);
    strcat(array_test_asphalt[i], ".txt");
  }

  // pass int vector to string "GRASS"
  for (int i=1; i<=25; i++){
    char str[2];
    int num;
    num = vector_test[i];
    sprintf(str, "%02d", num);
    strcpy(array_test_grass[i], "grass/grass_");
    strcat(array_test_grass[i], str);
    strcat(array_test_grass[i], ".txt");
  }

  // puts others 25 random numbers in training vector
  int pointer = 1;
  for (int num=1; num<=50; num++){
    if(isValueInArray(num, vector_test) == 0 && isValueInArray(num, vector_training) == 0){
      vector_training[pointer] = num;
      pointer++;
    }
  }

  // pass int vector to string "ASPHALT"
  for (int i=1; i<=25; i++){
    char str[2];
    int num;
    num = vector_training[i];
    sprintf(str, "%02d", num);
    strcpy(array_training_asphalt[i], "asphalt/asphalt_");
    strcat(array_training_asphalt[i], str);
    strcat(array_training_asphalt[i], ".txt");
  }

  // pass int vector to string "GRASS"
  for (int i=1; i<=25; i++){
    char str[2];
    int num;
    num = vector_training[i];
    sprintf(str, "%02d", num);
    strcpy(array_training_grass[i], "grass/grass_");
    strcat(array_training_grass[i], str);
    strcat(array_training_grass[i], ".txt");
  }


  int tamanho=0;
  tamanho = strlen(array_training_grass[1]);
  printf("%d\n",tamanho );
  char path[1];
  strcpy(path,array_training_grass[1]);
  //path=array_training_grass[0];
  printf("NOME DO ARQUIVO: %s\n", path);
  FILE *file;

  file=fopen(path,"r");

///////////////////////////////////////


  int rows=0;
  int cols=0;
  char ch;

  if(file==NULL){
    printf("Falha!\n");
  } else {
    while((ch=fgetc(file))!=EOF){
      if(ch=='\n'){
        rows++;
      } else if(ch==';'&& rows==0){
        cols++;
      }
    }
  }

  cols+=1; //corrigir, porque retorna 1024
  printf("rows: %d\n", rows);
  printf("cols: %d\n", cols);

  //aloca memórma com calloc, zerando todos os valores da matriz
  int **photo=(int **)calloc(rows,sizeof(int*));
  for(int i=0;i<rows;i++) photo[i]=(int*)calloc(cols,sizeof(int));

  rewind(file); //ler o arquivo do começo

  if(file==NULL) printf("Falha!\n");
  else{
    for(int i=0; i<rows; i++){
      for(int j=0; j<cols; j++){
        fscanf(file, "%d%*c", &photo[i][j]);
      }
    }
  }

  for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){
      printf("%d \t",photo[i][j]);
    }
    printf("\n");
  }

  printf("\n");
  printf("\n");

  int *pont;
  int soma=0;
  double media=0.0;

  int vetor9[3][3]={0};
  int vetor01[3][3]={0};
/*
  for (int i=1;i<rows-1;i++){
    for(int j=1;j<cols-1;j++){
      printf("%d\t",photo[i][j] ); //pegou os numeros sem ser os da borda
      for(int i_m9=i-1; i_m9<i+2;i_m9++){
        for(int j_m9=j-1; j_m9<j+2; j_m9++){
          soma+=vetor9[i_m9][j_m9];
            printf("SOMA: %d\n", soma );
        }
      }
    }
    printf("\n");
  }
  printf("SOMA: %d\n", soma );*/

  for (int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      vetor9[i][j]=photo[i][j];
    }
  }

  for(int i=0; i<3;i++){
    for(int j=0; j<3; j++){
      printf("%d\t",vetor9[i][j]);
      soma+=vetor9[i][j];
      media=(double)soma/9; //???
    }
    printf("\n");
  }
  int array[9];


  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      if(vetor9[i][j]>media)
        vetor01[i][j]=1;
      else
        vetor01[i][j]=0;
      //array[point]=vetor01[i][j];
      //point++;
    }
  }

  // FAZ A PRIMEIRA ROTAÇÃO COM OS 0 e 1
  for(int i=0;i<3;i++) array[i]=vetor01[0][i];
  for(int i=1;i<3;i++) array[i+2]=vetor01[i][2];
  int point=4;
  for(int i=1;i>-1;--i){
    array[i+point]=vetor01[2][i];
    point++;
    point++;
  }
  for(int i=0;i<2;i++) array[i+7]=vetor01[1][i];

  printf("\nSOMA %d\n", soma);
  printf("MEDIA %lf\n", media);

  printf("\n");
  printf("\n-----------------vetor01\n\n");
  for(int i=0; i<3; i++){
    for(int j=0; j<3;j++){
      printf("%d\t", vetor01[i][j]);
    }
    printf("\n");
  }

  printf("\n");
  for(int i=0;i<9;i++)
    printf("%d ",array[i]);

  int arrayRotacionado[9]={0};
  int count0=0;
  /*
  for(int i=8; i>=0; i--){
    printf("vetor ::: %d\n", array[i] );
  }*/

  // contar os zeros a direita
  int num=8;
  while(array[num]!=1){
    count0+=1;
    num--;
  }
  printf("\n\nquantos 0s a direita: %d\n",count0);
  // tranformar pra decimal
  int i = 0;
  unsigned int dec = 0;

  int s = 9;

  while( s-- ) {
      if( array[s] == 0 || array[s] == 1 ) {
          dec = dec + pow(2, i++) * (array[s] - 0);
          //printf("dec = %u, s=%d\n", dec,s);
      }
  };
  printf("\nDecimal: \t %u\n", dec);

  //andando os bits que precisa
  int x = dec;
  int decRot=0;

  if(count0==0) decRot = (x>>0);
  if(count0==1) decRot = (x>>1);
  if(count0==2) decRot = (x>>2);
  if(count0==3) decRot = (x>>3);
  if(count0==4) decRot = (x>>4);
  if(count0==5) decRot = (x>>5);
  if(count0==6) decRot = (x>>6);
  if(count0==7) decRot = (x>>7);
  if(count0==8) decRot = (x>>8);

  printf("\n");
  printf("x rotacionado: %d\n", decRot);

  int v[512]={0};
  v[decRot]+=1;

  printf("Quantidade frequencia [%d]: %d\n", decRot, v[decRot] );

  //não esquecer nunca de fechar
  fclose(file);
  free(photo);




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
