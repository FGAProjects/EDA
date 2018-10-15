#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {

    char nome_completo[101];
    char celular[14];
    unsigned int cep;
    char endereco[40];
    char data_nascimento[11];  
    struct Agenda *proximo;
    struct Agenda *anterior;
}Agenda;

//criar obejto da lista como vazia
Agenda *lista_vazia(void){
  return NULL;
}
Agenda *inserir_inicio(Agenda *l){
  Agenda *novo = (Agenda*)malloc(sizeof(Agenda));

  char nome[101];
  char telefone[11];
  char endereco[101];
  unsigned int cep;
  char dataNascimento[11];

  printf(" -----------------------------\n");
  printf("|        novo registro       |\n");
  printf(" -----------------------------\n");
  printf("1 - Inserir contato\n\n");
  printf("Digite o nome:  ");
  //getchar();
  scanf("%[^\n]", nome);
  printf("Numero de telefone:  ");
  scanf("%s", telefone);
  //printf("TELEFONE %s",telefone);
  fflush ( stdin );
  printf("Endereco:  ");
  getchar();
  scanf("%[^\n]", endereco);
  printf("CEP:  ");
  scanf("%d", &cep);
  printf("Data de nascimento:  ");
  scanf("%s", dataNascimento);
  printf("DATA %s",dataNascimento);
  //printf("das/dsa/dsad\n");

  strcpy(novo->nome_completo,nome);
  strcpy(novo->celular,telefone);
  strcpy(novo->endereco,endereco);
  novo->cep=cep;
  strcpy(novo->data_nascimento,dataNascimento);
  printf("novo data %s\n",novo->data_nascimento );
  novo->proximo = l;

  printf("\n_____Contato adicionado_____\n\n\n");

  return novo;
}

void imprimir_lista(Agenda *l){
  Agenda *ag;
  if(l==NULL)
    printf("VAZIA\n");
  else
    printf("\n\nVisualizar registros:\n");
  for(ag=l; ag!=NULL; ag=ag->proximo){
    printf("Nome: %s\n", ag->nome_completo);
		printf("Celular: %s\n", ag->celular);
		printf("Endereco: %s\n", ag->endereco);
		printf("CEP: %d\n", ag->cep);
		printf("DATA DE NASCIMENTO: %s\n", ag->data_nascimento);

  }
  printf("\n\n\n");
}



int main () {

	char arquivo [] = "contatos.txt";
	int qtdeLinhas = 0;
	int qtdeDolar = 0;
	char caracteres;
	char lixo[1];

	FILE *file;
	
	file = fopen(arquivo, "r");

  	if(file==NULL){
	    
	    printf("Falha!\n");
	} else {

		while((caracteres=fgetc(file))!=EOF){
	      	
	      	if(caracteres=='\n'){
	        
	        	qtdeLinhas++;
	        } if(caracteres=='$') {
	        	qtdeDolar++;
	        }
	    }		
	}

	rewind(file); 

	Agenda agenda[qtdeLinhas];

	for(int aux = 0; aux < qtdeLinhas; aux ++) {

		fscanf(file, "%[^\n]\n %[^\n]\n %[^\n]\n %d\n %[^\n]\n %[^\n]\n", 
			agenda[aux].nome_completo, 
			agenda[aux].celular, 
			agenda[aux].endereco,
			&agenda[aux].cep,
			agenda[aux].data_nascimento,
			lixo);
	}

	//for(int aux = 0; aux < total; aux ++) {

		printf("Nome: %s\n", agenda[2].nome_completo);
		printf("Celular: %s\n", agenda[2].celular);
		printf("Endereco: %s\n", agenda[2].endereco);
		printf("CEP: %d\n", agenda[2].cep);
		printf("DATA DE NASCIMENTO: %s\n", agenda[2].data_nascimento);
	//}
	Agenda *l = (Agenda *)malloc(sizeof(Agenda));
	l=lista_vazia();
	l=inserir_inicio(l);
	imprimir_lista(l);
	return 0;
}