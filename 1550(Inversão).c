#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Definimos o limite máximo para os vértices.
// Como B < 10000, 10001 é suficiente para a busca.
#define MAX_NODES 10001

// Função auxiliar para inverter os dígitos de um número
int invert(int n) {
    int reversed_n = 0;
    while (n > 0) {
        // Multiplica por 10 e adiciona o último dígito (n % 10)
        reversed_n = reversed_n * 10 + (n % 10);
        n /= 10;
    }
    return reversed_n;
}

// Função principal de BFS
int bfs_solve(int A, int B) {
    // Distâncias: -1 indica não visitado.
    // Usamos um array estático/globalmente alocado para evitar estouro da pilha em C com arrays grandes.
    static int dist[MAX_NODES];
    
    // Fila para a BFS (implementação simples com array circular ou ponteiros de cabeça/cauda)
    static int queue[MAX_NODES];
    int head = 0; // Início da fila
    int tail = 0; // Fim da fila (próxima posição vazia)

    // 1. Inicializa o array de distâncias
    // Usamos memset para inicializar rapidamente a -1.
    memset(dist, -1, sizeof(dist));

    // 2. Estado inicial
    dist[A] = 0;
    queue[tail++] = A; // Enfileira A

    // 3. Loop principal da BFS
    while (head < tail) {
        int u = queue[head++]; // Desenfileira o estado atual (u)
        
        // Se o destino for alcançado, retorna a distância
        if (u == B) {
            return dist[u];
        }

        // --- Geração dos Próximos Estados ---

        // 1. Operação de Adição (Botão 1: +1)
        int v1 = u + 1;
        
        // Verifica se é válido (dentro do limite e não visitado)
        if (v1 < MAX_NODES && dist[v1] == -1) {
            dist[v1] = dist[u] + 1;
            queue[tail++] = v1; // Enfileira
            
            if (v1 == B) return dist[v1]; // Otimização: verifica B aqui também
        }

        // 2. Operação de Inversão (Botão 2: Inverte)
        int v2 = invert(u);
        
        // Verifica se é válido (dentro do limite e não visitado)
        if (v2 < MAX_NODES && dist[v2] == -1) {
            dist[v2] = dist[u] + 1;
            queue[tail++] = v2; // Enfileira
            
            if (v2 == B) return dist[v2]; // Otimização
        }
    }

    // Deve ser alcançável, mas como fallback
    return -1; 
}


int main() {
    int T;
    // Leitura da quantidade de casos de teste
    if (scanf("%d", &T) != 1 || T <= 0) return 0;

    while (T--) {
        int A, B;
        // Leitura dos números inicial (A) e final (B)
        if (scanf("%d %d", &A, &B) != 2) break;
        
        // Executa a BFS e imprime o resultado
        printf("%d\n", bfs_solve(A, B));
    }

    return 0;
}