#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define CODIGO_AVIAO 7
#define MAXIMO_DE_CARACTERES 17
#define TIPO_DE_OPERACAO 1

struct aviao {
 	
 	char codigo[CODIGO_AVIAO];
 	int combustivel;
 	char status[MAXIMO_DE_CARACTERES];
 	char tipo_de_operacao[TIPO_DE_OPERACAO];
 	struct aviao* prox;
};
typedef struct aviao Aviao;

/* Fila da pista normal*/
struct pista_normal {
 	
 	Aviao* inicio;
 	Aviao* final;
};
typedef struct pista_normal Pista_Normal;

struct pista_emergencia {
 	
 	Aviao* inicio;
 	Aviao* final;
};
typedef struct pista_emergencia Pista_Emergencia;

/*Gerar um número aleatório a partir dos limites superiores e inferiores*/

int gerar_numero(int lim_inf, int lim_sup){
	

	int result = 0;

	for (int aux = 0; aux < 1; aux ++) {
		result = (rand() % (lim_sup - lim_inf + 1)) + lim_inf;
	}

	return result;
}

/* Criação das filas das pistas */
Pista_Normal* cria_pista_normal () {
 
 	Pista_Normal* pista_normal = (Pista_Normal*) malloc(sizeof(Pista_Normal));
 	pista_normal->inicio = pista_normal->final = NULL;
 	
 	return pista_normal;
}

Pista_Emergencia* cria_pista_emergencia () {
 
 	Pista_Emergencia* pista_emergencia = (Pista_Emergencia*) malloc(sizeof(Pista_Emergencia));
 	pista_emergencia->inicio = pista_emergencia->final = NULL;
 	
 	return pista_emergencia;
}

Aviao* inserir_fila_decolagem (Aviao* final, char codigo[CODIGO_AVIAO],char tipo_de_operacao[TIPO_DE_OPERACAO]) {
 
 	Aviao* novo = (Aviao*) malloc(sizeof(Aviao)); 
 	
 	strcpy(novo->codigo,codigo);
 	strcpy(novo->tipo_de_operacao,tipo_de_operacao);
 	novo->prox = NULL;
 	
 	if (final != NULL) { 
 		
 		final->prox = novo;
 	}

 	return novo;
}

Aviao* inserir_fila_emergencial (Aviao* final, char codigo[CODIGO_AVIAO]) {
 
 	Aviao* novo = (Aviao*) malloc(sizeof(Aviao));

 	strcpy(novo->codigo,codigo);
 	novo->prox = NULL;
 	
 	if (final != NULL) { 
 		
 		final->prox = novo;
 	}

 	return novo;
}

Aviao* inserir_fila_aproximacao (Aviao* aviao, char codigo[CODIGO_AVIAO],int combustivel,char tipo_de_operacao[TIPO_DE_OPERACAO]) {
 
 	Aviao* novo = (Aviao*) malloc(sizeof(Aviao));

 	strcpy(novo->codigo,codigo);
 	strcpy(novo->tipo_de_operacao,tipo_de_operacao);
 	novo->combustivel = combustivel;
 	novo->prox = NULL;

 	if (aviao != NULL) { 
 		
 		aviao->prox = novo;
 	}
}

Aviao* retira_inicio (Aviao* inicio) {
 	
 	Aviao* aviao = inicio->prox;
 	
 	free(inicio);
 	
 	return aviao;
}

void push_decolagem (Pista_Normal* pista_normal, char codigo[CODIGO_AVIAO],char tipo_de_operacao[TIPO_DE_OPERACAO]) {
 
 	pista_normal->final = inserir_fila_decolagem(pista_normal->final,codigo,tipo_de_operacao);
 
 	if (pista_normal->inicio == NULL) {

 		pista_normal->inicio = pista_normal->final;
	}
}

void push_aproximacao (Pista_Normal* pista_normal, char codigo[CODIGO_AVIAO],int combustivel,char tipo_de_operacao[TIPO_DE_OPERACAO]) {
 
 	pista_normal->final = inserir_fila_aproximacao(pista_normal->final,codigo,combustivel,tipo_de_operacao);
 
 	if (pista_normal->inicio == NULL) {

 		pista_normal->inicio = pista_normal->final;
	}
}

void push_emergencia (Pista_Emergencia* pista_emergencia, char codigo[CODIGO_AVIAO]) {
 
 	pista_emergencia->final = inserir_fila_emergencial(pista_emergencia->final,codigo);
 
 	if (pista_emergencia->inicio == NULL) {

 		pista_emergencia->inicio = pista_emergencia->final;
	}
}

void verifica (Pista_Normal* pista_normal,Pista_Emergencia* pista_emergencia,int combustivel,char codigo[CODIGO_AVIAO],
				char tipo_de_operacao[TIPO_DE_OPERACAO]) {

	if (combustivel == 0) {

		push_emergencia(pista_emergencia,codigo);
	} else if (tipo_de_operacao == "A"){

		push_aproximacao(pista_normal,codigo,combustivel,tipo_de_operacao);
	} else if (tipo_de_operacao == "D") {

		push_decolagem(pista_normal,codigo,tipo_de_operacao);
	}
}

int fila_vazia_aproximacao (Pista_Normal* pista_normal) {
 	
 	return (pista_normal->inicio == NULL);
}

void pop (Pista_Normal* pista_normal,char tipo_de_operacao[TIPO_DE_OPERACAO]) {

 	char codigo_aviao[CODIGO_AVIAO];
 	
 	if (fila_vazia_aproximacao(pista_normal)) {
 		
 		printf("Fila vazia.\n");
 		exit(1); 
 	}

 	if (tipo_de_operacao == "A") {

	 	strcpy(codigo_aviao,pista_normal->inicio->codigo);

	 	pista_normal->inicio = retira_inicio(pista_normal->inicio);
	 	
	 	if (pista_normal->inicio == NULL) { 
	 		
	 		pista_normal->final = NULL;
	 	}
	} else {

		printf("Esse avião já decolou\n");
	}
}

void libera (Pista_Normal* pista_normal,Pista_Emergencia* pista_emergencia) {
 
 	Aviao* aviao_pista_normal = pista_normal->inicio;
 	Aviao* aviao_pista_emergencia = pista_emergencia->inicio;
 	
 	while (aviao_pista_normal != NULL) {
 		
 		Aviao* normal = aviao_pista_normal->prox;
 		free(aviao_pista_normal);
 		aviao_pista_normal = normal;
 	}

 	while (aviao_pista_emergencia != NULL) {
 		
 		Aviao* emergencia = aviao_pista_emergencia->prox;
 		free(aviao_pista_emergencia);
 		aviao_pista_emergencia = emergencia;
 	}

 	free(pista_normal);
 	free(pista_emergencia);
}

void imprime (Pista_Normal* pista_normal,Pista_Emergencia* pista_emergencia,int nVoos,int nAproximacoes,int nDecolagens) {
 	
 	Aviao* aviao_pista_normal;
 	Aviao* aviao_pista_emergencia;
 	int pista = 0; 	
 	
 	printf("--------------------------------------------------------------------------------\n");
 	printf("Aeroporto Internacional de Brasília\n");
 	printf("Hora Inicial: %s\n",__TIME__);
 	printf("Fila de Pedidos: \n");
 	printf("NVoos: %d\n",nVoos);
 	printf("Naproximacoes: %d\n",nAproximacoes);
 	printf("NDecolagens: %d\n",nDecolagens);
 	printf("--------------------------------------------------------------------------------\n");
 	printf("Listagem de eventos\n\n");

 	//printf("FILA PRIORITARIA!\n"); /* TIRAR ESSE PRINT DAQUI */
 	/*for (aviao_pista_emergencia=pista_emergencia->inicio; aviao_pista_emergencia!= NULL; aviao_pista_emergencia=aviao_pista_emergencia->prox){
 		
 		printf("Código do voo: %s\n", aviao_pista_emergencia->codigo);
 		printf("Status: \n");
 		printf("Horário do início do procedimento: \n");
 		printf("Número da pista: \n\n");
	}*/

 	printf("FILA NORMAL!\n");  /* TIRAR ESSE PRINT DAQUI */
 	 
 	for (aviao_pista_normal=pista_normal->inicio; aviao_pista_normal!= NULL; aviao_pista_normal=aviao_pista_normal->prox){
 		
 		pista = gerar_numero(1,2);	
 		printf("Código do voo: %s\n", aviao_pista_normal->codigo);
 		printf("Status: \n");
 		printf("Horário do início do procedimento: \n");
 		printf("Número da pista: %d \n\n",pista);
	}
 }

int main () {

	int continua = 0;
	int nVoos = 0,nAproximacoes = 0,nDecolagens = 0,combustivelA = 0;
	srand(time(0));
	char codigo[CODIGO_AVIAO];
	char arquivo [] = "codigo_de_voos.txt";
	int contador = 0;

	Pista_Normal* pista_normal = cria_pista_normal();
	Pista_Emergencia* pista_emergencia = cria_pista_emergencia();

	nAproximacoes = gerar_numero(10,32);
	nDecolagens = gerar_numero(10,32);
	
	nVoos = nAproximacoes + nDecolagens;
	printf("Número de decolagens: %d\n", nDecolagens);
	printf("Numero de aproximacoes: %d\n", nAproximacoes);

	FILE *file;
	
	file = fopen(arquivo, "r");

  	if(file==NULL){
	    
	    printf("Falha!\n");
	} else {

		for(int aux = 0; aux < nDecolagens; aux ++) {

			fscanf(file, "%[^\n]\n", codigo);
				
			combustivelA = gerar_numero(0,12);
			verifica(pista_normal,pista_emergencia,combustivelA,codigo,"D");
		}
		/* ARRUMAR O FOR DEBAIXO */
		for(int aux = nDecolagens; aux < nAproximacoes; aux ++) {
			printf("vamo\n");
		}		
	}

	fclose(file);

	imprime(pista_normal,pista_emergencia,nVoos,nAproximacoes,nDecolagens);

	/*do {

		printf("Desejar continuar? Caso queira sair, aperte 0\n");
		scanf("%d",&continua);
	} while(continua != 0);*/
	return 0;
}