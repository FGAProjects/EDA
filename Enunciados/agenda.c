#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MTELEFONE "#####-####"
#define MDATA "##/##/####"

struct registro{
  char nome[101];
  char telefone[11];
  char endereco[101];
  unsigned int cep;
  char data[11];
  struct registro *prox;
};
typedef struct registro Agenda;

Agenda *inicializa(void);
Agenda *insere(Agenda *l);
void imprime(Agenda *l);
Agenda *apaga_contato(Agenda *l);
void libera(Agenda *l);
int tamanho(Agenda *l);
int menu();
void opcao(Agenda *l, int op);
char *registro_apagar();
void *busca(Agenda *l);
char *mascaraTelefone(char telefone[], char formato[]);

int vazia(Agenda *l){
  if(l->prox==NULL)
    return 1;
  else
    return 0;
}

char *mascaraData(char dataKa[]){
  char aux[11];
  int i=0;
 char formato[] = MDATA;

  while(*dataKa){
    if(formato[i] != '#'){
      aux[i]=formato[i];
      i++;
    } else {
      aux[i]=*dataKa;
      dataKa++;
      i++;
    }
  }
  aux[i]=0;
  strcpy(dataKa, aux);
  return dataKa;
}
void ler_arquivo(){
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
			agenda[aux].nome, 
			agenda[aux].telefone, 
			agenda[aux].endereco,
			&agenda[aux].cep,
			agenda[aux].data,
			lixo);
      //arquivo_lista(l,agenda[aux].nome,agenda[aux].telefone,agenda[aux].endereco,agenda[aux].cep,agenda[aux].data)
	}

	//for(int aux = 0; aux < total; aux ++) {
    
		printf("Nome: %s\n", agenda[2].nome);
		printf("Celular: %s\n", agenda[2].telefone);
		printf("Endereco: %s\n", agenda[2].endereco);
		printf("CEP: %d\n", agenda[2].cep);
		printf("DATA DE NASCIMENTO: %s\n", agenda[2].data);
  

}

int main(){
  ler_arquivo();
  Agenda *l = (Agenda *)malloc(sizeof(Agenda));
  if(!l){ // verifica se tem memória
    printf("Sem memória disponível!\n");
    exit(1);
  } else {
    l=inicializa();
    int opt;

    do{
      opt=menu();

      switch (opt) {
        case 0:
          libera(l);
          break;
        case 1:
          l=insere(l);
          break;
        case 2:
          l=apaga_contato(l);
          break;
        case 3:
          busca(l);
          break;
        case 4:
          imprime(l);
          break;
        default:
          printf("Digite uma opcao valida (:\n\n");
      }

    } while(opt);
    free(l);
    return 0;
  }
}

int menu(){

  int opt;
  printf("'-----------------------------'\n");
  printf("'        bem vindo            '\n");
  printf("'-----------------------------'\n");
  printf("Escolha alguma das opcoes:\n");
  printf("1. Adicionar um registro\n");
  printf("2. Remover um registro\n");
  printf("3. Buscar registro\n");
  printf("4. Visualizar todos os registros\n");
  printf("0. Sair\n");
  printf("\n\nOpção: ");
  scanf("%d", &opt);

  return opt;

}

//inicializa
Agenda *inicializa(void){
  return NULL;
}
//método de ler do arquivo e trasnformar em lista
/*
Agenda *arquivo_lista(Agenda *l,char nome,char telefone,char endereco,unsigned int cep,char data){
  Agenda *novo = (Agenda*)malloc(sizeof(Agenda));
  strcpy(novo->nome,nome);
  strcpy(novo->telefone,mascaraTelefone(telefone,MTELEFONE));
  strcpy(novo->endereco,endereco);
  novo->cep=cep;
  strcpy(novo->data,mascaraData(data));
  printf("novo data %s\n",novo->data );
  novo->prox = l;
  return novo;

}
*/

//insere
Agenda *insere(Agenda *l){
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
  getchar();
  scanf("%[^\n]", nome);
  printf("Numero de telefone:  ");
  scanf("%s", telefone);
  printf("TELEFONE %s",telefone);
  fflush ( stdin );
  printf("Endereco:  ");
  getchar();
  scanf("%[^\n]", endereco);
  printf("CEP:  ");
  scanf("%d", &cep);
  printf("Data de nascimento:  ");
  scanf("%s", dataNascimento);
  printf("DATA %s",dataNascimento);
  printf("das/dsa/dsad\n");

  strcpy(novo->nome,nome);
  strcpy(novo->telefone,mascaraTelefone(telefone,MTELEFONE));
  strcpy(novo->endereco,endereco);
  novo->cep=cep;
  strcpy(novo->data,mascaraData(dataNascimento));
  printf("novo data %s\n",novo->data );
  novo->prox = l;

  printf("\n_____Contato adicionado_____\n\n\n");

  return novo;
}

void imprime(Agenda *l){
  Agenda *ag;
/*  if(vazia(l)){
    printf("Lista vazia\n");
    return ;
  }
*/
  if(l==NULL)
    printf("VAZIA\n");
  else
    printf("\n\nVisualizar registros:\n");
  for(ag=l; ag!=NULL; ag=ag->prox){
    printf("Nome: %s\n", ag->nome);
    //mascara(ag->data,"#####-####");
  //  printf("Telefone: %s\n", ag->telefone);
  }
  printf("\n\n\n");
}

Agenda *apaga_contato(Agenda *l){//, char *nome_remover){
  Agenda *ant = NULL;
  Agenda *aux = l;

  char nome[101];

  printf(" -----------------------------\n");
  printf("|       apagar registro      |\n");
  printf(" -----------------------------\n");
  printf("2 - Digite o registro que deseja apagar:  ");
  getchar();
  scanf("%[^\n]", nome);


  /* Verifica se achou o elemento */
  while(aux!=NULL && strcmp(aux->nome,nome)!=0){
    ant = aux;
    aux = aux->prox;
  }
  /* Verifica se achou o elemento */
  if(aux==NULL){
    printf("\n\n!!! Não achou o registro solicitado.\n\n");
    return l;
  }
  /* Retira elemento */
  if(ant==NULL){
    /* retira do início */
    l = aux->prox;
  } else {
    /* retira do meio */
    ant->prox = aux->prox;
  }

  printf("Registro removido!");

  free(aux);
  return l;
}

/* Função de busca */
void *busca(Agenda *l){

  char nome[101];

  printf(" -----------------------------\n");
  printf("|        buscar registro      |\n");
  printf(" -----------------------------\n");
  printf("3 - Digite o registro que deseja buscar:  ");
  getchar();
  scanf("%[^\n]", nome);

  Agenda *aux;
  int achou = 0;
  for(aux=l; aux!=NULL; aux=aux->prox){
    if(strcmp(aux->nome, nome)==0){
      printf("\n\nACHOUU!!<o/ \n\nNome: %s\n",aux->nome);
      printf("Telefone: %s\n", aux->telefone);
      printf("Endereco: %s\n", aux->endereco);
      printf("CEP: %d\n",aux->cep);
      printf("Data de nascimento: %s \n\n\n", aux->data);
      achou = 1;
    }
  }
  if(achou==0){
    printf("\n\n !!! Não foi encontrado\n\n");
  }

}


void libera(Agenda *l){
  Agenda *p=l; //aux, agenda
  while(p!=NULL){
    Agenda *ag = p->prox; /* guarda referencia para o proximo elemento */
    free(p); /* libera a memória apontada por AUX */
    p=ag;  /* faz AUX apontar para o proximo */
  }
}

// Tamanho da lista
int tamanho(Agenda *l){
  if(l==NULL) return 0;
  int cont = 0;
  Agenda *no=l; //*l -> primeiro elemento da lista?
  while(no!=NULL){
    cont++;
    no=no->prox;
  }
  return cont;
}

char *mascaraTelefone(char telefone[], char formato[]){
  char aux[11];
  int i=0;

  while(*telefone){
    if(formato[i] != '#'){
      aux[i]=formato[i];
      i++;
    } else {
      aux[i]=*telefone;
      telefone++;
      i++;
    }
  }
  aux[i]=0;
  strcpy(telefone, aux);
  return telefone;
}