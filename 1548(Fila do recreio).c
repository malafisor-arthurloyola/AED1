#include <stdio.h>
#include <stdlib.h>

// Função de comparação para qsort (ordem decrescente!)
// Se o valor de 'a' for menor que 'b', retorna positivo para trocar (b vem antes de a)
int comparar_decrescente(const void *a, const void *b) {
    return (*(int*)b - *(int*)a); // b - a -> decrescente
}

void resolver_caso_teste() {
    int M; // Número de alunos
    scanf("%d", &M);

    // 1. Armazenar a lista ORIGINAL (Ordem de Chegada)
    int *original = (int*)malloc(M * sizeof(int));
    // 2. Armazenar a lista COPIADA (Para ser ordenada)
    int *copia = (int*)malloc(M * sizeof(int));

    // Leitura e preenchimento dos dois arrays
    for (int i = 0; i < M; i++) {
        int nota;
        scanf("%d", &nota);
        original[i] = nota;
        copia[i] = nota; // A cópia é idêntica inicialmente
    }

    // 3. Ordenar a cópia (DECERESCENTE: Maior nota primeiro)
    // Usamos a função qsort do C para eficiência
    qsort(copia, M, sizeof(int), comparar_decrescente);

    // 4. Comparar e Contar
    int alunos_sem_troca = 0;
    for (int i = 0; i < M; i++) {
        // Se a nota na posição i da lista original é a mesma da lista ordenada
        if (original[i] == copia[i]) {
            alunos_sem_troca++;
        }
    }

    // Imprimir o resultado do caso de teste
    printf("%d\n", alunos_sem_troca);

    // Liberar a memória alocada
    free(original);
    free(copia);
}

int main() {
    int N; // Número de casos de teste
    scanf("%d", &N);
    while (N--) {
        resolver_caso_teste();
    }
    return 0;
}