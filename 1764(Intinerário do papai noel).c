#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Definições e Estruturas ---

// M: cidades (vértices, máx 40000), N: rotas (arestas, máx 50000)
#define MAX_M 40000
#define MAX_N 50000

// Estrutura para a rota (aresta)
typedef struct {
    int u, v;  // Cidades
    int z;     // Distância (custo)
} Edge;

// Array para a estrutura Union-Find
int parent[MAX_M];

// Array de rotas
Edge edges[MAX_N];

// --- Union-Find Otimizado ---

// Inicializa a estrutura Union-Find
void make_set(int m) {
    for (int i = 0; i < m; i++) {
        parent[i] = i; 
    }
}

// Função Find com compressão de caminho (retorna o representante do conjunto)
int find_set(int i) {
    if (parent[i] == i) {
        return i;
    }
    // Compressão de caminho
    return parent[i] = find_set(parent[i]);
}

// Função Union (une dois conjuntos)
int union_sets(int i, int j) {
    int root_i = find_set(i);
    int root_j = find_set(j);
    
    if (root_i != root_j) {
        parent[root_i] = root_j; // Une os conjuntos
        return 1; // União realizada (rota adicionada)
    }
    return 0; // Já estavam conectados (rota descartada)
}

// --- Kruskal e Função de Comparação ---

// Função de comparação para qsort (ordena pelo custo 'z' em ordem crescente)
int compare_edges(const void *a, const void *b) {
    return ((Edge*)a)->z - ((Edge*)b)->z;
}

// Função Kruskal: Calcula a soma mínima das distâncias (Custo da AGM)
long long kruskal(int m, int n) {
    long long min_sum_distance = 0;
    int edges_count = 0; 
    
    make_set(m);
    
    // Ordena as rotas pelo custo (O(N log N))
    qsort(edges, n, sizeof(Edge), compare_edges);
    
    // Percorre as rotas e constrói a AGM (para M-1 arestas)
    for (int i = 0; i < n && edges_count < m - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int z = edges[i].z;
        
        // Se não formar ciclo, adiciona a aresta à AGM
        if (union_sets(u, v)) {
            min_sum_distance += z;
            edges_count++;
        }
    }
    
    return min_sum_distance;
}

// --- Função Principal de Resolução ---

void solve() {
    int M, N; // M: cidades, N: rotas
    
    // Loop principal de casos de teste (termina com M=N=0)
    while (scanf("%d %d", &M, &N) == 2 && (M != 0 || N != 0)) {
        
        // 1. Leitura das Rotas
        for (int i = 0; i < N; i++) {
            if (scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].z) != 3) {
                break;
            }
        }
        
        // 2. Cálculo da Soma Mínima das Distâncias (Custo da AGM)
        // O resultado é um long long, pois o custo total pode exceder 2^31.
        long long result = kruskal(M, N);
        
        // 3. Saída
        printf("%lld\n", result);
    }
}

int main() {
    solve();
    return 0;
}