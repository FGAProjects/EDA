#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#define MAX 50
#define NUMERO_SORTEIO 25

int *sorteiaTesteTreino() {

    srand(time(NULL));
    int *numero_sorteado = (int *)malloc(50*sizeof(int));

    int x = 1, y = 0, z = 0;
    numero_sorteado[0] = rand() % 50 + 1;
    
    do {
    	
    	numero_sorteado[x] = rand() % 50  + 1;
        y = 0;
        while(y < x) {
            
            if(numero_sorteado[y] == numero_sorteado[x]) {
                --x;
                break;
            }
            ++y;
        }
        ++x;
    } 
    while(x < 50);
    
    return numero_sorteado;
}

int salvaArquivos(int *array, int testeOuTreino, int gramaOuAsfalto){
    
    char nome[20];
    char diretorio[256];
    char linha[256];
    int i = 0;
    int tipo;

    if(testeOuTreino == 0 && gramaOuAsfalto == 0){
        
        strcpy(nome,"ArquivosTeste/teste_grass.txt");
        strcpy(diretorio,"DataSet/grass/grass_");
        tipo = 0;
    }
    else if (testeOuTreino == 0 && gramaOuAsfalto == 1){
        
        strcpy(nome,"ArquivosTeste/teste_asphalt.txt");
        strcpy(diretorio,"DataSet/asphalt/asphalt_");
        tipo = 1;
    }
    else if (testeOuTreino == 1 && gramaOuAsfalto == 0){
        
        strcpy(nome,"ArquivosTeste/treino_grass.txt");
        strcpy(diretorio,"DataSet/grass/grass_");
        tipo = 2;
    }
    else if (testeOuTreino == 1 && gramaOuAsfalto == 1){
        
        strcpy(nome,"ArquivosTeste/treino_asphalt.txt");
        strcpy(diretorio,"DataSet/asphalt/asphalt_");
        tipo = 3;
    }
    else{
        printf("ERRO");
    }
    printf("Criando: %s \n", nome);

    FILE *arquivo = NULL;
    arquivo = fopen(nome, "wt");

    int aux, aux2;
    char temp[50];

    for(i = 0; i < 25; i++){
         if(array[i]<10){
            aux = sprintf(temp, "%s0%d.txt\n", diretorio, array[i]);
            fprintf(arquivo,"%s" ,temp);
         }else if(array[i]>=10){
            aux = sprintf(temp, "%s%d.txt\n", diretorio, array[i]);
            fprintf(arquivo, "%s", temp);
        }
    }
    fclose(arquivo);
    return tipo;
}

void nomeArquivo(int codigoArquivo, char* nome){
    
    switch(codigoArquivo){
    
    	case(0):
    	
    		strcpy(nome,"ArquivosTeste/teste_grass.txt");
    	break;

    	case(1):
    	
    		strcpy(nome,"ArquivosTeste/teste_asphalt.txt");
    	break;

    	case(2):
    		
    		strcpy(nome,"ArquivosTeste/treino_grass.txt");
    	break;

    	case(3):
    	
    		strcpy(nome,"ArquivosTeste/treino_asphalt.txt");
    	break;
    }
}

void pegaLinhaNome(int codigoArquivo, int linha, char* filename, char* conteudoLinha){
    
    nomeArquivo(codigoArquivo, filename);

    FILE *fptr;

    fptr = fopen(filename, "r");
    rewind(fptr);
    int count = 0;
    char buffer[256];
    while (fgets(buffer, sizeof buffer, fptr)) {
        if (count == linha){
            break;
        }
        else{
            count++;
        }
    }

    strtok(buffer, "\n");
    printf("este eh o buffer %s\n", buffer);
    strcpy(conteudoLinha, buffer);
    fclose(fptr);    
}

void calculaILBP(int *matrizImagem[], int linha, int coluna){

	int soma = 0;
	double media = 0;

	int **matrizMedia = (int**)malloc(linha * sizeof(int*));

    for(int auxLinha = 0; auxLinha < linha; auxLinha ++){
    
        matrizMedia[auxLinha] = (int*) malloc(coluna * sizeof(int));
    }

    int *matrizBinaria = (int*) malloc(linha * sizeof(int));

    for(int auxLinha = 0; auxLinha < linha - 2; auxLinha ++) {
        
        for(int auxColuna = 0; auxColuna < coluna -2; auxColuna ++) {
            
            soma = 0;           
            for(int auxLinhaTrinca = auxLinha; auxLinhaTrinca < auxLinha + 3; auxLinhaTrinca ++) {

                for(int auxColunaTrinca = auxColuna; auxColunaTrinca < auxColuna + 3; auxColunaTrinca ++) {
                    
                    soma += matrizImagem[auxLinhaTrinca][auxColunaTrinca];
                }
            }

            media = (double) soma / 9;
            matrizMedia[auxLinha][auxColuna] = media;
        }       
    }

    for(int auxLinha = 0; auxLinha < linha - 2; auxLinha ++) {
        
        for(int auxColuna = 0; auxColuna < coluna -2; auxColuna ++) {
            
            soma = 0;           
            for(int auxLinhaTrinca = auxLinha; auxLinhaTrinca < auxLinha + 3; auxLinhaTrinca ++) {

                for(int auxColunaTrinca = auxColuna; auxColunaTrinca < auxColuna + 3; auxColunaTrinca ++) {
                    
                    if(matrizMedia[auxLinha][auxColuna] > matrizImagem[auxLinhaTrinca][auxColunaTrinca]) {
                        
                        matrizBinaria[auxLinhaTrinca] = 1;
                    } else {
                        
                        matrizBinaria[auxLinhaTrinca] = 0;
                    }
                }
            }
        }       
    }
}


void armazenaArquivoMatriz(char* filename){

	int qtde_linhas_asfalto = 0;
	int qtde_colunas_asfalto = 1;
	char caractere;
	FILE *file_asfalto;
	char arquivo_asfalto [] = "DataSet/asphalt/asphalt_01.txt";
	int* dimensaoMatriz;

	file_asfalto = fopen(arquivo_asfalto, "r");

    if(file_asfalto==NULL){
	    
	    printf("Falha!\n");
	} else {

		while((caractere = fgetc(file_asfalto)) != EOF) {
			
			if(caractere == '\n') {
				
				qtde_linhas_asfalto ++;
			} else if(qtde_linhas_asfalto == 0 && caractere == ';'){

				qtde_colunas_asfalto ++;
			}
		}
	}

	fclose(file_asfalto);

	FILE *file;
    file = fopen(filename, "r");

    int **matrizImagem = (int**)malloc(qtde_linhas_asfalto * sizeof(int*));

    for(int auxLinha = 0; auxLinha < qtde_linhas_asfalto; auxLinha ++){
    
        matrizImagem[auxLinha] = (int*) malloc(qtde_colunas_asfalto * sizeof(int));
    }

    rewind(file);

    if(file==NULL){
    
    	printf("ERRO!\n");
    } else {
        
        for(int auxLinha = 0; auxLinha < qtde_linhas_asfalto; auxLinha++){
          
          for(int auxColuna = 0; auxColuna < qtde_colunas_asfalto; auxColuna++){
     	   
               fscanf(file, "%d%*c", &matrizImagem[auxLinha][auxColuna]);
	        }
        }
    }

    sleep(1);
	printf("Preparando imagem pro ILPB...");
	sleep(1);
    calculaILBP(matrizImagem, qtde_linhas_asfalto, qtde_colunas_asfalto);

    printf("\n");

    fclose(file);
}

int main () {

	
	int qtde_linhas_grama = 0;
	int qtde_colunas_grama = 1;
	int aux  = 0;
	
	FILE *file_grama;

	
	char arquivo_grama [] = "DataSet/grass/grass_01.txt";

	int * ordemImagensAsfalto;
    int * ordemImagensGrama;

    ordemImagensAsfalto = sorteiaTesteTreino();
    sleep(1);
    ordemImagensGrama = sorteiaTesteTreino(); 

    int asfaltoTreino[NUMERO_SORTEIO];
    int asfaltoTeste[NUMERO_SORTEIO];
    int gramaTreino[NUMERO_SORTEIO];
    int gramaTeste[NUMERO_SORTEIO];

    printf("Sorteando arquivos de Treino... \n");
    for(aux = 0; aux < NUMERO_SORTEIO; aux ++){
     
        asfaltoTreino[aux] = *(ordemImagensAsfalto + aux);
        gramaTreino[aux] = *(ordemImagensGrama + aux);
    }

    sleep(1);

    printf("Sorteando arquivos de Teste...\n");
    for(; aux < MAX; aux ++){
     
        asfaltoTeste[aux - NUMERO_SORTEIO] = *(ordemImagensAsfalto + aux);
        gramaTeste[aux - NUMERO_SORTEIO] = *(ordemImagensGrama + aux);
    }

    sleep(1);
    printf("Criando arquivos...\n");

    sleep(1);
    int listaArquivosTesteGrama = salvaArquivos(gramaTeste, 0, 0);

    sleep(1);
    int listaArquivosTesteAsfalto = salvaArquivos(asfaltoTeste, 0, 1);

    sleep(1);
    int listaArquivosTreinoGrama = salvaArquivos(gramaTreino, 1, 0);

    sleep(1);
    int listaArquivosTreinoAsfalto = salvaArquivos(asfaltoTreino, 1, 1);

    char arquivoNome[50];
    char conteudoLinha[256];
    int linha, codigoArquivo;

    for (codigoArquivo = 2; codigoArquivo < 4; codigoArquivo++){
    
        for (linha = 0; linha < 25; linha++){
    
            pegaLinhaNome(codigoArquivo, linha, arquivoNome, conteudoLinha);
            sleep(1);
            armazenaArquivoMatriz(conteudoLinha);
        }
    }
}