#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 9
#define TRUE 1
#define FALSE 0

// Função para alocar a matriz 9x9 dinamicamente
int** aloca_matriz() {
    int i;
    int **matriz = (int**) malloc(N * sizeof(int*));
    if (matriz == NULL) {
        return NULL;
    }
    for (i = 0; i < N; i++) {
        matriz[i] = (int*) malloc(N * sizeof(int));
        if (matriz[i] == NULL) {
            // Libera memória já alocada em caso de falha
            while (i > 0) {
                free(matriz[--i]);
            }
            free(matriz);
            return NULL;
        }
    }
    return matriz;
}

// Função para desalocar a matriz
void desaloca_matriz(int **matriz) {
    int i;
    for (i = 0; i < N; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

// Função para ler a matriz
void le_matriz(int **matriz) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (scanf("%d", &matriz[i][j]) != 1) {
                // Tratar erro de leitura, se necessário
                exit(1);
            }
        }
    }
}

// Função para verificar se os números de 1 a 9 estão presentes
bool verifica_conjunto(int *conjunto) {
    int i, valor;
    // O array 'check' serve como um conjunto booleano, onde check[v] é 1 se o valor v foi encontrado.
    // Usamos N+1 para ter índices de 1 a 9.
    int check[N + 1] = {0}; 
    
    for (i = 0; i < N; i++) {
        valor = conjunto[i];
        if (valor < 1 || valor > 9) return FALSE;
        if (check[valor] == 1) return FALSE; // Número repetido
        check[valor] = 1;
    }
    return TRUE;
}

// Verifica todas as regras do Sudoku
bool verifica_sudoku(int **matriz) {
    int i, j, k;
    int temp_arr[N]; // Array temporário para passar os conjuntos de 9 números

    // 1. Verificação de Linhas
    for (i = 0; i < N; i++) {
        // A linha i já é um conjunto: matriz[i]
        if (!verifica_conjunto(matriz[i])) return FALSE;
    }

    // 2. Verificação de Colunas
    for (j = 0; j < N; j++) {
        for (i = 0; i < N; i++) {
            temp_arr[i] = matriz[i][j];
        }
        if (!verifica_conjunto(temp_arr)) return FALSE;
    }

    // 3. Verificação de Regiões 3x3
    // (k_start, l_start) define o canto superior esquerdo da sub-matriz 3x3
    for (int k_start = 0; k_start < N; k_start += 3) {
        for (int l_start = 0; l_start < N; l_start += 3) {
            int idx = 0;
            for (i = k_start; i < k_start + 3; i++) {
                for (j = l_start; j < l_start + 3; j++) {
                    temp_arr[idx++] = matriz[i][j];
                }
            }
            if (!verifica_conjunto(temp_arr)) return FALSE;
        }
    }

    return TRUE;
}

int main() {
    int num_instancias, instancia_k;
    int **matriz;

    if (scanf("%d", &num_instancias) != 1) return 0;

    for (instancia_k = 1; instancia_k <= num_instancias; instancia_k++) {
        matriz = aloca_matriz();
        if (matriz == NULL) {
            // Tratar erro de alocação
            return 1;
        }

        le_matriz(matriz);
        
        printf("Instancia %d\n", instancia_k);
        if (verifica_sudoku(matriz)) {
            printf("SIM\n");
        } else {
            printf("NAO\n");
        }

        desaloca_matriz(matriz);
        
        if (instancia_k < num_instancias) {
             printf("\n");
        }
    }

    return 0;
}