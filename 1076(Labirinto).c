#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definimos o limite máximo de Nodos: o labirinto máximo é 7x7, então V = 49.
// MAX_NODES = 50 é seguro (embora o problema diga N < X^2 e X entre 3 e 7).
#define MAX_NODES 50 

// Variáveis globais para a DFS e contagem
bool visited[MAX_NODES];
int movements;

// Lista de Adjacências usando array de listas dinâmicas
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adj[MAX_NODES];

// Função para adicionar uma aresta não-direcionada
void add_edge(int u, int v) {
    // Adiciona v na lista de u
    Node* newNodeV = (Node*)malloc(sizeof(Node));
    newNodeV->vertex = v;
    newNodeV->next = adj[u];
    adj[u] = newNodeV;

    // Adiciona u na lista de v
    Node* newNodeU = (Node*)malloc(sizeof(Node));
    newNodeU->vertex = u;
    newNodeU->next = adj[v];
    adj[v] = newNodeU;
}

// Função de Busca em Profundidade (DFS)
void dfs(int u) {
    visited[u] = true;
    
    Node* temp = adj[u];
    while (temp != NULL) {
        int v = temp->vertex;
        
        // Se o nó adjacente ainda não foi visitado, a aresta (u, v) precisa ser traçada.
        if (!visited[v]) {
            // Cada aresta visitada requer 2 movimentos: Ida (u -> v) e Volta (v -> u)
            movements += 2; 
            dfs(v);
        }
        temp = temp->next;
    }
}

// Função principal de solução para cada caso de teste
void solve() {
    int start_node; // N: Ponto de início/fim
    int V, A;       // V: Vértices, A: Arestas
    int u, v;       // Para ler as arestas
    int i;
    
    // 1. Leitura do nó inicial
    if (scanf("%d", &start_node) != 1) return;

    // 2. Leitura de V e A
    if (scanf("%d %d", &V, &A) != 2) return;

    // 3. Inicialização
    movements = 0;
    for (i = 0; i < V; i++) {
        visited[i] = false;
        adj[i] = NULL;
    }

    // 4. Leitura e Construção do Grafo (Lista de Adjacências)
    for (i = 0; i < A; i++) {
        if (scanf("%d %d", &u, &v) == 2) {
            add_edge(u, v);
        }
    }
    
    // 5. Execução da DFS a partir do nó inicial
    // Se o nó inicial não existe, o loop não rodará e o resultado será 0 (correto).
    if (start_node < V) {
        dfs(start_node);
    }
    
    // 6. Impressão do resultado
    printf("%d\n", movements);
    
    // 7. Limpeza da memória alocada (boas práticas)
    for (i = 0; i < V; i++) {
        Node* current = adj[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
        adj[i] = NULL;
    }
}

// Função principal de entrada
int main() {
    int T;
    
    // Leitura do número de casos de teste
    if (scanf("%d", &T) != 1) return 0;

    while (T--) {
        solve();
    }

    return 0;
}