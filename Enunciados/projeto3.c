#include <stdio.h>


typedef struct contatos
  {
    char nome[101];
    char celular[30];
    unsigned int CEP;
    char data_nascimento[10];  
    struct contatos *prox;
    struct contatos *ant;
}agenda;



int main(void){
  char arquivo [] = "contatos.txt";
  FILE *file;
  file = fopen(arquivo, "r");

  if(file==NULL){
	    printf("Falha!\n");
	} else {
      printf("arquivo lido com sucesso\n");
  }
  
}