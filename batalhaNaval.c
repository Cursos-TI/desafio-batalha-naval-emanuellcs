#include <stdio.h>
#include <string.h> // Para memset

#define TAM 10

// Função para imprimir o tabuleiro
void imprimirTabuleiro(int m[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Limpar tabuleiro
void limparTabuleiro(int m[TAM][TAM]) {
    memset(m, 0, sizeof(int) * TAM * TAM);
}

// Habilidade: Cone
void habilidadeCone(int m[TAM][TAM], int cx, int cy, int altura) {
    for (int i = 0; i < altura; i++) {
        for (int j = -i; j <= i; j++) {
            int nx = cx + i;
            int ny = cy + j;
            if (nx >= 0 && nx < TAM && ny >= 0 && ny < TAM)
                m[nx][ny] = 1;
        }
    }
}

// Habilidade: Cruz
void habilidadeCruz(int m[TAM][TAM], int cx, int cy, int tamanho) {
    for (int i = -tamanho; i <= tamanho; i++) {
        int nx = cx + i;
        int ny = cy;
        if (nx >= 0 && nx < TAM)
            m[nx][ny] = 1;
    }
    for (int j = -tamanho; j <= tamanho; j++) {
        int nx = cx;
        int ny = cy + j;
        if (ny >= 0 && ny < TAM)
            m[nx][ny] = 1;
    }
}

// Habilidade: Octaedro
void habilidadeOctaedro(int m[TAM][TAM], int cx, int cy, int alcance) {
    for (int dx = -alcance; dx <= alcance; dx++) {
        for (int dy = -alcance; dy <= alcance; dy++) {
            if (abs(dx) + abs(dy) <= alcance) {
                int nx = cx + dx;
                int ny = cy + dy;
                if (nx >= 0 && nx < TAM && ny >= 0 && ny < TAM)
                    m[nx][ny] = 1;
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];

    // Testando Habilidade Cone
    limparTabuleiro(tabuleiro);
    habilidadeCone(tabuleiro, 2, 4, 3);
    printf("Habilidade: Cone\n");
    imprimirTabuleiro(tabuleiro);

    // Testando Habilidade Cruz
    limparTabuleiro(tabuleiro);
    habilidadeCruz(tabuleiro, 4, 4, 3);
    printf("Habilidade: Cruz\n");
    imprimirTabuleiro(tabuleiro);

    // Testando Habilidade Octaedro
    limparTabuleiro(tabuleiro);
    habilidadeOctaedro(tabuleiro, 4, 4, 2);
    printf("Habilidade: Octaedro\n");
    imprimirTabuleiro(tabuleiro);

    return 0;
}