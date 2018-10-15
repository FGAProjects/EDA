#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 1025

int main(){

  char path[]="teste.txt";
  FILE *file;

  file=fopen(path,"r");

  int rows=0;
  int cols=0;
  char ch;

  if(file==NULL){
    printf("Falha!\n");
  } else {
    while((ch=fgetc(file))!=EOF){
      if(ch=='\n'){
        rows++;
      } else if(ch==';'&&rows==0){
        cols++;
      }
    }
  }

  cols +=1; //Corrigir, porque volta 1024
  printf("rows: %d\n", rows);
  printf("cols: %d\n", cols);

  // aloca memória com calloc, zerando todos os valores da matriz
  int **photo=(int**)calloc(rows,sizeof(int*));

  for(int i=0; i<rows; i++){
    photo[i]=(int*)calloc(cols,sizeof(int));
  }

  rewind(file);

  if(file==NULL){
    printf("Falha!\n");
  } else {
    for(int i=0; i<rows; i++){
      for(int j=0; j<cols; j++){
        fscanf(file, "%d%*c", &photo[i][j]);
      }
    }
  }

  for(int i=0; i<rows; ++i){
    for(int j=0; j<cols; ++j){
      printf("%d\t", photo[i][j]);
    }
    printf("\n");
  }

  //printf("%d", photo[2][0]);

  printf("\n");
  printf("\n");

  for (int i=1;i<rows-1;i++){
    for(int j=1;j<cols-1;j++){
      printf("%d\t",photo[i][j] ); //pegou os numeros sem ser os da borda
    }
    printf("\n");
  }

  //não esquecer nunca de fechar
  fclose(file);

  return 0;
}
