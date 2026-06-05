#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

int main() {
    /*
        Matriz 10x10 que representa o tabuleiro.

        Valor 0 = água
        Valor 3 = parte de um navio
    */
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    /*
        Vetores unidimensionais que representam os navios.

        Cada posição do vetor representa uma parte do navio.
        Como o tamanho do navio é 3, cada vetor possui 3 posições.
    */
    int navioHorizontal[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};
    int navioVertical[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};

    /*
        Coordenadas iniciais dos navios.

        Linha e coluna começam em 0.
        Portanto, em um tabuleiro 10x10, os índices válidos vão de 0 até 9.
    */
    int linhaNavioHorizontal = 2;
    int colunaNavioHorizontal = 3;

    int linhaNavioVertical = 5;
    int colunaNavioVertical = 6;

    int posicaoValida = 1;

    /*
        Inicializa todo o tabuleiro com água.

        O loop externo percorre as linhas.
        O loop interno percorre as colunas.
    */
    for (int linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
        for (int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
            tabuleiro[linha][coluna] = AGUA;
        }
    }

    /*
        Validação do navio horizontal.

        Como ele anda para a direita, precisamos garantir que:
        coluna inicial + tamanho do navio não ultrapasse o tamanho do tabuleiro.
    */
    if (colunaNavioHorizontal + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        printf("Erro: o navio horizontal ultrapassa os limites do tabuleiro.\n");
        posicaoValida = 0;
    }

    /*
        Validação do navio vertical.

        Como ele anda para baixo, precisamos garantir que:
        linha inicial + tamanho do navio não ultrapasse o tamanho do tabuleiro.
    */
    if (linhaNavioVertical + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        printf("Erro: o navio vertical ultrapassa os limites do tabuleiro.\n");
        posicaoValida = 0;
    }

    /*
        Se as posições estiverem dentro dos limites,
        posicionamos primeiro o navio horizontal.
    */
    if (posicaoValida) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linhaNavioHorizontal][colunaNavioHorizontal + i] = navioHorizontal[i];
        }

        /*
            Antes de posicionar o navio vertical, verificamos se ele
            vai ocupar alguma posição que já possui outro navio.

            Se encontrar valor 3, significa que há sobreposição.
        */
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaNavioVertical + i][colunaNavioVertical] == NAVIO) {
                printf("Erro: os navios estão se sobrepondo.\n");
                posicaoValida = 0;
            }
        }
    }

    /*
        Se não houve erro de limite nem sobreposição,
        posicionamos o navio vertical.
    */
    if (posicaoValida) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linhaNavioVertical + i][colunaNavioVertical] = navioVertical[i];
        }

        /*
            Exibe o tabuleiro completo.

            0 representa água.
            3 representa parte de um navio.
        */
        printf("Tabuleiro Batalha Naval:\n\n");

        for (int linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
            for (int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
                printf("%d ", tabuleiro[linha][coluna]);
            }

            printf("\n");
        }
    }

    return 0;
}