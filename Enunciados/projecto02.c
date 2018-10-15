#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	
	int count_expoente = 0;
  	char arquivo [] = "asphalt.txt";
	char caracteres;
	int qtdeLinhas = 0;
	int qtdeColunas = 0;
	double media = 0.0;
	int contador = 0;
	int soma = 0;

	FILE *file;
	
	file = fopen(arquivo, "r");

  	if(file==NULL){
	    
	    printf("Falha!\n");
	} else {
	    
	   while((caracteres=fgetc(file))!=EOF){
	      	
	      	if(caracteres=='\n'){
	        
	        	qtdeLinhas++;

	    	} else if(caracteres==';'&& qtdeLinhas==0){
	        	
	        	qtdeColunas++;
	      	}
	    }
	}

	qtdeColunas +=1; 

	printf("Quantidade de linhas : %d\n", qtdeLinhas);
	printf("Quantidade de colunas : %d\n", qtdeColunas);

	int **imagem = (int**) calloc(qtdeLinhas,sizeof(int*));
	double *matrizMedia = (double *) malloc(qtdeLinhas * sizeof(double));
	int *vetorNormalizado = (int*) malloc(qtdeLinhas * sizeof(int));
	int *soma_media_dec = (int*) malloc(qtdeLinhas * sizeof(int)); 

	for(int auxLinhas = 0; auxLinhas < qtdeLinhas; auxLinhas ++){
		imagem[auxLinhas]=(int*)calloc(qtdeColunas,sizeof(int));
	}

	rewind(file); 

	if(file==NULL){
	
		printf("Falha!\n");
	} else {

	    for(int auxLinhas = 0; auxLinhas < qtdeLinhas; auxLinhas ++){
	
	    	for(int auxColunas = 0; auxColunas < qtdeColunas; auxColunas ++){
	
	      		fscanf(file, "%d%*c", &imagem[auxLinhas][auxColunas]);				
			}	
	    }
	}

	for(int auxLinhas = 0; auxLinhas < qtdeLinhas; auxLinhas ++){
	
    	for(int auxColunas = 0; auxColunas < qtdeColunas; auxColunas ++){
	
      		printf("%d\t" ,imagem[auxLinhas][auxColunas]);	      		
		}
		printf("\n");	
    }

    fclose(file);

	for(int auxLinhas = 0; auxLinhas < qtdeLinhas -2; auxLinhas ++) {

		for(int auxColunas = 0; auxColunas < qtdeColunas -2; auxColunas ++) {

			for(int linhas = auxLinhas; linhas < auxLinhas +3; linhas ++) {

				for(int colunas = auxColunas; colunas < auxColunas +3; colunas ++) {

					soma += imagem[linhas][colunas];
					contador ++;
				}
			}
			printf("Soma %d\n", soma);
			media = (double) soma/contador;
			printf("Media: %lf\n", media);
			matrizMedia[auxLinhas] = media;
			media = 0;
			soma = 0;
			contador = 0;	
		}
	}	

	for(int auxLinhas = 0; auxLinhas < qtdeLinhas -2; auxLinhas ++) {

		for(int auxColunas = 0; auxColunas < qtdeColunas-2; auxColunas ++) {

			for(int linhas = auxLinhas; linhas < auxLinhas +3; linhas ++) {

				for(int colunas = auxColunas; colunas < auxColunas +3; colunas ++) {

					if (imagem[linhas][colunas] >= matrizMedia[linhas]) {
						imagem[linhas][colunas] = 1;
					} else {
						imagem[linhas][colunas] = 0;
					}
				}
			}	
		}
	}

	soma = 0;
	
	for(int auxLinhas = 0; auxLinhas < qtdeLinhas -2; auxLinhas +=1) {

		count_expoente = 0;
		
		for(int auxColunas = 0; auxColunas < qtdeColunas-2; auxColunas +=1) {
		
			vetorNormalizado[auxLinhas] = imagem[auxLinhas][auxColunas];
			
			for(int linhas = auxLinhas; linhas < auxLinhas +3; linhas ++) {
			
				for(int colunas = auxColunas; colunas < auxColunas +3; colunas ++) {
					
					vetorNormalizado[linhas]+= imagem[linhas][colunas] * pow(2,count_expoente);
					count_expoente++;				
				}
				if((imagem[linhas][0]==1) && (linhas == 0)){

			 		soma_media_dec[auxLinhas] = soma_media_dec[auxLinhas] - 1;	
			 	} 
				soma += soma_media_dec[linhas] += vetorNormalizado[linhas];				
			}
		}
	}

	for(int aux = 0; aux < qtdeLinhas; aux ++) {
		free(*(imagem + aux));
	}

	free(imagem);
	free(matrizMedia);
	free(vetorNormalizado);
	free(soma_media_dec);

	return 0;
}

