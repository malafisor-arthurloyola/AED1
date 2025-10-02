#include <stdio.h>
#include <string.h>

// Definimos o tamanho máximo para a "Pilha" de aberturas
#define MAX_STACK_SIZE 1000 

// A lógica principal que usa o array para simular a Pilha
void peneira_pilha_explicita(const char *str) {
    // 1. Array: Será o local onde guardamos as aberturas
    char pilha_de_aberturas[MAX_STACK_SIZE]; 
    
    // 2. Topo: Variável que rastreia quantos itens estão na pilha
    int topo = 0; // Quando topo é 0, a pilha está vazia
    
    int diamantes = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        
        // Se encontramos '<'
        if (str[i] == '<') {
            // Simulação de EMPILHAR (PUSH)
            // Apenas incrementamos o topo. Não precisamos armazenar o '<'
            // no array, já que só temos um tipo de abertura.
            if (topo < MAX_STACK_SIZE) {
                // Se fosse um problema com vários tipos, faríamos:
                // pilha_de_aberturas[topo] = '<';
                topo++; 
            }
        } 
        
        // Se encontramos '>' E a pilha NÃO está vazia (topo > 0)
        else if (str[i] == '>' && topo > 0) {
            // Simulação de DESEMPILHAR (POP)
            // Apenas decrementamos o topo.
            topo--; 
            diamantes++; // Contamos o diamante formado pelo par
        }
        // O '.' é ignorado.
    }
    printf("%d\n", diamantes);
}

// O código main permanece o mesmo para lidar com a entrada
int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    getchar(); // Limpa o buffer
    
    char peneira[1001];

    for (int i = 0; i < N; i++) {
        if (fgets(peneira, sizeof(peneira), stdin) == NULL) break;
        peneira[strcspn(peneira, "\n")] = '\0'; 
        
        peneira_pilha_explicita(peneira); // Chamando a nova função
    }

    return 0;
}