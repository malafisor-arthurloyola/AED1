#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 251
#define INF 1000000000 // Um valor grande

// Estrutura para a lista de adjacência (vizinho e custo)
typedef struct {
    int v;
    int p;
} Edge;

// Lista de adjacência para o grafo completo (usaremos no passo 1)
Edge original_adj[MAX_N][MAX_N];
int original_adj_size[MAX_N];

// Lista de adjacência para o grafo modificado (usaremos no passo 2)
Edge modified_adj[MAX_N][MAX_N];
int modified_adj_size[MAX_N];

// Distâncias mínimas de Dijkstra
int dist[MAX_N];

// Função auxiliar para adicionar aresta
void add_edge(Edge adj_list[][MAX_N], int size_array[], int u, int v, int p) {
    adj_list[u][size_array[u]].v = v;
    adj_list[u][size_array[u]].p = p;
    size_array[u]++;
}

// Algoritmo de Dijkstra (O(N^2) com array)
void dijkstra(int N, int start) {
    // Inicialização
    for (int i = 0; i < N; i++) {
        dist[i] = INF;
    }
    dist[start] = 0;

    int visited[MAX_N] = {0};

    for (int count = 0; count < N; count++) {
        int u = -1;
        int min_d = INF;

        // 1. Encontra o vértice não visitado com a menor distância
        for (int i = 0; i < N; i++) {
            if (!visited[i] && dist[i] < min_d) {
                min_d = dist[i];
                u = i;
            }
        }

        if (u == -1) break; // Todos os alcançáveis foram visitados

        visited[u] = 1;

        // 2. Relaxamento das arestas
        for (int i = 0; i < modified_adj_size[u]; i++) {
            int v = modified_adj[u][i].v;
            int cost = modified_adj[u][i].p;

            if (dist[u] != INF && dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
            }
        }
    }
}

void solve() {
    int N, M, C, K;

    // Loop principal de casos de teste
    while (scanf("%d %d %d %d", &N, &M, &C, &K) == 4 && (N != 0 || M != 0 || C != 0 || K != 0)) {
        
        // --- 1. Inicialização e Leitura do Grafo Original ---
        for (int i = 0; i < N; i++) {
            original_adj_size[i] = 0;
            modified_adj_size[i] = 0;
        }

        // Armazenamos o menor custo direto entre i e i+1
        int route_direct_cost[MAX_N]; 
        for(int i = 0; i < C - 1; i++){
            route_direct_cost[i] = INF;
        }

        for (int i = 0; i < M; i++) {
            int u, v, p;
            if (scanf("%d %d %d", &u, &v, &p) != 3) break;

            // Arestas da Rota (u < C-1, v = u+1 ou vice-versa)
            if (u < C - 1 && v == u + 1) {
                if (p < route_direct_cost[u]) {
                    route_direct_cost[u] = p; 
                }
            } else if (v < C - 1 && u == v + 1) {
                if (p < route_direct_cost[v]) {
                    route_direct_cost[v] = p;
                }
            }
            
            // Grafo original completo
            add_edge(original_adj, original_adj_size, u, v, p);
            add_edge(original_adj, original_adj_size, v, u, p); 
        }

        // --- 2. Pré-cálculo: Custo Fixo da Rota (R[I]) ---
        int route_cost[MAX_N];
        route_cost[C - 1] = 0;
        
        // Custo_Rota[i] = Custo(i -> i+1) + Custo_Rota[i+1]
        for (int i = C - 2; i >= 0; i--) {
             if (route_direct_cost[i] != INF) {
                 // Verifica se o próximo ponto da rota (i+1) é alcançável
                 if (route_cost[i + 1] != INF) {
                     route_cost[i] = route_direct_cost[i] + route_cost[i + 1];
                 } else {
                      route_cost[i] = INF;
                 }
             } else {
                 route_cost[i] = INF; // Ligação i -> i+1 não existe
             }
        }
        
        // --- 3. Construção do Grafo Modificado ---
        
        // A. Cidades Fora da Rota (U >= C)
        for (int u = C; u < N; u++) {
            for (int i = 0; i < original_adj_size[u]; i++) {
                int v = original_adj[u][i].v;
                int p = original_adj[u][i].p;
                
                // Adicionamos a aresta original ao grafo modificado (u é a origem do desvio)
                add_edge(modified_adj, modified_adj_size, u, v, p);
            }
        }
        
        // B. Cidades Na Rota (0 <= U < C) - Adição da Aresta Fictícia
        for (int u = 0; u < C; u++) {
            // Se u for alcançável, crie uma aresta direta para o destino C-1
            if (route_cost[u] != INF) {
                // Adiciona a aresta virtual U -> C-1 com custo R[U]
                add_edge(modified_adj, modified_adj_size, u, C - 1, route_cost[u]);
            }
        }

        // C. Cidades de Transição (Fora da Rota -> Na Rota)
        // Isso já está coberto pela A (u >= C) e B (arestas para C-1).
        // Se U >= C e V < C, a aresta U->V é adicionada em A, e V, por sua vez, 
        // tem uma aresta V->C-1 com custo R[V] (em B).

        // --- 4. Execução de Dijkstra ---
        // A busca começa na cidade de conserto K
        dijkstra(N, K);

        // --- 5. Saída ---
        // O custo mínimo total é o custo mínimo para chegar à cidade destino C-1.
        printf("%d\n", dist[C - 1]);
    }
}

int main() {
    solve();
    return 0;
}
