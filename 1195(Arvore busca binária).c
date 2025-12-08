#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do nó da Árvore Binária
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

// Função para criar um novo nó
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Erro na alocação de memória");
        exit(1);
    }
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Função para inserir um valor na Árvore Binária de Busca (ABB)
Node* insert(Node* root, int key) {
    // Se a árvore/subárvore estiver vazia, cria o novo nó e retorna ele
    if (root == NULL) {
        return createNode(key);
    }

    // Se o valor for menor, insere na subárvore esquerda
    if (key < root->key) {
        root->left = insert(root->left, key);
    } 
    // Se o valor for maior, insere na subárvore direita
    else {
        root->right = insert(root->right, key);
    }

    return root; // Retorna a raiz (inalterada)
}

// Variável global para controlar a formatação da saída (evitar espaço após o último)
int first = 1;

// --- Funções de Percurso ---

// Percurso Pré-ordem (Raiz -> Esquerda -> Direita)
void preorder_traversal(Node* root) {
    if (root != NULL) {
        // 1. Raiz
        if (first) {
            printf("%d", root->key);
            first = 0;
        } else {
            printf(" %d", root->key);
        }
        
        // 2. Esquerda
        preorder_traversal(root->left);
        // 3. Direita
        preorder_traversal(root->right);
    }
}

// Percurso In-ordem (Esquerda -> Raiz -> Direita)
void inorder_traversal(Node* root) {
    if (root != NULL) {
        // 1. Esquerda
        inorder_traversal(root->left);
        
        // 2. Raiz
        if (first) {
            printf("%d", root->key);
            first = 0;
        } else {
            printf(" %d", root->key);
        }
        
        // 3. Direita
        inorder_traversal(root->right);
    }
}

// Percurso Pós-ordem (Esquerda -> Direita -> Raiz)
void postorder_traversal(Node* root) {
    if (root != NULL) {
        // 1. Esquerda
        postorder_traversal(root->left);
        // 2. Direita
        postorder_traversal(root->right);
        
        // 3. Raiz
        if (first) {
            printf("%d", root->key);
            first = 0;
        } else {
            printf(" %d", root->key);
        }
    }
}

// Função para liberar a memória da árvore
void destroyTree(Node* root) {
    if (root != NULL) {
        destroyTree(root->left);
        destroyTree(root->right);
        free(root);
    }
}

// --- Função Principal ---

int main() {
    int C, N, i, key, case_num = 1;
    Node* root;

    // Leitura do número de casos de teste
    if (scanf("%d", &C) != 1) return 0;
    
    while (C-- > 0) {
        // 1. Leitura de N (quantidade de números)
        if (scanf("%d", &N) != 1) break;

        // Inicializa a raiz da árvore
        root = NULL;

        // 2. Leitura dos N números e construção da ABB
        for (i = 0; i < N; i++) {
            if (scanf("%d", &key) != 1) break;
            root = insert(root, key);
        }

        // 3. Impressão da Saída
        printf("Case %d:\n", case_num++);

        // Percurso Pré-ordem
        printf("Pre.: ");
        first = 1;
        preorder_traversal(root);
        printf("\n");

        // Percurso In-ordem
        printf("In..: ");
        first = 1;
        inorder_traversal(root);
        printf("\n");

        // Percurso Pós-ordem
        printf("Post: ");
        first = 1;
        postorder_traversal(root);
        printf("\n");
        
        // 4. Libera a memória e adiciona a linha em branco entre casos
        destroyTree(root);
        
        if (C > 0) {
            printf("\n"); // Linha em branco entre casos
        } else {
             // O beecrowd espera uma linha em branco após o último caso também
             printf("\n");
        }
    }

    return 0;
}