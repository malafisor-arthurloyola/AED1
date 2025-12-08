#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tamanho máximo do alfabeto ('a' a 'z')
#define MAX_VERTICES 26 

// Estrutura para representar a lista de adjacência (usando um array dinâmico simples)
typedef struct AdjList {
    int* neighbors;
    int size;
    int capacity;
} AdjList;

// Inicializa a lista de adjacência
void initAdjList(AdjList* list) {
    list->size = 0;
    list->capacity = 4; // Capacidade inicial
    list->neighbors = (int*)malloc(list->capacity * sizeof(int));
    if (list->neighbors == NULL) exit(1);
}

// Adiciona um vizinho (vertice de destino) à lista de adjacência
void addNeighbor(AdjList* list, int v_index) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->neighbors = (int*)realloc(list->neighbors, list->capacity * sizeof(int));
        if (list->neighbors == NULL) exit(1);
    }
    list->neighbors[list->size++] = v_index;
}

// Vetor para armazenar o componente conexo atual encontrado
int current_component[MAX_VERTICES];
int component_size;

// Array de flags para rastrear vértices visitados
int visited[MAX_VERTICES];

/**
 * Função de Busca em Profundidade (DFS)
 * Encontra todos os vértices acessíveis a partir de u e os armazena em current_component.
 */
void dfs(int u_index, AdjList adj[], int V) {
    visited[u_index] = 1;
    current_component[component_size++] = u_index; // Adiciona o vértice ao componente

    // Itera sobre todos os vizinhos de u
    for (int i = 0; i < adj[u_index].size; i++) {
        int v_index = adj[u_index].neighbors[i];
        if (!visited[v_index]) {
            dfs(v_index, adj, V);
        }
    }
}

// Função de comparação para qsort (ordem crescente)
int compare_ints(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// --- Função Principal de Resolução ---
void solve() {
    int N;
    if (scanf("%d", &N) != 1) return;

    for (int case_num = 1; case_num <= N; case_num++) {
        int V, E;
        if (scanf("%d %d", &V, &E) != 2) break;

        // Inicializa a lista de adjacência para o novo caso de teste
        AdjList adj[MAX_VERTICES];
        for (int i = 0; i < V; i++) {
            initAdjList(&adj[i]);
        }
        
        // Zera o vetor de visitados
        memset(visited, 0, sizeof(visited));
        
        // Leitura das arestas
        for (int i = 0; i < E; i++) {
            char u_char, v_char;
            if (scanf(" %c %c", &u_char, &v_char) != 2) break;
            
            // Mapeia o caractere para o índice do array (ex: 'a' -> 0)
            int u_index = u_char - 'a';
            int v_index = v_char - 'a';
            
            // Adiciona a aresta. O grafo é não-direcionado (simétrico).
            addNeighbor(&adj[u_index], v_index);
            addNeighbor(&adj[v_index], u_index);
        }

        printf("Case #%d:\n", case_num);
        int connected_components_count = 0;

        // Itera sobre todos os possíveis vértices ('a' até 'a' + V - 1)
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                // Encontramos um novo componente conexo!
                connected_components_count++;
                component_size = 0;
                
                // Executa a busca em profundidade a partir deste vértice
                dfs(i, adj, V);

                // Ordena os vértices do componente em ordem alfabética (crescente)
                qsort(current_component, component_size, sizeof(int), compare_ints);

                // Imprime o componente
                for (int j = 0; j < component_size; j++) {
                    printf("%c,", (char)('a' + current_component[j]));
                }
                printf("\n");
            }
        }

        // Imprime o total de componentes conexos
        printf("%d connected components\n", connected_components_count);

        // Imprime a linha em branco no final (regra do problema)
        printf("\n");
        
        // Libera a memória alocada para o próximo caso de teste
        for (int i = 0; i < V; i++) {
            free(adj[i].neighbors);
        }
    }
}

int main() {
    solve();
    return 0;
}