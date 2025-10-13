#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h> // Para qsort

#define MAX_SIZE 1000

// =====================================
// Estrutura para Simular as Estruturas
// =====================================

// Funções de comparação para qsort (maior primeiro para Priority Queue)
int compare_int_desc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

// =====================================
// FUNÇÃO PRINCIPAL
// =====================================

int main() {
    int n, cmd, x, i, j;
    
    // Arrays para simular as 3 estruturas
    int s[MAX_SIZE];    // Pilha
    int q[MAX_SIZE];    // Fila
    int pq[MAX_SIZE];   // Fila de Prioridade (ordenada)
    
    // Posições de controle
    int s_top;      // Topo da Pilha (LIFO)
    int q_head;     // Cabeça da Fila (FIFO)
    int q_tail;     // Cauda da Fila
    int pq_size;    // Tamanho da Fila de Prioridade
    
    bool is_stack, is_queue, is_priority;
    
    while (scanf("%d", &n) != EOF) {
        // Reinicializa o estado e os controles para cada caso de teste
        s_top = -1;
        q_head = 0;
        q_tail = 0;
        pq_size = 0;
        
        is_stack = true;
        is_queue = true;
        is_priority = true;

        for (i = 0; i < n; i++) {
            scanf("%d %d", &cmd, &x);

            if (cmd == 1) {
                // Comando 1 x: Jogue x na sacola

                if (is_stack) {
                    s_top++;
                    s[s_top] = x;
                }
                
                if (is_queue) {
                    q[q_tail] = x;
                    q_tail++;
                }
                
                if (is_priority) {
                    pq[pq_size] = x;
                    pq_size++;
                    // Mantém a Fila de Prioridade ordenada (Max-Heap simulado)
                    qsort(pq, pq_size, sizeof(int), compare_int_desc);
                }

            } else { 
                // Comando 2 x: Tire um elemento da sacola e o valor é x

                // Verifica Pilha (LIFO)
                if (is_stack) {
                    if (s_top < 0 || s[s_top] != x) {
                        is_stack = false;
                    } else {
                        s_top--;
                    }
                }

                // Verifica Fila (FIFO)
                if (is_queue) {
                    if (q_head >= q_tail || q[q_head] != x) {
                        is_queue = false;
                    } else {
                        q_head++;
                    }
                }

                // Verifica Fila de Prioridade (Maior primeiro)
                if (is_priority) {
                    if (pq_size <= 0 || pq[0] != x) {
                        is_priority = false;
                    } else {
                        // Remove o elemento do topo (índice 0) e move o resto
                        for (j = 0; j < pq_size - 1; j++) {
                            pq[j] = pq[j + 1];
                        }
                        pq_size--;
                    }
                }
            }
        }

        // Determina o resultado
        int total_true = is_stack + is_queue + is_priority;

        if (total_true == 0) {
            printf("impossible\n");
        } else if (total_true > 1) {
            printf("not sure\n");
        } else if (is_stack) {
            printf("stack\n");
        } else if (is_queue) {
            printf("queue\n");
        } else if (is_priority) {
            printf("priority queue\n");
        }
    }

    return 0;
}