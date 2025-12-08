#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do nó com chave do tipo char (caractere)
typedef struct Node {
    char key;
    struct Node* left;
    struct Node* right;
} Node;

// Função para criar um novo nó
Node* createNode(char key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        // Trata erro de alocação
        perror("Erro na alocação de memória");
        exit(1);
    }
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Função para inserir um valor na Árvore Binária de Pesquisa (ABP)
Node* insert(Node* root, char key) {
    if (root == NULL) {
        return createNode(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) { // Garante a regra da ABP (maior vai para a direita)
        root->right = insert(root->right, key);
    } 
    // Se for igual, não faz nada (o problema garante que não haverá duplicatas)

    return root; 
}

// Função para pesquisar um valor na ABP
// Retorna 1 se encontrado, 0 caso contrário
int search(Node* root, char key) {
    if (root == NULL) {
        return 0; // Não encontrado (chegou ao fim da subárvore)
    }

    if (key == root->key) {
        return 1; // Encontrado!
    } 
    
    if (key < root->key) {
        return search(root->left, key); // Busca na esquerda
    } else {
        return search(root->right, key); // Busca na direita
    }
}


// --- Funções de Percurso com controle de formatação ---

// O parâmetro 'first_ptr' é um ponteiro para um inteiro (flag) que controla se
// o elemento atual é o primeiro a ser impresso na linha, garantindo a ausência de espaço no final.

// Percurso Pré-ordem (Raiz -> Esquerda -> Direita)
void preorder_traversal(Node* root, int* first_ptr) {
    if (root != NULL) {
        // 1. Raiz
        if (*first_ptr) {
            printf("%c", root->key);
            *first_ptr = 0;
        } else {
            printf(" %c", root->key);
        }
        
        // 2. Esquerda
        preorder_traversal(root->left, first_ptr);
        // 3. Direita
        preorder_traversal(root->right, first_ptr);
    }
}

// Percurso In-ordem (Esquerda -> Raiz -> Direita) -> Retorna elementos em ordem alfabética
void inorder_traversal(Node* root, int* first_ptr) {
    if (root != NULL) {
        // 1. Esquerda
        inorder_traversal(root->left, first_ptr);
        
        // 2. Raiz
        if (*first_ptr) {
            printf("%c", root->key);
            *first_ptr = 0;
        } else {
            printf(" %c", root->key);
        }
        
        // 3. Direita
        inorder_traversal(root->right, first_ptr);
    }
}

// Percurso Pós-ordem (Esquerda -> Direita -> Raiz)
void postorder_traversal(Node* root, int* first_ptr) {
    if (root != NULL) {
        // 1. Esquerda
        postorder_traversal(root->left, first_ptr);
        // 2. Direita
        postorder_traversal(root->right, first_ptr);
        
        // 3. Raiz
        if (*first_ptr) {
            printf("%c", root->key);
            *first_ptr = 0;
        } else {
            printf(" %c", root->key);
        }
    }
}

// Função para liberar a memória da árvore (boa prática)
void destroyTree(Node* root) {
    if (root != NULL) {
        destroyTree(root->left);
        destroyTree(root->right);
        free(root);
    }
}

// --- Função Principal: Leitura de Comandos ---

int main() {
    Node* root = NULL;
    char command[10]; // Para armazenar "I", "P", "INFIXA", etc.
    char key_char;    // Para armazenar o elemento (caractere)
    int first_element_flag; // Flag de formatação (passada por referência virtual)

    // Loop principal de leitura: continua até o final do arquivo (EOF)
    while (scanf("%s", command) != EOF) {
        
        if (strcmp(command, "I") == 0) {
            // Comando de Inserção: "I n"
            // Lê o caractere a ser inserido. O espaço antes de %c consome whitespaces.
            if (scanf(" %c", &key_char) != 1) break;
            root = insert(root, key_char);
            // O comando 'I' não produz saída.
            
        } else if (strcmp(command, "P") == 0) {
            // Comando de Pesquisa: "P n"
            if (scanf(" %c", &key_char) != 1) break;
            
            if (search(root, key_char)) {
                printf("%c existe\n", key_char);
            } else {
                printf("%c nao existe\n", key_char);
            }
            
        } else if (strcmp(command, "INFIXA") == 0) {
            // Percurso In-ordem
            first_element_flag = 1;
            inorder_traversal(root, &first_element_flag);
            printf("\n");
            
        } else if (strcmp(command, "PREFIXA") == 0) {
            // Percurso Pré-ordem
            first_element_flag = 1;
            preorder_traversal(root, &first_element_flag);
            printf("\n");
            
        } else if (strcmp(command, "POSFIXA") == 0) {
            // Percurso Pós-ordem
            first_element_flag = 1;
            postorder_traversal(root, &first_element_flag);
            printf("\n");
        }
        // Ignora outros comandos desconhecidos
    }
    
    // Libera a memória no final do programa
    destroyTree(root);
    
    return 0;
}
