#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função que implementa o Insertion Sort
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        // 'key' é o elemento a ser inserido na sublista ordenada
        key = arr[i];
        j = i - 1;

        // Move os elementos da sublista arr[0..i-1] que são maiores que 'key'
        // para uma posição à frente de sua posição atual
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        // Insere 'key' em sua posição correta
        arr[j + 1] = key;
    }
}

// Função principal
int main() {
    int nc; // Número de casos de teste (cidades)
    
    // Leitura rápida para lidar com o grande volume de entrada
    // Esta otimização é crucial para TLE, mesmo com um algoritmo O(N^2)
    if (scanf("%d", &nc) != 1) return 0;
    
    // Loop para cada caso de teste
    while (nc--) {
        int n; // Quantidade de pessoas na cidade
        if (scanf("%d", &n) != 1) break;
        
        // Aloca memória para armazenar as alturas. O máximo é 3.000.000.
        int *heights = (int *)malloc(n * sizeof(int));
        if (heights == NULL) {
            // Lidar com falha na alocação, se necessário
            break; 
        }

        // Leitura das alturas
        for (int i = 0; i < n; i++) {
            if (scanf("%d", &heights[i]) != 1) break;
        }
        
        // A Aplicação do Insertion Sort começa aqui
        insertionSort(heights, n);

        // Impressão da saída (ordenada)
        for (int i = 0; i < n; i++) {
            printf("%d%c", heights[i], (i == n - 1) ? '\n' : ' ');
        }

        // Libera a memória alocada
        free(heights);
    }

    return 0;
}