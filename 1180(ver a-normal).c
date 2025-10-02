#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    
    int X[N];
    int menorValor;
    int posicao;
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &X[i]);
    }
    
    menorValor = X[0];
    posicao = 0;
    
    for (int i = 1; i < N; i++) {
        if (X[i] < menorValor) {
            menorValor = X[i];
            posicao = i;
        }
    }
    
    printf("Menor valor: %d\n", menorValor);
    printf("Posicao: %d\n", posicao);
    
    return 0;
}
