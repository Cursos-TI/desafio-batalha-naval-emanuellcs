#include <stdio.h>
#include <stdlib.h> // Para abs()
#include <string.h> // Para memset

#define TAM 10
#define TAM_HAB 5 // Tamanho das matrizes de habilidade (ímpar)

// Valores do tabuleiro
#define AGUA 0
#define NAVIO 3
#define HABILIDADE_CONE 5
#define HABILIDADE_CRUZ 6
#define HABILIDADE_OCTAEDRO 7

// ---------- Funções utilitárias ----------
void imprimirMatriz(int linhas, int cols, int m[linhas][cols]) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void limparMatriz(int linhas, int cols, int m[linhas][cols]) {
    memset(m, 0, sizeof(int) * linhas * cols);
}

// ---------- Posicionamento de navios ----------
void posicionarNavios(int tab[TAM][TAM]) {
    // Navio horizontal (linha 1)
    for (int j = 0; j < 3; j++) {
        tab[1][j] = NAVIO;
    }
    // Navio vertical (coluna 5)
    for (int i = 0; i < 3; i++) {
        tab[i][5] = NAVIO;
    }
    // Navio diagonal descendente
    for (int i = 0; i < 3; i++) {
        tab[5 + i][2 + i] = NAVIO;
    }
    // Navio diagonal ascendente
    for (int i = 0; i < 3; i++) {
        tab[8 - i][7 - i] = NAVIO;
    }
}

// ---------- Geração das matrizes de habilidade ----------
void gerarCone(int m[TAM_HAB][TAM_HAB]) {
    limparMatriz(TAM_HAB, TAM_HAB, m);
    int centro = TAM_HAB / 2;
    for (int i = 0; i <= centro; i++) {
        for (int j = -i; j <= i; j++) {
            m[i][centro + j] = 1;
        }
    }
}

void gerarCruz(int m[TAM_HAB][TAM_HAB]) {
    limparMatriz(TAM_HAB, TAM_HAB, m);
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        m[centro][i] = 1;
        m[i][centro] = 1;
    }
}

void gerarOctaedro(int m[TAM_HAB][TAM_HAB]) {
    limparMatriz(TAM_HAB, TAM_HAB, m);
    int centro = TAM_HAB / 2;
    int alcance = centro;
    for (int dx = -alcance; dx <= alcance; dx++) {
        for (int dy = -alcance; dy <= alcance; dy++) {
            if (abs(dx) + abs(dy) <= alcance) {
                m[centro + dx][centro + dy] = 1;
            }
        }
    }
}

// ---------- Sobreposição ----------
void aplicarHabilidade(
    int tab[TAM][TAM],
    int hab[TAM_HAB][TAM_HAB],
    int cx, int cy, // posição central no tabuleiro
    int valorHabilidade
) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (hab[i][j] == 1) {
                int nx = cx + (i - centro);
                int ny = cy + (j - centro);
                if (nx >= 0 && nx < TAM && ny >= 0 && ny < TAM) {
                    if (tab[nx][ny] == AGUA) {
                        tab[nx][ny] = valorHabilidade;
                    }
                }
            }
        }
    }
}

// ---------- Função principal ----------
int main() {
    int tabuleiro[TAM][TAM];
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    // Inicializar tabuleiro com água
    limparMatriz(TAM, TAM, tabuleiro);

    // Posicionar navios
    posicionarNavios(tabuleiro);

    printf("Tabuleiro inicial com navios:\n");
    imprimirMatriz(TAM, TAM, tabuleiro);

    // Criar padrões das habilidades
    gerarCone(cone);
    gerarCruz(cruz);
    gerarOctaedro(octaedro);

    printf("Matriz Cone (5x5):\n");
    imprimirMatriz(TAM_HAB, TAM_HAB, cone);

    printf("Matriz Cruz (5x5):\n");
    imprimirMatriz(TAM_HAB, TAM_HAB, cruz);

    printf("Matriz Octaedro (5x5):\n");
    imprimirMatriz(TAM_HAB, TAM_HAB, octaedro);

    // Aplicar habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, 2, 4, HABILIDADE_CONE);
    aplicarHabilidade(tabuleiro, cruz, 5, 5, HABILIDADE_CRUZ);
    aplicarHabilidade(tabuleiro, octaedro, 7, 2, HABILIDADE_OCTAEDRO);

    printf("Tabuleiro final após aplicar habilidades:\n");
    imprimirMatriz(TAM, TAM, tabuleiro);

    return 0;
}