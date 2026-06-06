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
        Vetor usado para representar um navio.

        Todos os navios terão tamanho 3.
        Cada posição do vetor guarda o valor 3, que será copiado para o tabuleiro.
    */
    int navio[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};

    /*
        Coordenadas iniciais dos quatro navios.

        Os índices começam em 0.
        Em um tabuleiro 10x10, os índices válidos vão de 0 até 9.
    */

    // Navio horizontal: anda para a direita.
    int linhaHorizontal = 2;
    int colunaHorizontal = 3;

    // Navio vertical: anda para baixo.
    int linhaVertical = 5;
    int colunaVertical = 6;

    // Navio diagonal principal: linha aumenta e coluna aumenta.
    int linhaDiagonalDireita = 0;
    int colunaDiagonalDireita = 0;

    // Navio diagonal secundária: linha aumenta e coluna diminui.
    int linhaDiagonalEsquerda = 0;
    int colunaDiagonalEsquerda = 9;

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
        Validação dos limites do navio horizontal.

        Como ele anda para a direita:
        - a linha inicial precisa estar entre 0 e 9
        - a coluna inicial + tamanho do navio não pode passar de 10
    */
    if (
        linhaHorizontal < 0 ||
        linhaHorizontal >= TAMANHO_TABULEIRO ||
        colunaHorizontal < 0 ||
        colunaHorizontal + TAMANHO_NAVIO > TAMANHO_TABULEIRO
    ) {
        printf("Erro: o navio horizontal ultrapassa os limites do tabuleiro.\n");
        posicaoValida = 0;
    }

    /*
        Validação dos limites do navio vertical.

        Como ele anda para baixo:
        - a coluna inicial precisa estar entre 0 e 9
        - a linha inicial + tamanho do navio não pode passar de 10
    */
    if (
        colunaVertical < 0 ||
        colunaVertical >= TAMANHO_TABULEIRO ||
        linhaVertical < 0 ||
        linhaVertical + TAMANHO_NAVIO > TAMANHO_TABULEIRO
    ) {
        printf("Erro: o navio vertical ultrapassa os limites do tabuleiro.\n");
        posicaoValida = 0;
    }

    /*
        Validação do navio diagonal para a direita.

        Como ele desce para a direita:
        - linha aumenta
        - coluna aumenta

        Portanto:
        linha inicial + tamanho <= tamanho do tabuleiro
        coluna inicial + tamanho <= tamanho do tabuleiro
    */
    if (
        linhaDiagonalDireita < 0 ||
        colunaDiagonalDireita < 0 ||
        linhaDiagonalDireita + TAMANHO_NAVIO > TAMANHO_TABULEIRO ||
        colunaDiagonalDireita + TAMANHO_NAVIO > TAMANHO_TABULEIRO
    ) {
        printf("Erro: o navio diagonal para a direita ultrapassa os limites do tabuleiro.\n");
        posicaoValida = 0;
    }

    /*
        Validação do navio diagonal para a esquerda.

        Como ele desce para a esquerda:
        - linha aumenta
        - coluna diminui

        Portanto:
        linha inicial + tamanho <= tamanho do tabuleiro
        coluna inicial - tamanho + 1 >= 0
    */
    if (
        linhaDiagonalEsquerda < 0 ||
        linhaDiagonalEsquerda + TAMANHO_NAVIO > TAMANHO_TABULEIRO ||
        colunaDiagonalEsquerda < 0 ||
        colunaDiagonalEsquerda >= TAMANHO_TABULEIRO ||
        colunaDiagonalEsquerda - TAMANHO_NAVIO + 1 < 0
    ) {
        printf("Erro: o navio diagonal para a esquerda ultrapassa os limites do tabuleiro.\n");
        posicaoValida = 0;
    }

    /*
        Posicionamento e verificação de sobreposição.

        Antes de colocar cada parte do navio no tabuleiro,
        verificamos se a posição ainda está com água.

        Se já houver valor 3, significa que outro navio ocupa aquela posição.
    */
    if (posicaoValida) {
        // Navio horizontal
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaHorizontal][colunaHorizontal + i] == NAVIO) {
                printf("Erro: sobreposição no navio horizontal.\n");
                posicaoValida = 0;
                break;
            }

            tabuleiro[linhaHorizontal][colunaHorizontal + i] = navio[i];
        }
    }

    if (posicaoValida) {
        // Navio vertical
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaVertical + i][colunaVertical] == NAVIO) {
                printf("Erro: sobreposição no navio vertical.\n");
                posicaoValida = 0;
                break;
            }

            tabuleiro[linhaVertical + i][colunaVertical] = navio[i];
        }
    }

    if (posicaoValida) {
        // Navio diagonal descendo para a direita
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaDiagonalDireita + i][colunaDiagonalDireita + i] == NAVIO) {
                printf("Erro: sobreposição no navio diagonal para a direita.\n");
                posicaoValida = 0;
                break;
            }

            tabuleiro[linhaDiagonalDireita + i][colunaDiagonalDireita + i] = navio[i];
        }
    }

    if (posicaoValida) {
        // Navio diagonal descendo para a esquerda
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaDiagonalEsquerda + i][colunaDiagonalEsquerda - i] == NAVIO) {
                printf("Erro: sobreposição no navio diagonal para a esquerda.\n");
                posicaoValida = 0;
                break;
            }

            tabuleiro[linhaDiagonalEsquerda + i][colunaDiagonalEsquerda - i] = navio[i];
        }
    }

    /*
        Exibição final do tabuleiro.

        Se todas as posições forem válidas, o programa imprime a matriz 10x10.
    */
    if (posicaoValida) {
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