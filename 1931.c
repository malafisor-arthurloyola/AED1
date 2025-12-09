#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Máximo número de cidades é 10^4. O grafo de estados tem 2 * 10^4 nós.
#define MAX_CITIES 10000
#define MAX_NODES (2 * MAX_CITIES + 2) // 2 * 10000 + 2 (para usar índices 1 a C)
#define MAX_EDGES (50000 * 4) // Número máximo de arestas no grafo de estados (50000 * 4)

// Usamos um valor grande para representar o infinito
#define INF 2000000000LL // Usamos long long para o custo total, 2 bilhões é suficiente

// Estrutura para representar a Aresta na Lista de Adjacência
typedef struct Edge {
    int to;    // Nó de destino
    int cost;  // Custo (pedágio)
    int next;  // Índice da próxima aresta na lista
} Edge;

// Arrays globais para evitar Stack Overflow
Edge edges[MAX_EDGES]; // Armazena todas as arestas
int head[MAX_NODES];   // head[u] armazena o índice da primeira aresta de u
int edge_count;        // Contador de arestas
long long dist[MAX_NODES]; // dist[u] armazena o custo mínimo para o nó u
char visited[MAX_NODES]; // Array para marcar nós visitados (simula a Priority Queue)

// --- Funções Auxiliares ---

/**
 * @brief Converte a cidade (1 a C) e a paridade (0=Par, 1=Ímpar) para o índice do nó (1-based).
 * * Cidades 1..C mapeiam para:
 * * Cidade c com paridade 0 (Par): c
 * * Cidade c com paridade 1 (Ímpar): c + C
 */
int get_node_index(int city, int parity, int C) {
    if (parity == 0) {
        return city;     // 1 -> C
    } else {
        return city + C; // C+1 -> 2C
    }
}

/**
 * @brief Adiciona uma aresta ao grafo de estados.
 */
void add_edge(int from, int to, int cost) {
    edges[edge_count].to = to;
    edges[edge_count].cost = cost;
    edges[edge_count].next = head[from]; // Novo elemento aponta para o antigo primeiro
    head[from] = edge_count;            // Novo elemento é o novo primeiro
    edge_count++;
}

/**
 * @brief Implementação Simples do Dijkstra (sem Priority Queue)
 * * Como N (2C) é no máximo 20000, um Dijkstra otimizado é crucial. 
 * * Em C puro, é comum usar uma fila de prioridade implementada via array ou o método
 * * de "relaxamento repetitivo" (mais lento) ou Heap. Usaremos a implementação de Heap (implicitamente, 
 * * via array dist e varredura) ou a mais simples para evitar complexidades de código C.
 */
void dijkstra(int C) {
    int i, u, v, min_node;
    long long min_dist;

    // 1. Inicialização
    for (i = 1; i <= 2 * C; ++i) {
        dist[i] = INF;
        visited[i] = 0;
    }

    // Nó inicial: Cidade 1 com Paridade 0 (Par). Índice 1.
    dist[1] = 0;

    // 2. Loop principal: Repetir 2C vezes (para cada nó)
    for (i = 1; i <= 2 * C; ++i) {
        min_dist = INF;
        min_node = -1;

        // Encontrar o nó não visitado com a menor distância
        for (u = 1; u <= 2 * C; ++u) {
            if (!visited[u] && dist[u] < min_dist) {
                min_dist = dist[u];
                min_node = u;
            }
        }

        // Se não houver mais nós acessíveis, pare
        if (min_node == -1) break;

        u = min_node;
        visited[u] = 1;

        // 3. Relaxamento das arestas
        int edge_idx = head[u];
        while (edge_idx != -1) {
            v = edges[edge_idx].to;
            long long weight = edges[edge_idx].cost;

            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
            edge_idx = edges[edge_idx].next;
        }
    }
}

void solve() {
    int C, V; // Cidades, Estradas
    
    // Leitura dos parâmetros
    if (scanf("%d %d", &C, &V) != 2) return;

    // Rejeitar casos impossíveis ou limites excedidos
    if (C < 2 || C > MAX_CITIES) return;

    // Limpeza e Inicialização do Grafo
    for (int i = 0; i <= 2 * C; ++i) {
        head[i] = -1; // -1 indica que a lista está vazia
    }
    edge_count = 0;

    // Leitura e Construção do Grafo de Estados
    for (int i = 0; i < V; ++i) {
        int c1, c2, g; // Cidade 1, Cidade 2, Pedágio (G)
        if (scanf("%d %d %d", &c1, &c2, &g) != 3) break;

        // --- Mapeamento e Transições ---
        
        // 1. Movimento Par (0) -> Ímpar (1)
        int u0 = get_node_index(c1, 0, C); // c1_Par
        int v1 = get_node_index(c2, 1, C); // c2_Ímpar
        add_edge(u0, v1, g);

        int v0 = get_node_index(c2, 0, C); // c2_Par
        int u1 = get_node_index(c1, 1, C); // c1_Ímpar

        // Bidirecional:
        add_edge(v0, u1, g); // c2_Par -> c1_Ímpar

        // 2. Movimento Ímpar (1) -> Par (0)
        add_edge(u1, v0, g); // c1_Ímpar -> c2_Par
        add_edge(v1, u0, g); // c2_Ímpar -> c1_Par
    }
    
    // Execução do Algoritmo de Caminho Mínimo
    dijkstra(C);

    // O nó destino é a Cidade C com Paridade 0 (Par)
    int target_node = get_node_index(C, 0, C);
    
    if (dist[target_node] == INF) {
        printf("-1\n");
    } else {
        printf("%lld\n", dist[target_node]);
    }
}

int main() {
    // Para resolver problemas competitivos em C, a otimização de I/O é importante.
    // setvbuf(stdout, NULL, _IONBF, 0);

    solve();

    return 0;
}