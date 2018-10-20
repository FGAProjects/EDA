#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct registro{

    char nome_completo[101];
    char telefone[11];
    char endereco[101];
    unsigned int cep;
    char data_nascimento[11];
    struct registro *prox;
    struct registro *ant;
};
typedef struct registro Agenda;

char *mascara(char telefone[], char formato[]);

int vazia(Agenda *agenda);
int menu();
int tamanho_lista(Agenda *agenda);

void imprime(Agenda *agenda);
void libera(Agenda *agenda);
void *busca(Agenda *agenda);


Agenda *insere_txt_na_lista();
Agenda *inicializa();
Agenda *insere(Agenda *agenda);
Agenda *apaga_contato(Agenda *agenda);
Agenda *buscaRegistro(Agenda *agenda, char nome[]);
Agenda *OrdenaCod(Agenda *Ordena);

int vazia(Agenda *agenda) {

    if(agenda->prox==NULL) {
        return 1;
    } else {
        return 0;
    }
}

Agenda *insere_txt_na_lista() {

    char arquivo [] = "contatos.txt";
    int qtdeLinhas = 0;
    int qtdeDolar = 0;
    char caracteres;
    char lixo[1];

    FILE *file;
    Agenda *agenda = NULL;
    Agenda *lista = NULL;
    Agenda *anterior = NULL;

    file = fopen(arquivo, "r");

    if(file==NULL) {

        printf("Falha!\n");
    } else {

        while((caracteres=fgetc(file))!=EOF) {

            if(caracteres=='\n'){

                qtdeLinhas++;
            } if(caracteres=='$') {

                qtdeDolar++;
            }
        }
    }

    rewind(file);

    Agenda nova_agenda[qtdeDolar];

    for(int aux = 0; aux < qtdeDolar; aux ++) {

        fscanf(file, "%[^\n]\n %[^\n]\n %[^\n]\n %d\n %[^\n]\n %[^\n]\n",
            nova_agenda[aux].nome_completo,
            nova_agenda[aux].telefone,
            nova_agenda[aux].endereco,
            &nova_agenda[aux].cep,
            nova_agenda[aux].data_nascimento,
            lixo);
    }

    fclose(file);


    for(int aux = 0; aux < qtdeDolar; aux ++) {

        agenda = malloc(sizeof(Agenda));

        strcpy(agenda->nome_completo,nova_agenda[aux].nome_completo);
        strcpy(agenda->telefone,nova_agenda[aux].telefone);
        strcpy(agenda->endereco,nova_agenda[aux].endereco);
        agenda->cep = nova_agenda[aux].cep;
        strcpy(agenda->data_nascimento,nova_agenda[aux].data_nascimento);
        agenda->prox = NULL;

        if(aux == 0) {

            lista = agenda;
        } else {

            anterior->prox = agenda;
        }

        anterior = agenda;
    }



    return lista;
}

int main(){

    Agenda *agenda = (Agenda*) malloc(sizeof(Agenda));

    if(!agenda){

        printf("Sem memória disponível!\n");
        exit(1);
    } else {

        agenda = inicializa();
        agenda = insere_txt_na_lista();

        int opt = 0;

        do {

            opt = menu();

            switch(opt) {



                case 0:
                    
                    libera(agenda);
                    break;
                case 1:

                    agenda = insere(agenda);
                    break;
                case 2:

                    agenda = apaga_contato(agenda);
                    break;
                case 3:

                    busca(agenda);
                    break;
                case 4:

                    imprime(agenda);
                    break;
                default:
                    printf("Digite uma opcao valida (:\n\n");
            }

        } while(opt);

        return 0;
    }
}

int menu() {

    int opcao = 0;

    printf("'-----------------------------'\n");
    printf("'        Bem Vindo            '\n");
    printf("'-----------------------------'\n");
    printf("Escolha alguma das opcoes:\n");
    printf("1. Adicionar um Registro\n");
    printf("2. Remover um Registro\n");
    printf("3. Buscar Registro\n");
    printf("4. Visualizar Todos os Registros\n");
    printf("0. Sair\n");
    printf("\n\nOpção: ");
    scanf("%d", &opcao);

    return opcao;
}

Agenda *inicializa() {

    return NULL;
}

Agenda *insere(Agenda *agenda) {

    Agenda *novo = (Agenda*)malloc(sizeof(Agenda));

    char nome[101];
    char telefone[10];
    char endereco[101];
    unsigned int cep;
    char dataNascimento[10];

    printf(" -----------------------------\n");
    printf("|        Novo Registro       |\n");
    printf(" -----------------------------\n");

    printf("1 - Inserir Contato\n\n");
    printf("Digite o nome:  ");
    getchar();
    scanf("%[^\n]", nome);

    printf("Numero de telefone:  ");
    getchar();
    scanf("%[^\n]", telefone);
    fflush ( stdin );

    printf("Endereco:  ");
    getchar();
    scanf("%[^\n]", endereco);

    printf("CEP:  ");
    scanf("%d", &cep);

    printf("Data de nascimento:  ");
    scanf("%s", dataNascimento);

    strcpy(novo->nome_completo,nome);
    strcpy(novo->endereco,endereco);
    novo->cep=cep;
    strcpy(novo->data_nascimento,mascara(dataNascimento,"##/##/####"));
    strcpy(novo->telefone,mascara(telefone,"#####-####"));
    novo->prox = agenda;
    novo->ant = NULL;

    if(agenda!=NULL){

        agenda->ant=novo;
    }

    printf("\n_____Contato adicionado_____\n\n\n");

    return novo;
}

void imprime(Agenda *agenda) {

    Agenda *contatos;

    if(agenda==NULL) {

        printf("\n\nNão possui nenhum registro :(\n");
    } else {

        printf("\n\nVisualizar registros:\n");
    }


    for(contatos=agenda; contatos!=NULL; contatos=contatos->prox) {

        printf("Nome: %s\n", contatos->nome_completo);
    }

    printf("\n\n\n");
}

Agenda *apaga_contato(Agenda *agenda) {

    char nome[101];

    printf(" -----------------------------\n");
    printf("|       Apagar Registro      |\n");
    printf(" -----------------------------\n");
    printf("2 - Digite o Registro Que Deseja Apagar:  ");
    getchar();
    scanf("%[^\n]", nome);

    Agenda *aux = buscaRegistro(agenda, nome);

    if(aux==NULL) {

        printf("\n\n!!! Não achou o registro solicitado.\n\n");
        return agenda;
    }

    if(agenda==aux) {

        agenda = aux->prox;
    } else {

        aux->ant->prox = aux->prox;
    }

    if(aux->prox != NULL) {

       aux->prox->ant=aux->ant;
    }

    printf("\nRegistro removido!\n\n");

    free(aux);
    return agenda;
}

void *busca(Agenda *agenda) {

    char nome[101];

    printf(" -----------------------------\n");
    printf("|        Buscar Registro      |\n");
    printf(" -----------------------------\n");
    printf("3 - Digite o registro que deseja buscar:  ");
    getchar();
    scanf("%[^\n]", nome);

    Agenda *aux;
    int achou = 0;

    for(aux=agenda; aux!=NULL; aux=aux->prox) {

        if(strcmp(aux->nome_completo, nome)==0) {

            printf("\n\nACHOUU!!<o/ \n\nNome: %s\n",aux->nome_completo);
            printf("Telefone: %s\n", aux->telefone);
            printf("Endereco: %s\n", aux->endereco);
            printf("CEP: %d\n",aux->cep);
            printf("Data de nascimento: %s \n\n\n", aux->data_nascimento);
            achou = 1;
        }
    }

    if(achou==0) {

        printf("\n\n !!! Não Foi Encontrado\n\n");
    }
}

Agenda *buscaRegistro(Agenda *agenda, char nome[]) {

    Agenda *aux;
    for(aux=agenda; aux!=NULL; aux=aux->prox) {

        if(strcmp(aux->nome_completo, nome)==0)
        return aux;
    }

    return NULL;
}


void libera(Agenda *agenda) {

    Agenda *ag;
    Agenda *p=agenda;

    char arquivo [] = "contatos.txt";
    FILE *file;

    file = fopen(arquivo, "w");
    char dolar[2];

    strcpy(dolar,"$");
    if(file==NULL) {

        printf("Falha!\n");
    } else {

          for(ag=agenda; ag!=NULL; ag=ag->prox) {

            fprintf(file,"%s\n", ag->nome_completo);
            fprintf(file,"%s\n", ag->telefone);
            fprintf(file,"%s\n", ag->endereco);
            fprintf(file, "%d\n",ag->cep);
            fprintf(file, "%s\n",ag->data_nascimento);
            fprintf(file, "%s\n", dolar);
        }
    }

    while(p!=NULL) {

        Agenda *ag = p->prox;
        free(p);
        p=ag;
    }
}

char *mascara(char telefone[], char formato[]) {
  
    char aux[11];
    int i=0;

    while(*telefone) {

        if(formato[i] != '#') {

            aux[i]=formato[i];
            i++;
        } else {

            aux[i]=*telefone;
            telefone++;
            i++;
        }
    }

    aux[i]=0;

    strcpy(telefone, aux);
    return telefone;
}

Agenda *OrdenaCod(Agenda *Ordena) {
    
    char arquivo [] = "contatos.txt";
    int qtdeLinhas = 0;
    int qtdeDolar = 0;
    char caracteres;
    char lixo[1];

    FILE *file;
    Agenda *agenda = NULL;
    Agenda *lista = NULL;
    Agenda *anterior = NULL;

    file = fopen(arquivo, "r");

    if(file==NULL) {

        printf("Falha!\n");
    } else {

        while((caracteres=fgetc(file))!=EOF) {

            if(caracteres=='\n'){

                qtdeLinhas++;
            } if(caracteres=='$') {

                qtdeDolar++;
            }
        }
    }

    rewind(file);

   int i, j;
   char aux[101];

   for (j=1; j<qtdeDolar; j++){
        for (i=j-1; i<j; i++){
            if (strcmp(Ordena[i].nome_completo, Ordena[i+1].nome_completo)>0){
                strcpy(aux, Ordena[i].nome_completo);
                strcpy(Ordena[i].nome_completo, Ordena[i+1].nome_completo);
                strcpy(Ordena[i+1].nome_completo, aux);
            }
        }
    }
}
