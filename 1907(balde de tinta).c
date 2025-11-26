#include <stdio.h>

#define MAX 1024

char grid[MAX][MAX];
int visited[MAX][MAX];

int N, M;

// Movimentos: baixo, cima, direita, esquerda
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void dfs(int sx, int sy) {
    // Stack manual para DFS iterativa
    int stackX[MAX * MAX];
    int stackY[MAX * MAX];
    int top = 0;

    stackX[top] = sx;
    stackY[top] = sy;
    top++;

    visited[sx][sy] = 1;

    while (top > 0) {
        top--;
        int x = stackX[top];
        int y = stackY[top];

        // Explora os 4 vizinhos
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // Checa limites
            if (nx < 0 || nx >= N || ny < 0 || ny >= M)
                continue;

            // Checa se é branco e não visitado
            if (grid[nx][ny] == '.' && !visited[nx][ny]) {
                visited[nx][ny] = 1;
                stackX[top] = nx;
                stackY[top] = ny;
                top++;
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);

    // Lê a imagem
    for (int i = 0; i < N; i++) {
        scanf("%s", grid[i]);
    }

    int count = 0;

    // Varre toda a matriz
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {

            // Encontrou uma nova região branca
            if (grid[i][j] == '.' && !visited[i][j]) {
                dfs(i, j);
                count++;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}
