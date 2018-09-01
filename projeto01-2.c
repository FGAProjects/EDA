#include<stdio.h>
#include<stdlib.h>

void recebe_notas(int *notas, int *APR) {

	int aux = 0;

	for(aux = 0; aux < 10; aux ++) {

		printf("Insira a sua nota: ");
		scanf("%d",& notas[aux]);
		
		if(notas[aux] >= 6) {

			APR[aux] = 1;
		} else {
			
			APR[aux] = 0;
		}
	}
}

void conta_notas(int *APR, int *aprovados, int *reprovados) {

	int aux = 0;
	int totalAprovados = 0;
	int totalReprovados = 0;

	for(aux = 0; aux < 10; aux ++) {

		if(APR[aux] == 1) {
			
			totalAprovados ++;
		} else {
			
			totalReprovados ++;
		}
	}

	*aprovados = totalAprovados;
	*reprovados = totalReprovados;

	printf("Quantidade de aprovados : %d\n", *aprovados);
	printf("Quantidade de reprovados : %d\n", *reprovados);
}

int percent_aprov(int *aprovados, int *reprovados) {

	int aux = 0;
	double percAprovados = 0.0, porcReprovados = 0.0;

	percAprovados = (double) *aprovados/10;
	porcReprovados = (double) *reprovados/10;

	printf("Percentual de aprovados: %.2lf \n", percAprovados);
	printf("Percentual de reprovados: %.2lf\n", porcReprovados);

	if(percAprovados > 0.5) {

		return 1;
	} else {
		
		return 0;
	}
} 

int main () {

	int notas[10];
	int APR[10];
	int aprovados = 0, reprovados = 0;
	int aprovadoFinal = 0;

	recebe_notas(notas,APR);
	conta_notas(APR,&aprovados,&reprovados);
	aprovadoFinal = percent_aprov(&aprovados,&reprovados);

	if(aprovadoFinal == 1) {
		
		printf("Menos da metade da turma foi reprovada \n");
		
	} else {
		
		printf("Mais da metade da turma foi aprovada \n");
	}
}
