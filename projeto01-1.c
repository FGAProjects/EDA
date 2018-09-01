#include<stdio.h>
#include<stdlib.h>
#define MAX 10

int fneuronio(int *entradas,int *pesos, int *limiarT, int tam) {

	int aux = 0;
	int somap = 0;

	for(aux = 0; aux < tam; aux ++) {

		somap += entradas[aux] * pesos [aux];
	}

	if(somap > *limiarT) {
		
		return 1;
	} else {
		
		return 0;
	}
}

int main () {

	int entradas[MAX];
	int pesos[MAX];
	int aux = 0;
	int limiarT = 0;
	int neuronio = 0;

	for(aux = 0; aux < MAX; aux ++) {

		printf("Insira as entradas \n");
		scanf("%d",& entradas[aux]);
		printf("Insira o peso \n");
		scanf("%d",& pesos[aux]);
	}

	printf("Insira o limiar de T: ");
	scanf("%d", & limiarT);

	neuronio = fneuronio(entradas,pesos,&limiarT, MAX);
	
	if (neuronio == 1) {

		printf("Neurônio ativado!\n");
	}else if (neuronio == 0) {
		
		printf("Neurônio inibido!\n");
	}

	return 0;
}