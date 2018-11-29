#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#define MAX 50
#define NUMERO_SORTEIO 25

int CONTADOR_ASFALTO = 1;
int CONTADOR_GRAMA = 1;

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
    free(numero_sorteado);
}

int salvaArquivos(int valor) {

    FILE *arquivo = NULL;

    char nome[20];
    char diretorio[256];
    char linha[256];
    char temp[50];

    int tipo;

    if(valor == 0) {

        strcpy(nome,"Grama/arquivos_grass.txt");
        strcpy(diretorio,"DataSet/grass/grass_");

        printf("Criando: %s \n", nome);
        arquivo = fopen(nome, "w");

        for(int aux = 0; aux < 51; aux++) {

            if(aux < 10) {

                sprintf(temp,"%s0%d.txt",diretorio,aux);
                fprintf(arquivo, "%s\n", temp);    
            } else {

                sprintf(temp,"%s%d.txt",diretorio,aux);
                fprintf(arquivo, "%s\n", temp);
            }  
        }

        tipo = 0;
    } else {

        strcpy(nome,"Asfalto/arquivos_asphalt.txt");
        strcpy(diretorio,"DataSet/asphalt/asphalt_");
        
        printf("Criando: %s \n", nome);
        arquivo = fopen(nome, "w");

        for(int aux = 0; aux < 51; aux++) {

           if(aux < 10) {

                sprintf(temp,"%s0%d.txt",diretorio,aux);
                fprintf(arquivo, "%s\n", temp);    
            } else {

                sprintf(temp,"%s%d.txt",diretorio,aux);
                fprintf(arquivo, "%s\n", temp);
            }
        }

        tipo = 1;
    }

    fclose(arquivo);
    return tipo;
}

double *normaliza(double* vetor){

    float menor = 1000;
    float maior = 0;
    float divisao;
    float conta;
    
    for(int auxLinha = 0; auxLinha < 536; auxLinha++) {
        
        if(menor > vetor[auxLinha]) {
            
            menor = vetor[auxLinha];
        }

        if(maior < vetor[auxLinha]) {
            
            maior = vetor[auxLinha];
        }
    }
    
    divisao = maior - menor;
    
    for(int auxLinha = 0; auxLinha < 536; auxLinha++) {
    
        vetor[auxLinha] = (vetor[auxLinha] - menor) / divisao;
    }

    return vetor;
}

void nomeArquivo(int codigoArquivo, char* nome){

    switch(codigoArquivo){

    	case(0):

    		strcpy(nome,"Grama/arquivos_grass.txt");
    	break;

    	case(1):

    		strcpy(nome,"Asfalto/arquivos_asphalt.txt");
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

int **desaloca_matriz(int linhas,int coluna,int **matriz) {

    for(int aux = 0; aux < linhas; aux ++) {

        free(*(matriz + aux));
    }

    free(matriz);
}


double **desaloca_matriz_double(int linhas,int coluna,double **matriz) {
    
    for(int aux = 0; aux < linhas; aux ++) {

        free(*(matriz + aux));
    }

    free(matriz);   
}

double *GLCM(int *matrizImagem[]) {

    int linha = 0;
    int coluna = 0;

    double glcmdireita[256][256];
    double glcmesquerda[256][256];
    double glcmcima[256][256];
    double glcmbaixo[256][256];
    double glcmdireitabaixo[256][256];
    double glcmesquerdabaixo[256][256];
    double glcmesquerdacima[256][256];
    double glcmdireitacima[256][256];

    for (int auxLinha = 0; auxLinha < 256; auxLinha ++) {
        
        for(int auxColuna = 0; auxColuna <256; auxColuna ++) {
           
           glcmdireita[auxLinha][auxColuna] = 0;
           glcmesquerda[auxLinha][auxColuna] = 0;
           glcmcima[auxLinha][auxColuna] = 0;
           glcmbaixo[auxLinha][auxColuna] = 0;
           glcmdireitabaixo[auxLinha][auxColuna] = 0;
           glcmdireitacima[auxLinha][auxColuna] = 0;
           glcmesquerdacima[auxLinha][auxColuna] = 0;
           glcmesquerdabaixo[auxLinha][auxColuna] = 0;
        }
    }

    linha = 1025;
    coluna = 1024;

    for (int auxLinha = 0; auxLinha < linha; auxLinha ++) {
        
        for(int auxColuna = 1; auxColuna < coluna; auxColuna ++) {
         
            glcmesquerda[matrizImagem[auxLinha][linha - auxColuna]][matrizImagem[auxLinha][coluna - auxColuna]] = 
            glcmesquerda[matrizImagem[auxLinha][linha - auxColuna]][matrizImagem[auxLinha][coluna - auxColuna]] + 1;
        }
    } 

    linha = 1025;
    coluna = 1025;

    for (int auxLinha = 0; auxLinha < linha; auxLinha ++) {
        
        for(int auxColuna = 1; auxColuna < coluna; auxColuna ++) {
            
            glcmcima[matrizImagem[linha - auxColuna][auxLinha]][matrizImagem[1024 - auxColuna][auxLinha]] = 
            glcmcima[matrizImagem[linha - auxColuna][auxLinha]][matrizImagem[1024 - auxColuna][auxLinha]] + 1;
        }
    }

    linha = 1025;
    coluna = 1025;

    for (int auxLinha = 0; auxLinha < linha; auxLinha ++) {
        
        for(int auxColuna = 1; auxColuna < coluna; auxColuna ++) {
        
            glcmcima[matrizImagem[1025 - auxColuna][auxLinha]][matrizImagem[1024 - auxColuna][auxLinha]] = 
            glcmcima[matrizImagem[1025 - auxColuna][auxLinha]][matrizImagem[1024 - auxColuna][auxLinha]] + 1;
        }
    }

    linha = 1025;
    coluna = 1024;

    for (int auxLinha = 0; auxLinha < 1025; auxLinha ++) {
        
        for(int auxColuna = 0; auxColuna < 1024; auxColuna ++) {
            
            glcmbaixo[matrizImagem[auxColuna][auxLinha]][matrizImagem[auxColuna + 1][auxLinha]] = 
            glcmbaixo[matrizImagem[auxColuna][auxLinha]][matrizImagem[auxColuna + 1][auxLinha]] + 1;
        }
    }

    linha = 1024;
    coluna = 1024;

    for (int auxLinha = 0; auxLinha < linha; auxLinha ++) {
        
        for(int auxColuna = 0; auxColuna < coluna; auxColuna ++) {
        
            glcmdireitabaixo[matrizImagem[auxColuna][auxLinha]][matrizImagem[auxColuna + 1][auxColuna + 1]] = 
            glcmdireitabaixo[matrizImagem[auxColuna][auxLinha]][matrizImagem[auxColuna + 1][auxLinha + 1]] + 1;
        }
    }

    linha = 1025;
    coluna = 1024;

    for (int auxLinha = 1; auxLinha < linha; auxLinha ++) {
        
        for(int auxColuna = 0; auxColuna < coluna; auxColuna ++) {
        
            glcmesquerdabaixo[matrizImagem[auxColuna][1025 - auxLinha]][matrizImagem[auxColuna + 1][1024 - auxLinha]] = 
            glcmesquerdabaixo[matrizImagem[auxColuna][1025 - auxLinha]][matrizImagem[auxColuna + 1][1024 - auxLinha]] + 1;
        }
    }

    linha = 1025;
    coluna = 1025;

    for (int auxLinha = 1; auxLinha < linha; auxLinha++) {
        
        for(int auxColuna = 1; auxColuna < coluna; auxColuna ++) {
     
           glcmesquerdacima[matrizImagem[1025 - auxColuna][1025 - auxLinha]][matrizImagem[1024 - auxColuna][1024 - auxLinha]] = 
           glcmesquerdacima[matrizImagem[1025 - auxColuna][1025 - auxLinha]][matrizImagem[1024 - auxColuna][1024 - auxLinha]] + 1;
        }
    }

    linha = 1024;
    coluna = 1025;

    for (int auxLinha = 0; auxLinha < linha; auxLinha ++) {
        for(int auxColuna = 1; auxColuna < coluna; auxColuna ++) {
        
            glcmdireitacima[matrizImagem[1025 - auxColuna][auxLinha]][matrizImagem[1024 - auxColuna][auxLinha + 1]] = 
            glcmdireitacima[matrizImagem[1025 - auxColuna][auxLinha]][matrizImagem[1024 - auxColuna][auxLinha + 1]] + 1;
        }
    }

    double energia[8];
    double contraste[8];
    double homogeneidade[8];
    double modulo;
    double d,n,m;

    for(int auxLinha = 0; auxLinha < 8; auxLinha++) {

        energia[auxLinha] = 0;
        contraste[auxLinha] = 0;
        homogeneidade[auxLinha] = 0;
    }

    for(int auxLinha = 0; auxLinha < 256; auxLinha++) {
        
        for(int auxColuna = 0; auxColuna < 256; auxColuna++) {

            if(auxColuna > auxLinha) {
                
                modulo = -1;
            } else{
                
                modulo = 1;
            }
    
            d = (auxLinha - auxColuna);

            n = d*d;
            m = 1 + (d * modulo);

            energia[0] = energia[0] + glcmdireita[auxLinha][auxColuna] * glcmdireita[auxLinha][auxColuna];
            energia[1] = energia[1] + glcmesquerda[auxLinha][auxColuna] * glcmesquerda[auxLinha][auxColuna];
            energia[2] = energia[2] + glcmcima[auxLinha][auxColuna] * glcmcima[auxLinha][auxColuna];
            energia[3] = energia[3] + glcmbaixo[auxLinha][auxColuna] * glcmbaixo[auxLinha][auxColuna];
            energia[4] = energia[4] + glcmdireitabaixo[auxLinha][auxColuna] * glcmdireitabaixo[auxLinha][auxColuna];
            energia[5] = energia[5] + glcmesquerdabaixo[auxLinha][auxColuna] * glcmesquerdabaixo[auxLinha][auxColuna];
            energia[6] = energia[6] + glcmesquerdacima[auxLinha][auxColuna] * glcmesquerdacima[auxLinha][auxColuna];
            energia[7] = energia[7] + glcmdireitacima[auxLinha][auxColuna] * glcmdireitacima[auxLinha][auxColuna];

            contraste[0] = contraste[0] + n * glcmdireita[auxLinha][auxColuna];
            contraste[1] = contraste[1] + n*glcmesquerda[auxLinha][auxColuna];
            contraste[2] = contraste[2] + n*glcmcima[auxLinha][auxColuna];
            contraste[3] = contraste[3] + n*glcmbaixo[auxLinha][auxColuna];
            contraste[4] = contraste[4] + n*glcmdireitabaixo[auxLinha][auxColuna];
            contraste[5] = contraste[5] + n*glcmesquerdabaixo[auxLinha][auxColuna];
            contraste[6] = contraste[6] + n*glcmesquerdacima[auxLinha][auxColuna];
            contraste[7] = contraste[7] + n*glcmdireitacima[auxLinha][auxColuna];

            homogeneidade[0] = homogeneidade[0] + ((double)glcmdireita[auxLinha][auxColuna] / m);
            homogeneidade[1] = homogeneidade[1] + ((double)glcmesquerda[auxLinha][auxColuna] / m);
            homogeneidade[2] = homogeneidade[2] + ((double)glcmcima[auxLinha][auxColuna] / m);
            homogeneidade[3] = homogeneidade[3] + ((double)glcmbaixo[auxLinha][auxColuna] / m);
            homogeneidade[4] = homogeneidade[4] + ((double)glcmdireitabaixo[auxLinha][auxColuna] / m);
            homogeneidade[5] = homogeneidade[5] + ((double)glcmesquerdabaixo[auxLinha][auxColuna] / m);
            homogeneidade[6] = homogeneidade[6] + ((double)glcmesquerdacima[auxLinha][auxColuna] / m);
            homogeneidade[7] = homogeneidade[7] + ((double)glcmdireitacima[auxLinha][auxColuna] / m);
        }
    }

    double *retorna = malloc(sizeof(double) * 24);

    for(int auxLinha = 0; auxLinha < 8; auxLinha ++) {
        
        retorna[auxLinha] = energia[auxLinha];
    }

    for(int auxLinha = 0; auxLinha < 8; auxLinha ++) {
    
        retorna[auxLinha + 8] = contraste[auxLinha];
    }

    for(int auxLinha = 0; auxLinha < 8; auxLinha ++) {
    
        retorna[auxLinha + 16] = homogeneidade[auxLinha];
    }

    return retorna;

    free(retorna);
}

int ILBP(int **matrizImagem, int linha, int coluna) {

    int ILBP[9];
    float media;
    float matriz[3][3];
    int  matriztemp[3][3];

    media = (matrizImagem[linha - 1][coluna - 1] + matrizImagem[linha - 1][coluna] + matrizImagem[linha - 1][coluna + 1] + matrizImagem[linha][coluna - 1] +
    matrizImagem[linha][coluna] + matrizImagem[linha][coluna + 1] + matrizImagem[linha + 1][coluna - 1] + matrizImagem[linha + 1][coluna] + matrizImagem[linha + 1][coluna + 1])/9;

    if((matrizImagem[linha - 1][coluna - 1] - media) >= 0) {
        
        matriztemp[0][0] = 1;
    } else {
        matriztemp[0][0] = 0;
    }

    if((matrizImagem[linha - 1][coluna] - media) >= 0) {
        
        matriztemp[0][1] = 1;
    }else {
        matriztemp[0][1] = 0;
    }

    if((matrizImagem[linha - 1][coluna + 1] - media) >= 0) {
        
        matriztemp[0][2] = 1;
    }else {
        matriztemp[0][2] = 0;
    }
    
    if((matrizImagem[linha][coluna - 1] - media) >= 0) {
        
        matriztemp[1][0] = 1;
    }else {
    
        matriztemp[1][0] = 0;
    }
    
    if((matrizImagem[linha][coluna] - media) >= 0) {
        
        matriztemp[1][1] = 1;
    }else {
    
        matriztemp[1][1] = 0;
    }
    
    if((matrizImagem[linha][coluna + 1] - media) >= 0) {
        
        matriztemp[1][2] = 1;
    }else {
    
        matriztemp[1][2] = 0;
    }
    
    if((matrizImagem[linha + 1][coluna - 1] - media) >= 0) {

        matriztemp[2][0] = 1;
    }else {
    
        matriztemp[2][0] = 0;
    }
    if((matrizImagem[linha + 1][coluna] - media) >= 0) {

        matriztemp[2][1] = 1;
    }else {
    
        matriztemp[2][1] = 0;
    }
    
    if((matrizImagem[linha + 1][coluna + 1] - media) >= 0) {

        matriztemp[2][2] = 1;
    }else {

        matriztemp[2][2] = 0;
    }

    ILBP[0] = matrizImagem[0][0];
    ILBP[1] = matrizImagem[0][1];
    ILBP[2] = matrizImagem[0][2];
    ILBP[3] = matrizImagem[1][2];
    ILBP[4] = matrizImagem[2][2];
    ILBP[5] = matrizImagem[2][1];
    ILBP[6] = matrizImagem[2][0];
    ILBP[7] = matrizImagem[1][0];
    ILBP[8] = matrizImagem[1][1];

    //---------------------------- rotação ---------------------------//

    int menorvalor[9];

    int ILBP1[9];

    ILBP1[0] = ILBP[8];
    ILBP1[1] = ILBP[0];
    ILBP1[2] = ILBP[1];
    ILBP1[3] = ILBP[2];
    ILBP1[4] = ILBP[3];
    ILBP1[5] = ILBP[4];
    ILBP1[6] = ILBP[5];
    ILBP1[7] = ILBP[6];
    ILBP1[8] = ILBP[7];

    int valor = 0;
    for(int aux = 0; aux < 9; aux ++) {
    
        if(ILBP[8 - aux] == 1) {  
    
            valor = valor + pow(2, aux);
        }
    }

    menorvalor[8] = valor;
    valor = 0;
    
    for(int aux = 0; aux < 9; aux ++) {
    
        if(ILBP1[8 - aux] == 1) {  
    
            valor = valor + pow(2, aux);
        }
    }

    menorvalor[0] = valor;

    ILBP1[0] = ILBP[7];
    ILBP1[1] = ILBP[8];
    ILBP1[2] = ILBP[0];
    ILBP1[3] = ILBP[1];
    ILBP1[4] = ILBP[2];
    ILBP1[5] = ILBP[3];
    ILBP1[6] = ILBP[4];
    ILBP1[7] = ILBP[5];
    ILBP1[8] = ILBP[6];

    valor = 0;
    
    for(int aux = 0; aux < 9; aux ++) {
    
        if(ILBP1[8 - aux] == 1) {  
            
            valor = valor + pow(2, aux);
        }
    }
    menorvalor[1] = valor;

    ILBP1[0] = ILBP[6];
    ILBP1[1] = ILBP[7];
    ILBP1[2] = ILBP[8];
    ILBP1[3] = ILBP[0];
    ILBP1[4] = ILBP[1];
    ILBP1[5] = ILBP[2];
    ILBP1[6] = ILBP[3];
    ILBP1[7] = ILBP[4];
    ILBP1[8] = ILBP[5];

    valor = 0;
    
    for(int aux = 0; aux < 9; aux ++) {
    
        if(ILBP1[8 - aux] == 1) {  
    
            valor = valor + pow(2, aux);
        }
    }
    menorvalor[2] = valor;

    ILBP1[0] = ILBP[5];
    ILBP1[1] = ILBP[6];
    ILBP1[2] = ILBP[7];
    ILBP1[3] = ILBP[8];
    ILBP1[4] = ILBP[0];
    ILBP1[5] = ILBP[1];
    ILBP1[6] = ILBP[2];
    ILBP1[7] = ILBP[3];
    ILBP1[8] = ILBP[4];

    valor = 0;
    for(int aux = 0; aux < 9; aux++) {
        
        if(ILBP1[8 - aux] == 1) {  
        
            valor = valor + pow(2, aux);
        }
    }
    menorvalor[3] = valor;

    ILBP1[0] = ILBP[4];
    ILBP1[1] = ILBP[5];
    ILBP1[2] = ILBP[6];
    ILBP1[3] = ILBP[7];
    ILBP1[4] = ILBP[8];
    ILBP1[5] = ILBP[0];
    ILBP1[6] = ILBP[1];
    ILBP1[7] = ILBP[2];
    ILBP1[8] = ILBP[3];

    valor = 0;
    for(int aux = 0; aux < 9; aux ++) {
        
        if(ILBP1[8 - aux] == 1) {  
        
            valor = valor + pow(2, aux);
        }
    }
    menorvalor[4] = valor;

    ILBP1[0] = ILBP[3];
    ILBP1[1] = ILBP[4];
    ILBP1[2] = ILBP[5];
    ILBP1[3] = ILBP[6];
    ILBP1[4] = ILBP[7];
    ILBP1[5] = ILBP[8];
    ILBP1[6] = ILBP[0];
    ILBP1[7] = ILBP[1];
    ILBP1[8] = ILBP[2];

    valor = 0;
    for(int aux = 0; aux < 9; aux ++) {
    
        if(ILBP1[8 - aux] == 1) {  
            
            valor = valor + pow(2, aux);
        }
    }
    menorvalor[5] = valor;

    ILBP1[0] = ILBP[2];
    ILBP1[1] = ILBP[3];
    ILBP1[2] = ILBP[4];
    ILBP1[3] = ILBP[5];
    ILBP1[4] = ILBP[6];
    ILBP1[5] = ILBP[7];
    ILBP1[6] = ILBP[8];
    ILBP1[7] = ILBP[0];
    ILBP1[8] = ILBP[1];

    valor = 0;
    for(int aux = 0; aux < 9; aux ++) {
    
        if(ILBP1[8 - aux] == 1) {  
    
            valor = valor + pow(2, aux);
        }
    }
    menorvalor[6] = valor;

    ILBP1[0] = ILBP[1];
    ILBP1[1] = ILBP[2];
    ILBP1[2] = ILBP[3];
    ILBP1[3] = ILBP[4];
    ILBP1[4] = ILBP[5];
    ILBP1[5] = ILBP[6];
    ILBP1[6] = ILBP[7];
    ILBP1[7] = ILBP[8];
    ILBP1[8] = ILBP[0];

    valor = 0;
    for(int aux = 0; aux < 9; aux ++) {
    
        if(ILBP1[8 - aux] == 1) {  
            
            valor = valor + pow(2, aux);
        }
    }
    menorvalor[7] = valor;

    int menorILBP = 100000;

    for(int aux = 0; aux < 9; aux ++) {

        if(menorILBP > menorvalor[aux]) {

            menorILBP = menorvalor[aux];
        }
    }

    return menorILBP;
}

double *armazenaArquivoMatriz(char* filename){

    FILE *file_asfalto;

    char string[50];
    char grass[6] = "grass";
    char asphalt[8] = "asphalt";
    char string_base_asfalto[20] = "Asfalto/asfalto_";
    char string_base_grama[20] = "Grama/grama_"; 
	char caractere;
	char arquivo_asfalto [] = "DataSet/asphalt/asphalt_01.txt";
    
    int histograma[512];
    int qtde_linhas_asfalto = 0;
    int qtde_colunas_asfalto = 1;
    int ILBP_imagem;
    int contador = 1;

    double *VetorCompleto = malloc (sizeof(double) * 536);
    double *VetorNormalizado = malloc (sizeof(double) * 536);
    double *GLCM_imagem;

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

    if(file == NULL){

    	printf("ERRO!\n");
    } else {

        for(int auxLinha = 0; auxLinha < qtde_linhas_asfalto; auxLinha++){

          for(int auxColuna = 0; auxColuna < qtde_colunas_asfalto; auxColuna++){

               fscanf(file, "%d%*c", &matrizImagem[auxLinha][auxColuna]);
	        }
        }
    }

    printf("\n");

    fclose(file);

    sleep(1);
	printf("Preparando imagem pro ILPB...");
	sleep(1);

    GLCM_imagem = GLCM(matrizImagem); 

    qtde_linhas_asfalto -= 1;
    qtde_colunas_asfalto -=1;

    for(int auxLinha = 1; auxLinha < qtde_linhas_asfalto; auxLinha ++) {
        
        for(int auxColuna = 1; auxColuna < qtde_colunas_asfalto; auxColuna ++) {

            ILBP_imagem = ILBP(matrizImagem,auxLinha,auxColuna);
            histograma[ILBP_imagem] =  histograma[ILBP_imagem] + 1;
        }
    }

    desaloca_matriz(qtde_linhas_asfalto,qtde_colunas_asfalto,matrizImagem);

    for(int auxLinha = 0; auxLinha < 512; auxLinha ++) {

        VetorCompleto[auxLinha] = histograma[auxLinha];
    }

    for(int auxLinha = 0; auxLinha < 24; auxLinha ++) {

        VetorCompleto[512 + auxLinha] = GLCM_imagem[auxLinha];
    }

    VetorNormalizado = normaliza(VetorCompleto);

    FILE *grama_file;
    FILE *asfalto_file;

    // char string[50];
    // char string_base_asfalto[20] = "Asfalto/asfalto_";
    // char string_base_grama[20] = "Grama/grama_"; 


    if(CONTADOR_ASFALTO <= 50){

        snprintf(string, MAX, "%s%d.txt", string_base_asfalto, CONTADOR_ASFALTO);
        printf("%s\n", string);
        asfalto_file = fopen(string,"w");
      

        for(int aux = 0; aux < 536; aux ++) {

            fprintf(asfalto_file, "%lf\n", VetorNormalizado[aux]);

        }

        CONTADOR_ASFALTO++;

    }

    else if(CONTADOR_GRAMA <=50){

        snprintf(string, MAX, "%s%d.txt", string_base_grama, CONTADOR_GRAMA);
        printf("%s\n", string);
        grama_file = fopen(string,"w");

        for(int aux = 0; aux < 536; aux ++) {

            fprintf(asfalto_file,"%lf\n", VetorNormalizado[aux]);

        }

        CONTADOR_GRAMA++;
    }

    

    for(int aux = 0; aux < 536; aux ++) {


        printf("%lf\n", VetorNormalizado[aux]);
    }

    return VetorNormalizado;
    fclose(asfalto_file);
    fclose(grama_file);

    free(VetorNormalizado);
    free(VetorCompleto);
}

int main () {

	FILE *file;

    // char string[50];
    // char string_base_asfalto[20] = "Asfalto/asfalto_";
    // char string_base_grama[20] = "Grama/grama_"; 

    // //Asfalto
    // for(int aux = 1; aux < 51; aux ++) {

    //     snprintf(string, MAX, "%s%d.txt", string_base_asfalto, aux);
    //     printf("%s\n", string);
    //     file = fopen(string,"w");
    //     fprintf(file, *armazenaArquivoMatriz);
    // }

    // //Grama
    // for(int aux = 1; aux < 51; aux ++) {

    //     snprintf(string, MAX, "%s%d.txt", string_base_grama, aux);
    //     printf("%s\n", string);
    //     file = fopen(string,"w");
    // }

    // fclose(file);

    sleep(1);
    printf("Criando arquivos...\n");

    sleep(1);
    int listaArquivosGrama = salvaArquivos(0);

    sleep(1);
    int listaArquivosAsfalto = salvaArquivos(1);

    char arquivoNome[MAX];
    char conteudoLinha[256];
    int linha, codigoArquivo;

    for (codigoArquivo = 0; codigoArquivo <= 1; codigoArquivo++){

        for (linha = 1; linha < 51; linha++){

            pegaLinhaNome(codigoArquivo, linha, arquivoNome, conteudoLinha);
            sleep(1);
            armazenaArquivoMatriz(conteudoLinha);
        }
    }
}
