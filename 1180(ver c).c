#include <stdio.h>
#include <stdlib.h>

    int main(){
        int n;
        scanf("%d", &n);

        int *x = (int*) malloc(n * sizeof(int));
        
        //Leitura

        for (int i = 0; i < n; i++)
        {
            scanf("%d", &x[i]);
        }
        
        int menor = x[0];
        int pos = 0;

        for (int i = 1; i < n; i++)
        {
            if (x[i] < menor)
            {
                menor = x[i];
                pos = i;
            }
            
        }
        printf("Menor valor: %d\n", menor);
        printf("Posicao: %d\n", pos);
    
        free(x);
        return 0;
    }