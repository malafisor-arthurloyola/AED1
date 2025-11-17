#include <stdio.h>
#include <stdlib.h> // Necessário para 'malloc'

// O nó da lista encadeada permanece o mesmo
typedef struct no {
    int valor;
    struct no* prox;
} No;

// Estrutura da Fila (precisa de início e fim)
typedef struct {
    No* inicio; // O topo (onde se remove a carta)
    No* fim;    // A base (onde se insere a carta)
} Fila;

// Inicializa a Fila
void inicializaFila(Fila* f) {
    f->inicio = NULL;
    f->fim = NULL;
}

// 📤 Enqueue (Inserir no FIM/BASE)
void enqueue(Fila *f, int valor) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro de alocação de memória!\n");
        return;
    }
    novo->valor = valor;
    novo->prox = NULL; // O novo nó SEMPRE é o último

    if (f->inicio == NULL) { // Fila vazia
        f->inicio = novo;
    } else {
        f->fim->prox = novo;
    }
    f->fim = novo;
}

// 🗑️ Dequeue (Remover do INÍCIO/TOPO) - Retorna o valor removido
int dequeue(Fila *f) {
    if (f->inicio == NULL) {
        return -1; // Valor de erro/indicação de fila vazia
    }
    No *aux = f->inicio;
    int valor = aux->valor;

    f->inicio = f->inicio->prox; // Move o início para o próximo

    if (f->inicio == NULL) { // Se a fila ficou vazia
        f->fim = NULL;
    }

    free(aux);
    return valor;
}

// ✨ Cria a Fila (a carta 1 na base é o PRIMEIRO a entrar)
// No seu problema, o 1 está no topo e o n na base.
// Em uma Fila/Queue: o 1 deve ser o primeiro a sair (inicio), e o n o último a entrar (fim).
void fazerafila(Fila *f, int n) {
    // A carta 1 é a primeira a sair (inicio da Fila)
    for (int i = 1; i <= n; i++) {
        enqueue(f, i);
    }
}

// Conta quantas cartas restam na Fila
int contaCartas(Fila *f) {
    int count = 0;
    No *aux = f->inicio;
    while (aux != NULL) {
        count++;
        aux = aux->prox;
    }
    return count;
}

// Função que implementa a lógica do problema
void algoritmo_cartas(Fila *f) {
    // Lista para guardar as cartas descartadas
    int descartadas[50]; 
    int num_descartadas = 0;
    
    // O problema continua enquanto houver 2 ou mais cartas
    while (contaCartas(f) >= 2) {
        // 1. Joga fora a carta do topo (dequeue)
        int carta_descartada = dequeue(f);
        if (carta_descartada != -1) {
            descartadas[num_descartadas++] = carta_descartada;
        }

        // 2. Move a próxima carta (a que ficou no topo) para a base (dequeue e enqueue)
        int carta_movida = dequeue(f);
        if (carta_movida != -1) {
            enqueue(f, carta_movida);
        }
    }

    // Saída: Cartas Descartadas
    printf("Discarded cards: ");
    for (int i = 0; i < num_descartadas; i++) {
        printf("%d", descartadas[i]);
        if (i < num_descartadas - 1) {
            printf(", ");
        }
    }
    printf("\n");

    // Saída: Carta Remanescente (a única que restou na fila)
    int carta_remanescente = dequeue(f);
    if (carta_remanescente != -1) {
        printf("Remaining card: %d\n", carta_remanescente);
    } else {
        // Caso em que n=1, a fila tem 1 carta inicialmente.
        // O loop 'while' acima não executa, então a carta 1 permanece.
        // É necessário tratar o caso n=1 separadamente, ou a lógica da fila ficará inconsistente.
        // Já que o problema diz "enquanto tiver 2 ou mais cartas", a saída deve ser:
        // Se n=1: Discarded cards: \n Remaining card: 1
        // Se n=0: Não deve ser processado.
        
        // No caso geral, a última carta é a única remanescente.
        // Se o loop terminou e a fila está vazia, algo está errado (a menos que n=0)
    }
    
    // Libera qualquer nó remanescente na fila (apesar de só sobrar 1 no final)
    // Para n=1, a fila tem 1 elemento, se n>=2, a fila tem 1 elemento.
    // O dequeue final garante que a fila está vazia.
}

int main() {
    int n;
    
    // Loop de leitura da entrada
    while (scanf("%d", &n) == 1 && n != 0) {
        if (n < 1 || n > 50) {
            // Ignora valores fora do limite
            continue;
        }
        
        // ⚠️ Tratamento especial para N=1: não há descarte nem movimento
        if (n == 1) {
            printf("Discarded cards:\n");
            printf("Remaining card: 1\n");
            continue; 
        }

        // 1. Inicializa a Fila
        Fila filaexemplo;
        inicializaFila(&filaexemplo);

        // 2. Preenche a Fila (1 no início, n no fim)
        fazerafila(&filaexemplo, n);

        // 3. Executa a lógica
        algoritmo_cartas(&filaexemplo);
        
        // *Não é necessário desalocar memória aqui, pois algoritmo_cartas já faz isso com dequeue.*
    }

    return 0;
}
