#include <stdio.h>
#include <stdlib.h>

// ===================================
// ESTRUTURA DA PILHA
// ===================================

typedef struct No {
    char caractere;
    struct No *prox;
} No;

typedef struct {
    No *topo;
} Pilha;

// ===================================
// FUNÇÕES AUXILIARES DA PILHA
// ===================================

Pilha* cria_pilha() {
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    if (p != NULL) {
        p->topo = NULL;
    }
    return p;
}

int is_empty(Pilha *p) {
    return p->topo == NULL;
}

void push(Pilha *p, char item) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        return; 
    }
    
    novo->caractere = item;
    novo->prox = p->topo;

    p->topo = novo;
}

void pop(Pilha *p) {
    if (is_empty(p)) {
        return;
    }
    
    No *aux = p->topo;
    p->topo = aux->prox;
    free(aux);
}

void libera_pilha(Pilha *p) {
    No *aux;
    while (p->topo != NULL) {
        aux = p->topo;
        p->topo = p->topo->prox;
        free(aux);
    }
    free(p);
}

// ===================================
// 🚀 FUNÇÃO PRINCIPAL
// ===================================

int main() {
    char expr[1001];
    
    while (fgets(expr, 1001, stdin) != NULL) {
        Pilha *p = cria_pilha();
        int correto = 1;

        for (int i = 0; expr[i] != '\0' && expr[i] != '\n'; i++) {
            char current_char = expr[i];

            if (current_char == '(') {
                push(p, current_char);
            } 
            
            else if (current_char == ')') {
                if (is_empty(p)) {
                    correto = 0;
                    break; 
                }
                
                pop(p);
            }
        }

        if (correto && is_empty(p)) {
            printf("correct\n");
        } else {
            printf("incorrect\n");
        }
        
        libera_pilha(p);
    }

    return 0;
}