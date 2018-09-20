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

int* calculaDimensao(char* filename){
    int *dimensaoMatriz = (int*) calloc (2,sizeof(int));

    //printf(filename);

    FILE *arq;
    char c, end = '\n';
    int eol = 0;


    if ((arq = fopen(filename, "r")) == NULL) {
        printf("Erro ao abrir o arquivo.");
    }
    else {
        while(fread(&c, sizeof(char), 1, arq)) {
            if (c == '\n'){
              //  printf("%d",dimensaoMatriz[0]);
                dimensaoMatriz[0]++;
                eol = 1;
            }
            if(c == ';' && eol == 0){
                dimensaoMatriz[1]++;
            }
        }
    }
    dimensaoMatriz[1]++;

    sleep(1);
    printf("dimensao matriz %d\t %d", dimensaoMatriz[0], dimensaoMatriz[1]);

    fclose(arq);
    return dimensaoMatriz;
}

void calculaILBP(int *mat[], int lin, int col){
    int i = 0;
    int j = 0;

   int* ilbp = (int *)calloc(pow(2, 9), sizeof(int));
   FILE* ilbp_file;
   fopen("ilpb.txt", "w");
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

    int **matrizImagem = (int**)calloc(qtde_linhas_asfalto,sizeof(int*));

    for(int i=0; i<qtde_linhas_asfalto; i++){
    
        matrizImagem[i]=(int*)calloc(qtde_colunas_asfalto,sizeof(int));
    }

    rewind(file);

    if(file==NULL){
    
    	printf("ERRO!\n");
    } else {
        for(int i=0; i<qtde_linhas_asfalto-1; i++){
          for(int j=0; j<qtde_colunas_asfalto-1; j++){
     	       fscanf(file, "%d%*c", &matrizImagem[i][j]);
	        }
        }
    }

    for(int i=0; i<qtde_linhas_asfalto-1; i++){
        for(int j=0; j<qtde_colunas_asfalto-1; j++){
     	    printf("%d",matrizImagem[i][j]);
	    }
	        printf("\n");
    }

    sleep(1);
	printf("Preparando imagem pro ILPB...");
	sleep(1);
    calculaILBP(matrizImagem, qtde_linhas_asfalto, qtde_colunas_asfalto);

    printf("\n");

    fclose(file);

    /*
    dimensaoMatriz = calculaDimensao(filename);
    int lin = dimensaoMatriz[0];
    int col = dimensaoMatriz[1];

    FILE *file;
    file = fopen(filename, "r");

    int **matrizImagem = (int**)calloc(lin,sizeof(int*));

    for(int i=0; i<lin; i++){
        matrizImagem[i]=(int*)calloc(col,sizeof(int));
    }

    rewind(file);

    if(file==NULL){
    printf("ERRO!\n");
    } else {
        for(int i=0; i<lin-1; i++){
          for(int j=0; j<col-1; j++){
     	       fscanf(file, "%d%*c", &matrizImagem[i][j]);
	        }
        }
    }
	sleep(1);
	//printf("Preparando imagem pro ILPB...");
	sleep(1);
    calculaILBP(matrizImagem, lin, col);

    printf("\n");

    fclose(file);*/
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
	

	//IMPORTANTE PRA CARALHO

	/*int **matrizImagem = (int**)calloc(qtde_linhas_asfalto,sizeof(int*));

    for(int aux = 0; aux <qtde_linhas_asfalto; aux ++){
       
        matrizImagem[aux]=(int*)calloc(qtde_colunas_asfalto,sizeof(int));
    }

	rewind(file_asfalto);
	rewind(file_grama);

    if(file_asfalto == NULL) {
    	
    	printf("ERRO!\n");
    } else {
      	
      	for(int aux = 0; aux < qtde_linhas_asfalto - 1; aux ++){
        	
        	for(int auxColuna = 0; auxColuna < qtde_colunas_asfalto-1; qtde_colunas_asfalto++){
     	       fscanf(file, "%d%*c", &matrizImagem[i][j]);
	        }
        }
    }*/

    /*
		FAZER UM MÉTODO PRA CALCULAR A QUANTIDADE DE LINHAS E COLUNAS. DE PREFERENCIA QUE 
		RETORNE O VALOR POR REFENCIA
    */

    

	//fclose(file);

    /*char arquivoNome[50];
    char conteudoLinha[256];

    int linha, codigoArquivo;

    //treinamento do sistema

    for (codigoArquivo = 2; codigoArquivo < 4; codigoArquivo++){
        for (linha = 0; linha < 25; linha++){
            pegaLinhaNome(codigoArquivo, linha, arquivoNome, conteudoLinha);
            sleep(1);
           armazenaArquivoMatriz(conteudoLinha);
        }
    }*/

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