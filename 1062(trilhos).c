#include <stdio.h>
#include <stdbool.h>

// Tamanho máximo do trem (N <= 1000)
#define MAX_VAGOES 1001

// --- Simulação da Pilha (Stack) para a Pista de Manobra ---

int stack[MAX_VAGOES];
int top = -1;

void push(int value) {
    if (top < MAX_VAGOES - 1) {
        stack[++top] = value;
    }
}

int pop() {
    if (top != -1) {
        return stack[top--];
    }
    return -1; // Sinaliza erro ou pilha vazia
}

int peek() {
    if (top != -1) {
        return stack[top];
    }
    return -1; // Sinaliza pilha vazia
}

bool isEmpty() {
    return top == -1;
}

void initialize_stack() {
    top = -1;
}

// --- Lógica Principal ---

void solve_train_reorganization(int N) {
    int desired_output[MAX_VAGOES];
    int i, next_coming;
    bool possible;

    // Loop para processar múltiplas permutações para o mesmo N
    // Lê a primeira linha da permutação
    while (scanf("%d", &desired_output[0]) == 1 && desired_output[0] != 0) {
        // Lê os N-1 vagões restantes da permutação
        for (i = 1; i < N; i++) {
            scanf("%d", &desired_output[i]);
        }

        initialize_stack();
        next_coming = 1; // O primeiro vagão que chega da Direção A
        i = 0;           // Índice para o próximo vagão desejado na saída (a_i)
        possible = true;

        // Itera sobre a sequência de saída desejada
        while (i < N) {
            int current_desired = desired_output[i];

            // 1. Tenta colocar vagões da Direção A na estação até que o desejado chegue
            while (next_coming <= N && (isEmpty() || peek() != current_desired)) {
                // Se o próximo a entrar é o que queremos OU se não há mais vagões para entrar
                if (next_coming == current_desired) {
                    // O vagão desejado é o próximo a entrar, mas ele sai direto (não passa pela stack)
                    break;
                }
                
                // Se não é o vagão desejado, e ainda há vagões, coloque na estação
                push(next_coming);
                next_coming++;
            }

            // 2. Verifica a condição de saída
            
            // A. O vagão desejado está no topo da Pilha
            if (!isEmpty() && peek() == current_desired) {
                pop(); // Sai da estação para a Direção B
                i++;   // Avance para o próximo vagão desejado
            } 
            // B. O vagão desejado é o próximo a entrar (sai direto)
            else if (next_coming == current_desired) {
                next_coming++; // Vagão sai direto da Direção A para a Direção B
                i++;           // Avance para o próximo vagão desejado
            }
            // C. Falha: O vagão desejado não está na pilha, nem é o próximo a entrar,
            // e já colocamos todos os vagões possíveis na pilha (next_coming > N)
            else {
                possible = false;
                break;
            }
        }
        
        // --- Saída ---
        if (possible) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
}

// --- Função Principal (Main) ---

int main() {
    int N;

    // Loop principal para processar múltiplos blocos de entrada
    while (scanf("%d", &N) == 1 && N != 0) {
        if (N >= 1 && N <= 1000) {
            solve_train_reorganization(N);
        }
        
        // Imprime a linha em branco após cada bloco (exceto após o último zero)
        printf("\n");
    }

    return 0;
}