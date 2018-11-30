#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#define MAX 50

double num_aleatorio() {

    double aleatorio = rand() % 9;
    aleatorio = aleatorio;
    return aleatorio;
}

double derivada(double valor) {      

    double derivada;
    double numerador;
    double denominador;

    numerador = pow(2.71828182, (-1) * valor);        
    denominador = 1 + pow(2.71828182, (-1) * valor);

    derivada = numerador / pow(denominador, 2);

    return derivada;
}

int *OrdemAleatoria() {

    char *nomeasfalto;
    char *stringdovalor;
    stringdovalor = malloc(2 * sizeof(char));
    int *inicializa = malloc(50 * sizeof(int));

    for (int aux = 0; aux < 50; aux ++) {
    	
    	inicializa[aux] = aux;
    }

    for (int aux = 0; aux < 50; aux ++) {
        
        int temp = inicializa[aux];
        int aleatorio = rand() % 50;
        inicializa[aux] = inicializa[aleatorio];
        inicializa[aleatorio] = temp;
    }
    return inicializa;
}

double neuronio(double* entradas, double* pesos, double deslocamentos, int numero_de_neuronios) {

    double Campo_local_induzido = 0;
    double Ativacao_logistica = 0;

    for(int aux = 0; aux < numero_de_neuronios; aux ++) {

        Campo_local_induzido = Campo_local_induzido + (entradas[aux] * pesos[aux]);
    }

    Campo_local_induzido = Campo_local_induzido + deslocamentos;

    Ativacao_logistica = 1 / (1 + pow(2.71828182, (-1) * Campo_local_induzido)); 

    return Ativacao_logistica;
}

int main(int argc, char *argv[]) {

    FILE *file;
    char nome[80];
    char valor[3];
    char string[30];
    char string_base_asfalto[20] = "Asfalto/asfalto_";
    char string_base_grama[20] = "Grama/grama_"; 
    time_t t;
    srand((unsigned) time(&t));

    int numero_de_neuronios_ocultos = atoi(argv[1]); 

    double* entradas = (double*)malloc(sizeof(double)*537); 

    double** entradas_grama = (double**)malloc(sizeof(double*)*50);
    
    for(int aux = 0; aux <51; aux++) {
        
    	entradas_grama[aux] = (double*)malloc(sizeof(double)*537); 
    }

    double** entradas_asfalto = (double**)malloc(sizeof(double*)*50);
    
    for(int aux = 0; aux<51;aux++){
        
        entradas_asfalto[aux] = (double*)malloc(sizeof(double)*537); 
    }

    double** pesos_de_entrada = (double**)malloc(sizeof(double*)*numero_de_neuronios_ocultos);
    
    for(int aux = 0; aux<numero_de_neuronios_ocultos;aux++){
        
        pesos_de_entrada[aux] = (double*)malloc(sizeof(double)*536); 
    }

    double* pesos_camada_oculta = (double*)malloc(sizeof(double)*numero_de_neuronios_ocultos); 
    double* deslocamentos_camada_oculta = (double*)malloc(sizeof(double)*numero_de_neuronios_ocultos); 
    double* neuronios_camada_oculta = (double*)malloc(sizeof(double)*numero_de_neuronios_ocultos); 
    double neuronio_de_saida; 

    for(int auxLinha = 1; auxLinha < 51; auxLinha ++) {

    	snprintf(string, MAX, "%s%d.txt", string_base_grama, auxLinha);
        file = fopen(string,"r");

        for(int auxColuna = 0; auxColuna < 536; auxColuna ++) {

        	fscanf(file, "%lf%*c", &entradas_grama[auxLinha][auxColuna]);
        }
    }

    for(int auxLinha = 1; auxLinha < 51; auxLinha ++) {

    	snprintf(string, MAX, "%s%d.txt", string_base_asfalto, auxLinha);
        file = fopen(string,"r");

        for(int auxColuna = 0; auxColuna < 536; auxColuna ++) {

        	fscanf(file, "%lf%*c", &entradas_asfalto[auxLinha][auxColuna]);
        }
    }

    fclose(file);

	for(int aux = 0; aux < 51; aux++) {
        
        entradas_grama[aux][536] = 1; 
        
        entradas_asfalto[aux][536] = 0; 
    }

    for(int auxLinha = 0; auxLinha < numero_de_neuronios_ocultos; auxLinha++) {
        
        for(int auxColuna = 0; auxColuna < 536; auxColuna++) {
        
            pesos_de_entrada[auxLinha][auxColuna] = num_aleatorio(); 
        }
    }

    for(int auxLinha = 0; auxLinha < numero_de_neuronios_ocultos; auxLinha++) {
        
        pesos_camada_oculta[auxLinha] = num_aleatorio(); 
        
        deslocamentos_camada_oculta[auxLinha] = num_aleatorio();   
    }

    double deslocamento_saida = num_aleatorio();

    for(int auxLinha = 0; auxLinha < numero_de_neuronios_ocultos; auxLinha++) {
        
        neuronios_camada_oculta[auxLinha] = neuronio(entradas, pesos_de_entrada[auxLinha],deslocamentos_camada_oculta[auxLinha], numero_de_neuronios_ocultos); // Cálculo do valor que o neuronio guardará
    }    

    neuronio_de_saida = neuronio(neuronios_camada_oculta,pesos_camada_oculta,deslocamento_saida, 1);

    // Treinamento 

    int* OrdenacaoAleatoriaAsfalto;
    int* OrdenacaoAleatoriaGrama;
    int* OrdemAleatoriaTreinamento;
    double somadosquadrados = 0;
    double MSE;
    double erro;
    double derivada_oculta[536];
    double derivada_saida;
    double gradiente_saida;
    double gradiente_oculta[536];
    int Flag_ImagemGrama;
    int incr = 0;
    int contador = 0;

    double** entrada_treinamento = (double**)malloc(sizeof(double*)*50);
    for(int aux = 0; aux < 51; aux++) {
        
        entrada_treinamento[aux] = (double*)malloc(sizeof(double)*537); 
    }                                                                 

    double** entrada_teste = (double**)malloc(sizeof(double*)*50);
    for(int aux = 0; aux < 51; aux++) {
        
        entrada_teste[aux] = (double*)malloc(sizeof(double)*537); 
    }

    OrdenacaoAleatoriaAsfalto = OrdemAleatoria();
    OrdenacaoAleatoriaGrama = OrdemAleatoria();
    OrdemAleatoriaTreinamento = OrdemAleatoria();

    for(int aux = 0; aux < 51; aux++) {

        if(aux < 25) {
            
            entrada_treinamento[aux] = entradas_grama[OrdenacaoAleatoriaGrama[aux]]; 
        }else {
           	
           	entrada_teste[aux - 25] = entradas_grama[OrdenacaoAleatoriaGrama[aux]]; 
        }
    }

    for(int aux = 0; aux < 50; aux++) {

        if(aux < 25) {

            entrada_treinamento[aux + 25] = entradas_asfalto[OrdenacaoAleatoriaAsfalto[aux]]; 
        }else{
            
            entrada_teste[aux] = entradas_asfalto[OrdenacaoAleatoriaAsfalto[aux]]; 
        }
    }

    for(int aux = 0; aux < 1000; aux++) {

        if(incr == 50) {

        	incr = 0;
        	OrdemAleatoriaTreinamento = OrdemAleatoria(); 
        }

        entradas = entrada_treinamento[OrdemAleatoriaTreinamento[incr]]; 

        Flag_ImagemGrama = entradas[536];

        if(Flag_ImagemGrama == 1) { 
        	
        	erro =  1 - neuronio_de_saida; // Se for grama (Flag = 1), o valor desejado para o cálculo do erro é 1
        } else {
        
        	erro =  (-1) * neuronio_de_saida; // Se for asfalto (Flag = 0), o valor desejado para o cálculo do erro é 0
        }

        for(int newAux = 0; newAux < numero_de_neuronios_ocultos; newAux++) {
            
            derivada_oculta[newAux] = derivada(neuronios_camada_oculta[newAux]); 
        }

        derivada_saida = derivada(neuronio_de_saida); 
        
        gradiente_saida = derivada_saida*erro; 

        for(int newAux = 0; newAux < numero_de_neuronios_ocultos; newAux++) {
            
            gradiente_oculta[newAux] = derivada_oculta[newAux] * gradiente_saida * pesos_camada_oculta[newAux]; 
        }

        deslocamento_saida =  deslocamento_saida + 2 * 0.1 * 1 * gradiente_saida; 

        for(int newAux = 0; newAux < numero_de_neuronios_ocultos; newAux++) {
            
            deslocamentos_camada_oculta[newAux] =  deslocamentos_camada_oculta[newAux] + (2 * 0.1 * 1 * gradiente_oculta[newAux]); 
        }

        for(int newAux = 0; newAux < numero_de_neuronios_ocultos; newAux++) {
           
           pesos_camada_oculta[newAux] = pesos_camada_oculta[newAux] + (2 * 0.1 * neuronios_camada_oculta[newAux] * gradiente_saida); 
        }

        for(int newAuxLinha = 0; newAuxLinha < numero_de_neuronios_ocultos; newAuxLinha++) {
            
            for(int newAuxColuna = 0; newAuxColuna < 536; newAuxColuna++) {
                
                pesos_de_entrada[newAuxLinha][newAuxColuna] = pesos_de_entrada[newAuxLinha][newAuxColuna] + (2 * 0.1 * entradas[newAuxLinha] * gradiente_oculta[newAuxLinha]);   
            }
        }

        for(int newAux = 0; newAux < numero_de_neuronios_ocultos; newAux++) {
            
            neuronios_camada_oculta[newAux] = neuronio(entradas, pesos_de_entrada[newAux],deslocamentos_camada_oculta[newAux], numero_de_neuronios_ocultos); 
        }

        neuronio_de_saida = neuronio(neuronios_camada_oculta,pesos_camada_oculta,deslocamento_saida, 1); 
        somadosquadrados = somadosquadrados + pow(erro, 2);

        if(contador == 50) {
        
        	MSE = somadosquadrados/50;
        	somadosquadrados = 0;
        	contador = 0;

	        if(MSE < 0.2) {
	           
	        }
        }
        incr++;
        contador++;
    }

    // Testes

    int acertos_grama = 0;
    int falsos_erros = 0;
    int acertos_asfalto = 0;
    int falsos_acertos = 0;

    for(int auxLinha = 0; auxLinha < 50; auxLinha++) {

        entradas = entrada_teste[auxLinha]; 

        for(int auxColuna = 0; auxColuna < numero_de_neuronios_ocultos; auxColuna++) {
            
            neuronios_camada_oculta[auxColuna] = neuronio(entradas, pesos_de_entrada[auxColuna],deslocamentos_camada_oculta[auxColuna], numero_de_neuronios_ocultos); 
        }

        neuronio_de_saida = neuronio(neuronios_camada_oculta,pesos_camada_oculta,deslocamento_saida, 1); // Calcula o novo valor de saída do neuronio

        if(auxLinha < 25) {
            
            if(neuronio_de_saida > 0.5) {
                
                acertos_grama = acertos_grama + 1;
            }else {
                
                falsos_erros = falsos_erros + 1;
            }

        }else{
            
            if(neuronio_de_saida <= 0.5) {
                
                acertos_asfalto = acertos_asfalto + 1;
            }else {
                
                falsos_acertos = falsos_acertos + 1;
            }
        }
    }

    printf("Acertos de grama: %d\n", acertos_grama);
    printf("Acertos asfalto: %d\n", acertos_asfalto);
    printf("Falsos acertos: %d\n", falsos_acertos);
    printf("Falsos erros %d\n", falsos_erros);

    return 0;
}
