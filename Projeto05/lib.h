#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_HEIGHT 1000
#define INFINITY (1<<20)

int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
int gap = 3;
int print_next;

typedef struct arvore {
  
    int valor;
    int altura;
    struct arvore* direita; 
    struct arvore* esquerda; 
} Arvore;

Arvore* libera(Arvore* arvore) {

    if (arvore != NULL) {
    
        libera(arvore->esquerda);
        libera(arvore->direita);
        free(arvore);
    }

    return NULL;
}

Arvore* cria_arvore() {
    
    return NULL;
}

int arvore_vazia(Arvore* arvore) {
  
    return arvore == NULL;
}

Arvore* insere(Arvore** arvore, int valor) {
  
    if(*arvore == NULL) {
      
        *arvore = (Arvore*)malloc(sizeof(Arvore)); 
        (*arvore)->esquerda = NULL; 
        (*arvore)->direita = NULL; 
        (*arvore)->valor = valor; 
    } else {

        if(valor < (*arvore)->valor) {

            insere(&(*arvore)->esquerda, valor);
        }

        if(valor > (*arvore)->valor) {

            insere(&(*arvore)->direita, valor);
        }
    }
}

int maior(int a, int b) {

    if(a > b)
        return a;
    else
        return b;
}

/* Acha a altura da arvore */
int height(Arvore *arvore) {
    
    if (arvore == NULL) {
        
        return 0;
    }

    return arvore->altura;
}

/*Acha elemento */
Arvore *find(int elem, Arvore *arvore) {
    
    if (arvore == NULL){
    
        return NULL;
    }

    if (elem < arvore->valor) {
    
        return find(elem, arvore->esquerda);
    } else if (elem > arvore->valor) {
    
        return find(elem, arvore->direita);
    } else {
    
        return arvore;
    }
}

Arvore *find_min(Arvore *arvore) {

    if (arvore == NULL){
    
        return NULL;
    } else if (arvore->esquerda == NULL) {
    
        return arvore;
    } else {
    
        return find_min(arvore->esquerda);
    }
}

Arvore * delete(int valor, Arvore * arvore) {
  
    Arvore *tmp_cell;

    if (arvore==NULL) {

        return NULL;
    }

    if (valor < arvore->valor) {
    
        arvore->esquerda = delete(valor, arvore->esquerda);
    } else if (valor > arvore->valor) {
    
        arvore->direita = delete(valor, arvore->direita);
    } else if (arvore->esquerda && arvore->direita) {
    
        tmp_cell = find_min(arvore->direita);
        arvore->valor = tmp_cell->valor;
        arvore->direita = delete(arvore->valor, arvore->direita);
    } else {
        
        tmp_cell = arvore;
        
        if (arvore->esquerda == NULL) {
        
           arvore = arvore->direita;
        } else if (arvore->direita == NULL) {
        
            arvore = arvore->esquerda;
        }
        free(tmp_cell);
    }

    return arvore;
}

typedef struct asciinode_struct asciinode;

struct asciinode_struct {
    
    asciinode * esquerda, * direita;

    int comprimento; 
    int altura; 
    int lablen;
    int parent_dir;
    char label[11];
};


int MIN (int X, int Y) {
  
    return ((X) < (Y)) ? (X) : (Y);
}

int MAX (int X, int Y) {
    
    return ((X) > (Y)) ? (X) : (Y);
}

asciinode * build_ascii_tree_recursive(Arvore* arvore) {
    
    asciinode * node;

    if (arvore == NULL) {

        return NULL;  
    } 

    node = malloc(sizeof(asciinode));
    node->esquerda = build_ascii_tree_recursive(arvore->esquerda);
    node->direita = build_ascii_tree_recursive(arvore->direita);

    if (node->esquerda != NULL) {
        
        node->esquerda->parent_dir = -1;
    }

    if (node->direita != NULL) {
        
        node->direita->parent_dir = 1;
    }

    sprintf(node->label, "%d", arvore->valor);
    node->lablen = strlen(node->label);

    return node;
}

asciinode * build_ascii_tree(Arvore* arvore) {
  
    asciinode *node;
    
    if (arvore == NULL) {

        return NULL;
    }
    node = build_ascii_tree_recursive(arvore);
    
    node->parent_dir = 0;
    
    return node;
}

void free_ascii_tree(asciinode *node) {
    
    if (node == NULL) {

        return;
    }
    
    free_ascii_tree(node->esquerda);
    free_ascii_tree(node->direita);
    free(node);
}

void compute_lprofile(asciinode *node, int x, int y) {

    int i, isleft;
    
    if (node == NULL) {

        return;
    }

    isleft = (node->parent_dir == -1);
    lprofile[y] = MIN(lprofile[y], x-((node->lablen-isleft)/2));
    
    if (node->esquerda != NULL) {

        for (i=1; i <= node->comprimento && y+i < MAX_HEIGHT; i++) {
        
            lprofile[y+i] = MIN(lprofile[y+i], x-i);
        }
    }

    compute_lprofile(node->esquerda, x-node->comprimento-1, y+node->comprimento+1);
    compute_lprofile(node->direita, x+node->comprimento+1, y+node->comprimento+1);
}

void compute_rprofile(asciinode *node, int x, int y) {

    int i, notleft;
    
    if (node == NULL) {

        return;
    }
    
    notleft = (node->parent_dir != -1);
    rprofile[y] = MAX(rprofile[y], x+((node->lablen-notleft)/2));
    
    if (node->direita != NULL) {

        for (i=1; i <= node->comprimento && y+i < MAX_HEIGHT; i++) {
            
            rprofile[y+i] = MAX(rprofile[y+i], x+i);
        }
    }

    compute_rprofile(node->esquerda, x-node->comprimento-1, y+node->comprimento+1);
    compute_rprofile(node->direita, x+node->comprimento+1, y+node->comprimento+1);
}

void compute_edge_lengths(asciinode *node)  {
  
    int h, hmin, i, delta;
    
    if (node == NULL) {

        return;
    } 
    
    compute_edge_lengths(node->esquerda);
    compute_edge_lengths(node->direita);

    if (node->direita == NULL && node->esquerda == NULL) {
    
        node->comprimento = 0;
    } else {
    
        if (node->esquerda != NULL) {

            for (i=0; i<node->esquerda->altura && i < MAX_HEIGHT; i++) {
            
                rprofile[i] = -INFINITY;
            }

            compute_rprofile(node->esquerda, 0, 0);
            hmin = node->esquerda->altura;
        } else {
        
            hmin = 0;
        }
        
        if (node->direita != NULL) {
            
            for (i=0; i<node->direita->altura && i < MAX_HEIGHT; i++) {
            
                lprofile[i] = INFINITY;
            }

            compute_lprofile(node->direita, 0, 0);
            hmin = MIN(node->direita->altura, hmin);
        } else {
        
            hmin = 0;
        }
        
        delta = 4;
        for (i=0; i<hmin; i++) {
            
            delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
        }

        if (((node->esquerda != NULL && node->esquerda->altura == 1) ||(node->direita != NULL && node->direita->altura == 1))&&delta>4) {
        
            delta--;
        }

        node->comprimento = ((delta+1)/2) - 1;
    }

    h = 1;
  
    if (node->esquerda != NULL) {
        
        h = MAX(node->esquerda->altura + node->comprimento + 1, h);
    }
    
    if (node->direita != NULL){
        
        h = MAX(node->direita->altura + node->comprimento + 1, h);
    }
    
    node->altura = h;
}

void print_level(asciinode *node, int x, int level) {
  
    int i, isleft;
    
    if (node == NULL) {
    
        return;
    }
    
    isleft = (node->parent_dir == -1);
    
    if (level == 0) {

        for (i=0; i<(x-print_next-((node->lablen-isleft)/2)); i++) {
        
            printf(" ");
        }
    
        print_next += i;
        printf("%s", node->label);
        print_next += node->lablen;
    } else if (node->comprimento >= level) {

        if (node->esquerda != NULL) {
      
            for (i=0; i<(x-print_next-(level)); i++) {
                
                printf(" ");
            }
      
            print_next += i;
            printf("/");
            print_next++;
        }
        
        if (node->direita != NULL) {
      
            for (i=0; i<(x-print_next+(level)); i++) {
                
                printf(" ");
            }
          
            print_next += i;
            printf("\\");
            print_next++;
        }
    } else {

        print_level(node->esquerda,x-node->comprimento-1,level-node->comprimento-1);
        print_level(node->direita,x+node->comprimento+1,level-node->comprimento-1);
    }
}

void print_ascii_tree(Arvore * arvore) {
  
    asciinode *proot;
    int xmin, i;

    if (arvore == NULL) {

        return;    
    }

    proot = build_ascii_tree(arvore);
    compute_edge_lengths(proot);
    
    for (i=0; i<proot->altura && i < MAX_HEIGHT; i++) {
        
        lprofile[i] = INFINITY;
    }

    compute_lprofile(proot, 0, 0);
    xmin = 0;
    
    for (i = 0; i < proot->altura && i < MAX_HEIGHT; i++) {
        
        xmin = MIN(xmin, lprofile[i]);
    }
    
    for (i = 0; i < proot->altura; i++) {
        
        print_next = 0;
        print_level(proot, -xmin, i);
        printf("\n");
    }
    
    if (proot->altura >= MAX_HEIGHT) {
        
        printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
    }

    free_ascii_tree(proot);
}

Arvore* newNode(int valor) {

    Arvore* node = (Arvore*)malloc(sizeof(Arvore));
    node->valor = valor;
    node->esquerda   = NULL;
    node->direita  = NULL;
    node->altura = 1; 

    return(node);
}

int getBalance(Arvore* arvore) {
    
    if (arvore == NULL) {
        
        return 0;
    }
    return height(arvore->esquerda) - height(arvore->direita);
}

Arvore* rightRotate(Arvore* arvore) {
    
    Arvore* x = arvore->esquerda;
    Arvore* T2 = x->direita;

    x->direita = arvore;
    arvore->esquerda = T2;

    arvore->altura = MAX(height(arvore->esquerda), height(arvore->direita))+1;
    x->altura = MAX(height(x->esquerda), height(x->direita))+1;

    return x;
}

Arvore* leftRotate(Arvore* arvore) {

    Arvore* y = arvore->direita;
    Arvore* T2 = y->esquerda;

    y->esquerda = arvore;
    arvore->direita = T2;

    arvore->altura = MAX(height(arvore->esquerda), height(arvore->direita))+1;
    y->altura = MAX(height(y->esquerda), height(y->direita))+1;

    return y;
}

/*Balanceia a arvore*/
Arvore* insertBalanced(Arvore* node, int key) {
    
    if (node == NULL) {
        
        return(newNode(key));
    }

    if (key < node->valor) {
        
        node->esquerda  = insertBalanced(node->esquerda, key);
    } else if (key > node->valor) {
      
        node->direita = insertBalanced(node->direita, key);
    }
    else {
     
        return node;
    }
    
    node->altura = 1 + MAX(height(node->esquerda),height(node->direita));

    int balance = getBalance(node);

    if (balance > 1 && key < node->esquerda->valor) {
        
        return rightRotate(node);
    }

    if (balance < -1 && key > node->direita->valor) {
        
        return leftRotate(node);
    }

    if (balance > 1 && key > node->esquerda->valor) {
        
        node->esquerda =  leftRotate(node->esquerda);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->direita->valor) {
        
        node->direita = rightRotate(node->direita);
        return leftRotate(node);
    }

    return node;
}

int isFullTree(Arvore* arvore) {

    if(arvore == NULL) {
        
        return 1;
    }

    if(arvore->esquerda == NULL && arvore->direita == NULL) {
    	
    	printf("\n\n");
    	printf("Arvore não cheia\n");    
        return 1;
    }

    if((arvore->esquerda)&&(arvore->direita)) {
        
        printf("\n\n");
        printf("Arvore Cheia\n");
        return (isFullTree(arvore->esquerda) && isFullTree(arvore->direita));
    }
}