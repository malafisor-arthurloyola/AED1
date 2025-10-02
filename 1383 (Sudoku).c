#include <stdio.h>

int main() {
    int tabuleiros;
    scanf("%d", &tabuleiros);

    for (int t = 0; t < tabuleiros; t++) {
        int mat[9][9];
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                scanf("%d", &mat[i][j]);
            }
        }

        int valido = 1;

        // Verifica linhas
        for (int i = 0; i < 9 && valido; i++) {
            int linha[10] = {0};
            for (int j = 0; j < 9; j++) {
                linha[mat[i][j]]++;
                if (linha[mat[i][j]] > 1) {
                    valido = 0;
                }
            }
        }

        // Verifica colunas
        for (int j = 0; j < 9 && valido; j++) {
            int coluna[10] = {0};
            for (int i = 0; i < 9; i++) {
                coluna[mat[i][j]]++;
                if (coluna[mat[i][j]] > 1) {
                    valido = 0;
                }
            }
        }

        // Verifica blocos 3x3
        for (int bi = 0; bi < 9 && valido; bi += 3) {
            for (int bj = 0; bj < 9 && valido; bj += 3) {
                int bloco[10] = {0};
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        bloco[mat[bi + i][bj + j]]++;
                        if (bloco[mat[bi + i][bj + j]] > 1) {
                            valido = 0;
                        }
                    }
                }
            }
        }

        printf("Instancia %d\n", t + 1);
        if (valido)
            printf("SIM\n\n");
        else
            printf("NAO\n\n");
    }
    return 0;
}
