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
 	int prioridade;
 	struct aviao* prox;
};
typedef struct aviao Aviao;

struct fila {

 	Aviao* inicio;
 	Aviao* final;
};
typedef struct fila Fila;

Fila* cria () {

 	Fila* fila = (Fila*) malloc(sizeof(Fila));
 	fila->inicio = fila->final = NULL;

 	return fila;
}

int vazia (Fila* fila) {

 	return (fila->inicio == NULL);
}

Aviao* ins_fim (Aviao* final, char codigo[CODIGO_AVIAO],int combustivel,int numero_aleatorio) {

 	Aviao* novo = (Aviao*) malloc(sizeof(Aviao));
 	int contador = 0;

 	if (numero_aleatorio == 65) {

 		strcpy(novo->tipo_de_operacao,"A");
 		strcpy(novo->status,"decolou");
 	} else {

 		strcpy(novo->tipo_de_operacao,"D");
 		strcpy(novo->status,"pousou");
 	}

 	strcpy(novo->codigo,codigo);
 	novo->combustivel = combustivel;

 	if(strcmp(novo->tipo_de_operacao,"A") == 0) {
 		
 		if(novo->combustivel == 0) {

 			novo->prioridade = 0;		
 		} else {

 			novo->prioridade = 1;
 		}	
 	} else {

 		novo->prioridade = 1;
 	}

 	novo->prox = NULL;

 	if (final != NULL) {

 		final->prox = novo;
 	}

 	return novo;
}

Aviao* retira_inicio (Aviao* inicio) {

 	Aviao* aviao = inicio->prox;

 	free(inicio);

 	return aviao;
}

Fila* push (Fila* fila,char codigo[CODIGO_AVIAO],int combustivel,int numero_aleatorio) {

 	fila->final = ins_fim(fila->final,codigo,combustivel,numero_aleatorio);

 	if (fila->inicio == NULL) {

 		fila->inicio = fila->final;
	}

	return fila;
}

void pop (Fila* fila) {

 	char codigo_aviao[CODIGO_AVIAO];

 	if (vazia(fila)) {

 		printf("Fila vazia.\n");
 		exit(1);
 	}

 	strcpy(codigo_aviao,fila->inicio->codigo);

 	fila->inicio = retira_inicio(fila->inicio);

 	if (fila->inicio == NULL) {

 		fila->final = NULL;
 	}
}

void libera (Fila* fila) {

 	Aviao* aviao = fila->inicio;

 	while (aviao != NULL) {

 		Aviao* t = aviao->prox;
 		free(aviao);
 		aviao = t;
 	}

 	free(fila);
}

struct tm* add_unidade_de_tempo(struct tm *now_tm, int qnt){

  	int min;

  	min = now_tm->tm_min;
  	int num = 5 * qnt;
  
  	if(min+num > 59){
    	
    	now_tm->tm_hour+=1;
    	now_tm->tm_min=(now_tm->tm_min+num)-60;
  	} else {
    
    	now_tm->tm_min=now_tm->tm_min+num;
  	}
  	
  	return now_tm;
}

int gerar_numero(int limite_inferior, int limite_superior){

	int result = 0;

	for (int aux = 0; aux < 1; aux ++) {
		
		result = (rand() % (limite_superior - limite_inferior + 1)) + limite_inferior;
	}

	return result;
}

int gerar_numero_char(int numero) {

	while (numero != 65 && numero != 68) {

		numero = gerar_numero(65,68);
	}

	return numero;
}

// Fila* ordena(Fila* fila,char codigo[CODIGO_AVIAO],int combustivel,int numero_aleatorio) {

// 	Aviao* aviao;
// 	Fila* novo = push(fila,codigo,combustivel,numero_aleatorio);
// 	Fila* anterior = NULL;
// 	Fila* p = fila;

// 	for (aviao=fila->inicio; aviao!= NULL; aviao=aviao->prox) {

// 		if(aviao->combustivel == 0) {

// 			anterior = p;
// 		}

// 		if(anterior == NULL) {

// 			novo->inicio = fila->inicio;
// 			fila->inicio = aviao;
// 		} else {

// 			novo->inicio = anterior->final;
// 			anterior->final = aviao;
// 		}
// 	}

// 	return fila;
// }

void imprime (Fila* fila,int nVoos,int nAproximacoes,int nDecolagens) {

 	Aviao* aviao;
 	
	time_t now;
	struct tm *now_tm;
	int numero_pista;
	int contador_critico = 0;
	int hora_atual = 0;
	int minuto_atual = 0;
	int contador_de_pista = 0;
	int contador = 0;
	int interador = 0;
	int contador_pista_3 = 0;
	int alerta_critico = 0;

	now = time(NULL);
	now_tm = localtime(&now);
	now_tm = add_unidade_de_tempo(now_tm, interador);

	printf("--------------------------------------------------------------------------------\n");
 	printf("Aeroporto Internacional de Brasília\n");
 	printf("Hora Inicial: %s\n",__TIME__);
 	printf("Fila de Pedidos: \n");
 	printf("NVoos: %d\n",nVoos);
 	printf("Naproximacoes: %d\n",nAproximacoes);
 	printf("NDecolagens: %d\n",nDecolagens);
 	printf("--------------------------------------------------------------------------------\n");
 	printf("Listagem de eventos\n\n");
 	
 	for (aviao=fila->inicio; aviao!= NULL; aviao=aviao->prox) {
	     
	    //ARRUMAR AS HORAS
	    now_tm = add_unidade_de_tempo(now_tm, interador);
 		hora_atual = now_tm->tm_hour;
	    minuto_atual = now_tm->tm_min;

	    if(strcmp(aviao->tipo_de_operacao,"A") == 0) {

			numero_pista = gerar_numero(1,2);	    	
	    } else if(strcmp(aviao->tipo_de_operacao,"A") == 0 && aviao->combustivel == 0) {

	    	numero_pista = gerar_numero(1,2);
	    	//GANHA PRIORIDADE
	    	alerta_critico ++;

	    } else {

	    	numero_pista = gerar_numero(1,3);
	    }
	   	
		contador ++;

		if(alerta_critico == 3) {

			printf("“ALERTA GERAL DE DESVIO DE AERONAVE\n");
			numero_pista = 3; //CASO ESTEJA DISPONIVEL, DEVE SER FEITO UMA FORMA DE NÃO 
			//REPETIR AS PISTAS
			interador ++;
			now_tm = add_unidade_de_tempo(now_tm, interador);
			interador = 0;
		}

		// if(contador == 3) {
	    	
		// 	interador ++;
		// 	now_tm = add_unidade_de_tempo(now_tm, interador);
		// 	aviao->combustivel --;
		// 	interador = 0;
		// 	contador = 0;
		// 	contador_pista_3 = 0;
		// 	alerta_critico = 0;
		// }

		printf("Código do voo: %s\n", aviao->codigo);
	    printf("Status: [aeronave %s]\n", aviao->status);
		printf("Horário do início do procedimento: %d:%d \n", hora_atual, minuto_atual);
		printf("Número da pista: %d\n\n", numero_pista);

		// if(numero_pista == 3) {

		// 	contador_de_pista ++;
		// }
	}

 	/*printf("--------------------------------------------------------------------------------\n");
 	printf("Aeroporto Internacional de Brasília\n");
 	printf("Hora Inicial: %s\n",__TIME__);
 	printf("Fila de Pedidos: \n");
 	printf("NVoos: %d\n",nVoos);
 	printf("Naproximacoes: %d\n",nAproximacoes);
 	printf("NDecolagens: %d\n",nDecolagens);
 	printf("--------------------------------------------------------------------------------\n");
 	printf("Listagem de eventos\n\n");

 	for (aviao=fila->inicio; aviao!= NULL; aviao=aviao->prox) {
	    
	    now_tm=add_unidade_de_tempo(now_tm, 1);
	    hora_atual = now_tm->tm_hour;
	    minuto_atual = now_tm->tm_min;

	    if (strcmp(aviao->tipo_de_operacao,"D") == 0) {
	    		
    		numero_pista = gerar_numero(1,3);
    		printf("Código do voo: %s\n", aviao->codigo);
			printf("Status: [aeronave decolou]\n");
			printf("Horário do início do procedimento: %d:%d \n", hora_atual, minuto_atual);
			printf("Número da pista: %d\n\n", numero_pista);

			if(numero_pista == 3) {

				contador_de_pista ++;
			}
    	} else {
	    		
    		numero_pista = gerar_numero(1,2);
    		printf("Código do voo: %s\n", aviao->codigo);
			printf("Status: [aeronave pousou]\n");
			printf("Horário do início do procedimento: %d:%d \n", hora_atual, minuto_atual);
			printf("Número da pista: %d\n\n", numero_pista);
    	} 

	    if (aviao->combustivel == 0) {

	    	numero_pista = gerar_numero(1,3);

	    	if(numero_pista == 3) {

	    		contador_de_pista ++;
	    	}

	    	contador_critico ++;

	    	if (contador_critico == 3) {

	    		printf("ALERTA GERAL DE DESVIO DE AERONAVE\n\n");

	    		contador_critico = 0;

	    		if(contador_de_pista == 3) {

	    			printf("ALERTA CRÍTICO, AERONAVE IRÁ CAIR\n\n");
	    			pop(fila);
	    		}	    		
	    	} else {

	    		printf("Código do voo: %s\n", aviao->codigo);
 				printf("Status: [aeronave pousou]\n");
 				printf("Horário do início do procedimento: %d:%d \n", hora_atual, minuto_atual);
 				printf("Número da pista: %d\n\n", numero_pista);
	    	}	    	
	    }

	    if (contador_de_pista == 3) {

	    	contador_de_pista = 0;
	    }
	}*/
}

int main () {

 	Fila* fila = cria();

 	int nVoos = 0,nAproximacoes = 0,nDecolagens = 0,combustivelA = 0;
	int numero_aleatorio = 0;

	srand(time(0));
	char codigo[CODIGO_AVIAO];
	char arquivo [] = "codigo_de_voos.txt";

	nAproximacoes = gerar_numero(10,32);
	nDecolagens = gerar_numero(10,32);
	combustivelA = gerar_numero(0,12);
	nVoos = nAproximacoes + nDecolagens;

	FILE *file;

	file = fopen(arquivo, "r");

  	if(file==NULL){

	    printf("Falha!\n");
	} else {

		for(int aux = 0; aux < nVoos; aux ++) {

			fscanf(file, "%[^\n]\n", codigo);

			numero_aleatorio = gerar_numero_char(gerar_numero(65,68));
			combustivelA = gerar_numero(0,12);
			fila = push(fila,codigo,combustivelA,numero_aleatorio);
		}
	}

	fclose(file);

 	imprime(fila,nVoos,nAproximacoes,nDecolagens);
 	libera(fila);

 	return 0;
}
