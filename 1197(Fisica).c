#include <stdio.h>

int main() {
    // v: velocidade (-100 a 100), t: tempo (0 a 200)
    int v, t;

    // Loop para ler a entrada até o final do arquivo (EOF)
    while (scanf("%d %d", &v, &t) != EOF) {
        
        // A fórmula derivada do MUV (assumindo v0=0) é:
        // Deslocamento = 2 * v * t
        // Como os limites de v e t são pequenos (100 * 200 * 2 = 40000), 
        // o tipo int é suficiente para o resultado.
        
        int displacement = 2 * v * t;

        // Imprime o resultado
        printf("%d\n", displacement);
    }

    return 0;
}