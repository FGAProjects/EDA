#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#define MAX 50

double num_aleatorio(){

    double aleatorio = rand() % 9;
    aleatorio = aleatorio;
    return aleatorio;

}

double calcula_derivada(double n){      // derivada de 1/(1+e^(-x))

    double derivada;
    double numerador;
    double denominador;

    numerador = pow(2.71828182, (-1)*n);        
    denominador = 1 + pow(2.71828182, (-1)*n);

    derivada = numerador / pow(denominador, 2);

    return derivada;
}

int *OrdemAleatoria(){
    char *nomeasfalto;
    char *stringdovalor;
    stringdovalor = malloc(2*sizeof(char));
    int *inicializa = malloc(50*sizeof(int));

    for (int i = 0; i < 50; i++) {
        inicializa[i] = i;
    }
    for (int i = 0; i < 50; i++) {
        int temp = inicializa[i];
        int aleatorio = rand() % 50;
        inicializa[i] = inicializa[aleatorio];
        inicializa[aleatorio] = temp;
    }
    return inicializa;
}

double neuronio(double* entradas, double* pesos, double deslocamentos, int numero_de_neuronios){

    double Campo_local_induzido = 0;
    double Ativacao_logistica = 0;

    int i;

    for(i = 0; i < numero_de_neuronios; i ++){
        Campo_local_induzido = Campo_local_induzido + (entradas[i] * pesos[i]); // Cálculo do campo local induzido
    }

    Campo_local_induzido = Campo_local_induzido + deslocamentos;

    Ativacao_logistica = 1 / (1 + pow(2.71828182, (-1)*Campo_local_induzido)); // Calculo da ativação. 2.71828182 = e(numero de euler)

    return Ativacao_logistica;

}

int main(int argc, char *argv[]) {

    FILE *file;
    char nome[80];
    char valor[3];
    char string[30];
    char string_base_asfalto[20] = "Asfalto/asfalto_";
    char string_base_grama[20] = "Grama/grama_"; 
    int z;
    time_t t;
    srand((unsigned) time(&t));

    int numero_de_neuronios_ocultos = atoi(argv[1]); // Converte para int o numero inserido pelo usuario

    double* entradas = (double*)malloc(sizeof(double)*537); // Define o numero de entradas igual ao de featerues(536) + Flag para definir se é asfalto ou frama durante treinamento

    double** entradas_grama = (double**)malloc(sizeof(double*)*50);
    for(int aux = 0; aux <51; aux++){
        entradas_grama[aux] = (double*)malloc(sizeof(double)*537); // Define a quantidade de pesos que serão criados para cada neuronio baseando-se no numero de neuronios presentes na camada oculta
    }

    double** entradas_asfalto = (double**)malloc(sizeof(double*)*50);
    for(int aux = 0; aux<51;aux++){
        entradas_asfalto[aux] = (double*)malloc(sizeof(double)*537); // Define a quantidade de pesos que serão criados para cada neuronio baseando-se no numero de neuronios presentes na camada oculta
    }

    double** pesos_de_entrada = (double**)malloc(sizeof(double*)*numero_de_neuronios_ocultos);
    for(int aux = 0; aux<numero_de_neuronios_ocultos;aux++){
        pesos_de_entrada[aux] = (double*)malloc(sizeof(double)*536); // Define a quantidade de pesos que serão criados para cada neuronio baseando-se no numero de neuronios presentes na camada oculta
    }

    double* pesos_camada_oculta = (double*)malloc(sizeof(double)*numero_de_neuronios_ocultos); // Define a quantidade de pesos que serão criados para o neuronio de saída
    double* deslocamentos_camada_oculta = (double*)malloc(sizeof(double)*numero_de_neuronios_ocultos); // Define a quantidade de pesos que serão criados para o neuronio de saída


    double* neuronios_camada_oculta = (double*)malloc(sizeof(double)*numero_de_neuronios_ocultos); // Define o numero de neuronios presentes na camada oculta

    double neuronio_de_saida; // Cria o neuronio de saida

    // Carrega os valores //

    for(int auxLinha = 1; auxLinha < 51; auxLinha ++) {

    	snprintf(string, MAX, "%s%d.txt", string_base_grama, auxLinha);
        file = fopen(string,"w");

        for(int auxColuna = 0; auxColuna < 536; auxColuna ++) {

        	fscanf(file, "%lf%*c", &entradas_grama[auxLinha][auxColuna]);
        }
    }

    for(int auxLinha = 1; auxLinha < 51; auxLinha ++) {

    	snprintf(string, MAX, "%s%d.txt", string_base_asfalto, auxLinha);
        file = fopen(string,"w");

        for(int auxColuna = 0; auxColuna < 536; auxColuna ++) {

        	fscanf(file, "%lf%*c", &entradas_asfalto[auxLinha][auxColuna]);
        }
    }

	for(int aux = 0; aux <51;aux++){
         entradas_grama[aux][536] = 1; // Coloca no ultimo valor o indicativo de que é grama para ser utilizado durante treinamento
    }

    for(int aux = 0; aux<51;aux++){
         entradas_asfalto[aux][536] = 0; // Coloca no ultimo valor o indicativo de que é asfalto para ser utilizado durante treinamento
    }

    for(int auxLinha = 0; auxLinha <numero_de_neuronios_ocultos; auxLinha++){
        for(int auxColuna = 0; auxColuna<536; auxColuna++){
            pesos_de_entrada[auxLinha][auxColuna] = num_aleatorio();   // Inicia os valores dos pesos de entrada
        }
    }

    for(int auxLinha = 0; auxLinha <numero_de_neuronios_ocultos; auxLinha++){
        pesos_camada_oculta[auxLinha] = num_aleatorio();    // Inicia os valores dos pesos da camada oculta
    }

    for(int auxLinha = 0; auxLinha <numero_de_neuronios_ocultos; auxLinha++){
        deslocamentos_camada_oculta[auxLinha] = num_aleatorio();    // Inicia os valores dos pesos da camada oculta
    }

    double deslocamento_saida = num_aleatorio();

    // Gera os valores dos neuronios da camada oculta

    for(int auxLinha = 0; auxLinha <numero_de_neuronios_ocultos; auxLinha++){
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
    int i;
    int j;

    double** entrada_treinamento = (double**)malloc(sizeof(double*)*50);
    for(int aux = 0; aux<51;aux++){
        entrada_treinamento[aux] = (double*)malloc(sizeof(double)*537); // Define a quantidade de pesos que serão criados para cada neuronio baseando-se no numero de neuronios presentes na camada oculta
    }                                                                 // Possui 537 valores pois o ultimo é uma flag pra dizer se é asfalto ou grama

    double** entrada_teste = (double**)malloc(sizeof(double*)*50);
    for(int aux = 0; aux<51;aux++){
        entrada_teste[aux] = (double*)malloc(sizeof(double)*537); // Define a quantidade de pesos que serão criados para cada neuronio baseando-se no numero de neuronios presentes na camada oculta
    }

    OrdenacaoAleatoriaAsfalto = OrdemAleatoria();
    OrdenacaoAleatoriaGrama = OrdemAleatoria();
    OrdemAleatoriaTreinamento = OrdemAleatoria();

    for(i = 0; i<51;i++){
        if(i < 25){
            entrada_treinamento[i] = entradas_grama[OrdenacaoAleatoriaGrama[i]]; // Carrega no treinamento entradas de grama aleatorias
        }else{
           entrada_teste[i-25] = entradas_grama[OrdenacaoAleatoriaGrama[i]]; // Carrega no teste entradas de grama aleatorias
        }
    }

    for(i = 0; i<50;i++){
        if(i < 25){
            entrada_treinamento[i+25] = entradas_asfalto[OrdenacaoAleatoriaAsfalto[i]]; // Carrega no treinamento entradas de asfalto aleatorias
        }else{
            entrada_teste[i] = entradas_asfalto[OrdenacaoAleatoriaAsfalto[i]]; // Carrega no teste entradas de asfalto aleatorias
        }
    }

    for(z = 0; z<1000;z++){

        if(incr == 50){
        incr = 0;
        OrdemAleatoriaTreinamento = OrdemAleatoria(); // Embaralha de forma aleatória a ordem do conjunto de elementos de entrada
        }

        entradas = entrada_treinamento[OrdemAleatoriaTreinamento[incr]]; // entradas da rede neural

        Flag_ImagemGrama = entradas[536];

        if(Flag_ImagemGrama == 1){ // Flag que indica que a imagem é grama (1) ou não (0)
        erro =  1 - neuronio_de_saida; // Se for grama (Flag = 1), o valor desejado para o cálculo do erro é 1
        }
        else{
        erro =  (-1)*neuronio_de_saida; // Se for asfalto (Flag = 0), o valor desejado para o cálculo do erro é 0
        }

        for(i = 0; i < numero_de_neuronios_ocultos ; i++){
            derivada_oculta[i] = calcula_derivada(neuronios_camada_oculta[i]); // Calcula as derivadas dos valores dos neuronios na camada oculta
        }

        derivada_saida = calcula_derivada(neuronio_de_saida); // Calcula as derivadas dos valores dos neuronios na camada de saida
        
        gradiente_saida = derivada_saida*erro; // Calcula o gradiente de saida

        for(i = 0; i < numero_de_neuronios_ocultos ; i++){
            gradiente_oculta[i] = derivada_oculta[i] * gradiente_saida * pesos_camada_oculta[i]; // Calcula o gradiente da camada oculta
        }

        deslocamento_saida =  deslocamento_saida + 2 * 0.1 * 1 * gradiente_saida; // Atualiza deslocamento de saída

        for(i = 0; i <numero_de_neuronios_ocultos; i++){
            deslocamentos_camada_oculta[i] =  deslocamentos_camada_oculta[i] + (2 * 0.1 * 1 * gradiente_oculta[i]); // Atualiza deslocamento na camada oculta
        }

        for(i = 0; i <numero_de_neuronios_ocultos; i++){
           pesos_camada_oculta[i] = pesos_camada_oculta[i] + (2 * 0.1 * neuronios_camada_oculta[i] * gradiente_saida); // Atualiza pesos da camada oculta
        }

        for(i = 0; i <numero_de_neuronios_ocultos; i++){
            for(j = 0; j<536; j++){
                pesos_de_entrada[i][j] = pesos_de_entrada[i][j] + (2 * 0.1 * entradas[i] * gradiente_oculta[i]);   // Atualiza pesos da entrada
            }
        }

        for(i = 0; i <numero_de_neuronios_ocultos; i++){
            neuronios_camada_oculta[i] = neuronio(entradas, pesos_de_entrada[i],deslocamentos_camada_oculta[i], numero_de_neuronios_ocultos); // Cálculo do valor que o neuronio guardará
        }
        neuronio_de_saida = neuronio(neuronios_camada_oculta,pesos_camada_oculta,deslocamento_saida, 1); // Calcula o novo valor de saída do neuronio
        somadosquadrados = somadosquadrados + pow(erro, 2);

        if(contador == 50){
        MSE = somadosquadrados/50;
        somadosquadrados = 0;
        contador = 0;

        if(MSE < 0.2){
           // break;
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

    for(z = 0; z<50; z++){

        entradas = entrada_teste[z]; // entradas da rede neural

        for(i = 0; i <numero_de_neuronios_ocultos; i++){
            neuronios_camada_oculta[i] = neuronio(entradas, pesos_de_entrada[i],deslocamentos_camada_oculta[i], numero_de_neuronios_ocultos); // Cálculo do valor que o neuronio guardará
        }
        neuronio_de_saida = neuronio(neuronios_camada_oculta,pesos_camada_oculta,deslocamento_saida, 1); // Calcula o novo valor de saída do neuronio

        if(z<25){
            if(neuronio_de_saida > 0.5){
                acertos_grama = acertos_grama + 1;
            }else{
                falsos_erros = falsos_erros + 1;
            }

        }else{
            if(neuronio_de_saida <= 0.5){
                acertos_asfalto = acertos_asfalto + 1;
            }else{
                falsos_acertos = falsos_acertos + 1;
            }

        }

        printf("Neuronio %d valor: %lf\n", z, neuronio_de_saida);
    }

    printf("Acertos de grama: %d\n", acertos_grama);
    printf("Acertos asfalto: %d\n", acertos_asfalto);
    printf("Falsos acertos: %d\n", falsos_acertos);
    printf("Falsos erros %d\n", falsos_erros);

    return 0;
}