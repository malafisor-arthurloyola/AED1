#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definimos o limite máximo de junções (m) e o número máximo de estradas (n)
#define MAX_M 200005 
#define MAX_N 200005 

// --- Estruturas de Dados ---

// Estrutura para a estrada (aresta)
typedef struct {
    int u, v;  // Junções (vértices)
    int z;     // Comprimento (custo)
} Edge;

// Array para a estrutura Union-Find (parent[i] é o pai/representante de i)
int parent[MAX_M];

// Array de estradas
Edge edges[MAX_N];

// --- Funções Auxiliares (Union-Find) ---

// Inicializa a estrutura Union-Find
void make_set(int m) {
    for (int i = 0; i < m; i++) {
        parent[i] = i; // Cada junção é inicialmente seu próprio pai
    }
}

// Função Find com compressão de caminho (otimiza a busca pela raiz do conjunto)
int find_set(int i) {
    if (parent[i] == i) {
        return i;
    }
    // Compressão de caminho: aponta diretamente para a raiz
    return parent[i] = find_set(parent[i]);
}

// Função Union (une dois conjuntos)
// Retorna 1 se a união ocorreu (sem ciclo), 0 se já estavam conectados
int union_sets(int i, int j) {
    int root_i = find_set(i);
    int root_j = find_set(j);
    
    if (root_i != root_j) {
        // Une o conjunto de i ao conjunto de j
        parent[root_i] = root_j;
        return 1; // União realizada
    }
    return 0; // Já estavam conectados (ciclo)
}

// --- Funções Auxiliares (Kruskal) ---

// Função de comparação para qsort (ordena as estradas pelo custo 'z' em ordem crescente)
int compare_edges(const void *a, const void *b) {
    return ((Edge*)a)->z - ((Edge*)b)->z;
}

// Função Kruskal: Calcula o Custo Mínimo da Iluminação (AGM)
long long kruskal(int m, int n) {
    long long min_cost = 0;
    int edges_count = 0; 
    
    // 1. Inicializa o Union-Find
    make_set(m);
    
    // 2. Ordena as arestas (O(N log N))
    qsort(edges, n, sizeof(Edge), compare_edges);
    
    // 3. Percorre as arestas e constrói a AGM
    // O loop pode parar quando m-1 arestas forem adicionadas (AGM completa)
    for (int i = 0; i < n && edges_count < m - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int z = edges[i].z;
        
        // Se as junções u e v não estão no mesmo conjunto (não forma ciclo)
        if (union_sets(u, v)) {
            min_cost += z;
            edges_count++;
        }
    }
    
    return min_cost;
}

// --- Função Principal de Resolução ---

void solve() {
    int m, n;
    
    // Loop principal de casos de teste (termina com m=n=0)
    while (scanf("%d %d", &m, &n) == 2 && (m != 0 || n != 0)) {
        
        long long total_cost = 0;
        
        // 1. Leitura das Arestas e Cálculo do Custo Total Original
        for (int i = 0; i < n; i++) {
            if (scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].z) != 3) {
                break;
            }
            total_cost += edges[i].z;
        }
        
        // 2. Cálculo do Custo Mínimo que DEVE ser mantido (AGM)
        long long min_lighting_cost = kruskal(m, n);
        
        // 3. Cálculo da Economia Máxima: Custo Total - Custo Mínimo
        // A economia é o valor total das estradas que NÃO foram incluídas na AGM.
        long long max_saving = total_cost - min_lighting_cost;
        
        // Imprime o resultado (usamos %lld para long long)
        printf("%lld\n", max_saving);
    }
}

int main() {
    solve();
    return 0;
}