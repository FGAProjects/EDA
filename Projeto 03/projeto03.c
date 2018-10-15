#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define novo 1
#define remover 2
#define buscar 3
#define visualizar 4
#define sair 0 

struct registro {
  char nome_completo[101];
  char telefone[11];
  char endereco[101];
  unsigned int cep;
  char data_nascimento[11];
  struct registro *prox;
};
typedef struct registro Agenda;

int vazia(Agenda *agenda) {

	if(agenda->prox == NULL) { 
	
		return 1;
	} else {
		return 0;
	}
}

void imprime(Agenda *agenda){

	if(vazia(agenda)) {
		
		printf("Lista vazia\n");
	} else {

		Agenda *tmp;
		tmp = agenda->prox;
	
	while( tmp != NULL){
		printf("%s", tmp->nome_completo);
		tmp = tmp->prox;
	}
	
	printf("\n\n");
	}
}

Agenda *insere_struct(Agenda *agenda,int tamanho) {

	Agenda *proximo = agenda->prox;
	
	Agenda *novo_contato = (Agenda*)malloc(sizeof(Agenda));

	for(int aux = 0; aux < tamanho; aux ++) {

		strcpy(novo_contato->nome_completo,agenda[aux].nome_completo);
		strcpy(novo_contato->telefone,agenda[aux].telefone);
		strcpy(novo_contato->endereco,agenda[aux].endereco);
		novo_contato->cep,agenda[aux].cep;
		strcpy(novo_contato->data_nascimento,agenda[aux].data_nascimento);
		novo_contato->prox = agenda;
	}

	return novo_contato;
}

void ler_arquivo() {

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
			agenda[aux].telefone, 
			agenda[aux].endereco,
			&agenda[aux].cep,
			agenda[aux].data_nascimento,
			lixo);
	}

	insere_struct(agenda,qtdeDolar);
	
	fclose(file);
}

void inicializa_lista(Agenda *agenda) {

	agenda->prox = NULL;
}

int main () {

	Agenda * agenda = (Agenda *) malloc(sizeof(agenda));

	inicializa_lista(agenda);
	ler_arquivo();
	free(agenda);
	return 0;
}
