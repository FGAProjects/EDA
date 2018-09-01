#include <stdio.h>
#include <stdlib.h>


void hanoi(int n, char ori, char dest, char aux){
    
    if(n==1){ 
       
        printf("Mova o disco 1 da base %c para a base %c\n", ori ,dest);
    
    }
    else{
       
        return
        hanoi(n-1, ori, aux, dest),
        printf("Mova o disco %d da base %c para a base %c\n", n, ori, dest),
        hanoi(n-1, aux, dest, ori);
        
    }
    
}

main(){
    
    int n;
    
    printf("Digite o numero de discos: ");
    scanf("%d", &n);
    
    printf("Para resolver a torre de Hanoi faça:\n");
    hanoi(n, 'A', 'C', 'B');
    
    return 0;
}
