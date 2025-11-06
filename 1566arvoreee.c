#include <stdio.h>
#include <stdlib.h> // Necessário para 'malloc'

// === 1. Estrutura da Árvore ===
struct cel {
    int conteudo;
    struct cel *esq;
    struct cel *dir;
};
typedef struct cel No;
typedef No *arvore;

// Inicializa a raiz de uma nova árvore
arvore inicializar_arvore() {
    return NULL;
}

// === 2. Função de Inserção na ABB ===
// Insere um novo nó na Árvore Binária de Busca (ABB) de forma recursiva.
arvore inserir_na_abb(arvore r, int altura_inserida) {
    // Caso base: Árvore vazia ou encontrou o local de inserção
    if (r == NULL) {
        No *novo = (No*)malloc(sizeof(No));

        novo->conteudo = altura_inserida;
        novo->esq = novo->dir = NULL;
        return novo; // O novo nó se torna a raiz (ou o filho do nó pai)
    }

    // Caso recursivo: Decide se vai para a esquerda ou direita
    if (altura_inserida < r->conteudo) {
        // Se a altura for menor, insere na subárvore esquerda
        r->esq = inserir_na_abb(r->esq, altura_inserida);
    } else { 
        // Se a altura for maior ou igual, insere na subárvore direita.
        // É crucial permitir valores iguais (população pode ter a mesma altura)
        r->dir = inserir_na_abb(r->dir, altura_inserida);
    }

    return r; // Retorna a raiz atual (que pode ter sido alterada por referência)
}

// Variável global para controle de espaços (Não é a melhor prática, mas simplifica o problema de impressão do último elemento)
int primeiro_elemento;

// === 3. Percurso Em Ordem (Erd) ===
// Imprime o conteúdo da árvore em ordem crescente.
void Erd (arvore r) {
    if (r != NULL) {
        Erd (r->esq);
        
        // Lógica para imprimir os espaços entre os números (não após o último)
        if (primeiro_elemento == 0) {
            printf(" ");
        }
        printf("%d", r->conteudo);
        primeiro_elemento = 0; // Depois do primeiro, os próximos terão espaço
        
        Erd (r->dir);
    }
}

// === 4. Função para liberar memória (Importante!) ===
void liberar_arvore(arvore r) {
    if (r != NULL) {
        liberar_arvore(r->esq);
        liberar_arvore(r->dir);
        free(r);
    }
}


// === 5. Função Principal (Main) e Leitura dos Casos de Teste ===
int main() {
    // Número de casos (cidades)
    int NC; 
    
    // Leitura otimizada do NC
    if (scanf("%d", &NC) != 1) return 1;

    // Loop principal: Processa cada caso de teste (cidade)
    for (int i = 0; i < NC; i++) {
        // Variáveis para cada caso de teste
        int N; // Quantidade de pessoas na cidade
        int altura_lida;
        
        // 1. Inicializa uma nova árvore para a cidade
        arvore raiz_cidade = inicializar_arvore(); 

        // Leitura otimizada do N
        if (scanf("%d", &N) != 1) return 1;

        // Loop interno: Leitura e inserção de cada altura
        for (int j = 0; j < N; j++) {
            // Leitura da altura
            if (scanf("%d", &altura_lida) != 1) {
                // Se a leitura falhar antes de N pessoas, sai (erro de entrada)
                break; 
            }
            
            // 2. Insere a altura na ABB
            raiz_cidade = inserir_na_abb(raiz_cidade, altura_lida);
        }

        // --- Saída do Caso de Teste ---
        // 3. Inicializa o controle de espaço e imprime a lista ordenada
        primeiro_elemento = 1; // 1 significa que o próximo elemento a ser impresso é o primeiro
        Erd(raiz_cidade);
        
        // 4. Imprime a quebra de linha após o caso de teste
        printf("\n"); 

        // 5. Libera a memória alocada para esta árvore
        liberar_arvore(raiz_cidade); 
    }

    return 0;
}