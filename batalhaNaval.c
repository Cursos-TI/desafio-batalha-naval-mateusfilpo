#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5

#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

int main() {
    /*
        Tabuleiro principal do jogo.

        0 = água
        3 = navio
        5 = área afetada por habilidade
    */
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    /*
        Vetor usado para representar os navios.
        Cada navio possui tamanho fixo igual a 3.
    */
    int navio[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};

    /*
        Matrizes das habilidades especiais.

        Cada matriz possui tamanho 5x5.
        0 = posição não afetada
        1 = posição afetada
    */
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    /*
        Coordenadas dos navios.
    */
    int linhaHorizontal = 2;
    int colunaHorizontal = 3;

    int linhaVertical = 5;
    int colunaVertical = 6;

    int linhaDiagonalDireita = 0;
    int colunaDiagonalDireita = 0;

    int linhaDiagonalEsquerda = 0;
    int colunaDiagonalEsquerda = 9;

    /*
        Pontos de origem das habilidades no tabuleiro.

        Para Cruz e Octaedro, a origem representa o centro da habilidade.

        Para o Cone, a origem também será usada como referência central,
        mas o formato do cone se expande para baixo dentro da matriz 5x5.
    */
    int origemConeLinha = 3;
    int origemConeColuna = 2;

    int origemCruzLinha = 6;
    int origemCruzColuna = 2;

    int origemOctaedroLinha = 6;
    int origemOctaedroColuna = 8;

    int posicaoValida = 1;

    /*
        Inicializa o tabuleiro com água.
    */
    for (int linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
        for (int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
            tabuleiro[linha][coluna] = AGUA;
        }
    }

    /*
        Posiciona o navio horizontal.
        Ele ocupa três posições na mesma linha.
    */
    if (colunaHorizontal + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaHorizontal][colunaHorizontal + i] == NAVIO) {
                posicaoValida = 0;
                break;
            }

            tabuleiro[linhaHorizontal][colunaHorizontal + i] = navio[i];
        }
    } else {
        posicaoValida = 0;
    }

    /*
        Posiciona o navio vertical.
        Ele ocupa três posições na mesma coluna.
    */
    if (posicaoValida && linhaVertical + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaVertical + i][colunaVertical] == NAVIO) {
                posicaoValida = 0;
                break;
            }

            tabuleiro[linhaVertical + i][colunaVertical] = navio[i];
        }
    } else if (posicaoValida == 1) {
        posicaoValida = 0;
    }

    /*
        Posiciona o navio diagonal descendo para a direita.

        A cada passo:
        - linha aumenta
        - coluna aumenta
    */
    if (
        posicaoValida &&
        linhaDiagonalDireita + TAMANHO_NAVIO <= TAMANHO_TABULEIRO &&
        colunaDiagonalDireita + TAMANHO_NAVIO <= TAMANHO_TABULEIRO
    ) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaDiagonalDireita + i][colunaDiagonalDireita + i] == NAVIO) {
                posicaoValida = 0;
                break;
            }

            tabuleiro[linhaDiagonalDireita + i][colunaDiagonalDireita + i] = navio[i];
        }
    } else if (posicaoValida == 1) {
        posicaoValida = 0;
    }

    /*
        Posiciona o navio diagonal descendo para a esquerda.

        A cada passo:
        - linha aumenta
        - coluna diminui
    */
    if (
        posicaoValida &&
        linhaDiagonalEsquerda + TAMANHO_NAVIO <= TAMANHO_TABULEIRO &&
        colunaDiagonalEsquerda - TAMANHO_NAVIO + 1 >= 0
    ) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaDiagonalEsquerda + i][colunaDiagonalEsquerda - i] == NAVIO) {
                posicaoValida = 0;
                break;
            }

            tabuleiro[linhaDiagonalEsquerda + i][colunaDiagonalEsquerda - i] = navio[i];
        }
    } else if (posicaoValida == 1) {
        posicaoValida = 0;
    }

    /*
        Construção da matriz da habilidade Cone.

        O cone aponta para baixo.

        A ideia é:
        - linha 0: apenas o centro é afetado
        - linha 1: centro e posições vizinhas
        - linha 2: uma faixa maior
        - linhas abaixo seguem a mesma lógica de expansão

        Como a matriz tem tamanho 5x5, o centro está na coluna 2.
    */
    for (int linha = 0; linha < TAMANHO_HABILIDADE; linha++) {
        for (int coluna = 0; coluna < TAMANHO_HABILIDADE; coluna++) {
            int centro = TAMANHO_HABILIDADE / 2;

            if (coluna >= centro - linha && coluna <= centro + linha) {
                cone[linha][coluna] = 1;
            } else {
                cone[linha][coluna] = 0;
            }
        }
    }

    /*
        Construção da matriz da habilidade Cruz.

        A cruz afeta:
        - toda a linha central
        - toda a coluna central
    */
    for (int linha = 0; linha < TAMANHO_HABILIDADE; linha++) {
        for (int coluna = 0; coluna < TAMANHO_HABILIDADE; coluna++) {
            int centro = TAMANHO_HABILIDADE / 2;

            if (linha == centro || coluna == centro) {
                cruz[linha][coluna] = 1;
            } else {
                cruz[linha][coluna] = 0;
            }
        }
    }

    /*
        Construção da matriz da habilidade Octaedro.

        A vista frontal do octaedro parece um losango.

        Usamos a distância em relação ao centro:
        - quanto mais perto do centro, mais provável ser afetado
        - se a distância vertical + distância horizontal for menor ou igual ao centro,
          a posição faz parte do losango.
    */
    for (int linha = 0; linha < TAMANHO_HABILIDADE; linha++) {
        for (int coluna = 0; coluna < TAMANHO_HABILIDADE; coluna++) {
            int centro = TAMANHO_HABILIDADE / 2;

            int distanciaLinha = linha - centro;
            int distanciaColuna = coluna - centro;

            if (distanciaLinha < 0) {
                distanciaLinha = distanciaLinha * -1;
            }

            if (distanciaColuna < 0) {
                distanciaColuna = distanciaColuna * -1;
            }

            if (distanciaLinha + distanciaColuna <= centro) {
                octaedro[linha][coluna] = 1;
            } else {
                octaedro[linha][coluna] = 0;
            }
        }
    }

    /*
        Sobreposição da habilidade Cone no tabuleiro.

        A matriz da habilidade é percorrida com loops aninhados.
        Quando a posição da matriz vale 1, calculamos a posição equivalente
        no tabuleiro.

        Se estiver dentro dos limites e não tiver navio, marcamos com 5.
    */
    for (int linha = 0; linha < TAMANHO_HABILIDADE; linha++) {
        for (int coluna = 0; coluna < TAMANHO_HABILIDADE; coluna++) {
            if (cone[linha][coluna] == 1) {
                int linhaTabuleiro = origemConeLinha + linha;
                int colunaTabuleiro = origemConeColuna + coluna - (TAMANHO_HABILIDADE / 2);

                if (
                    linhaTabuleiro >= 0 &&
                    linhaTabuleiro < TAMANHO_TABULEIRO &&
                    colunaTabuleiro >= 0 &&
                    colunaTabuleiro < TAMANHO_TABULEIRO &&
                    tabuleiro[linhaTabuleiro][colunaTabuleiro] != NAVIO
                ) {
                    tabuleiro[linhaTabuleiro][colunaTabuleiro] = HABILIDADE;
                }
            }
        }
    }

    /*
        Sobreposição da habilidade Cruz no tabuleiro.

        Como a origem da cruz é o centro, deslocamos a matriz 5x5
        para que o centro dela fique exatamente na origem definida.
    */
    for (int linha = 0; linha < TAMANHO_HABILIDADE; linha++) {
        for (int coluna = 0; coluna < TAMANHO_HABILIDADE; coluna++) {
            if (cruz[linha][coluna] == 1) {
                int linhaTabuleiro = origemCruzLinha + linha - (TAMANHO_HABILIDADE / 2);
                int colunaTabuleiro = origemCruzColuna + coluna - (TAMANHO_HABILIDADE / 2);

                if (
                    linhaTabuleiro >= 0 &&
                    linhaTabuleiro < TAMANHO_TABULEIRO &&
                    colunaTabuleiro >= 0 &&
                    colunaTabuleiro < TAMANHO_TABULEIRO &&
                    tabuleiro[linhaTabuleiro][colunaTabuleiro] != NAVIO
                ) {
                    tabuleiro[linhaTabuleiro][colunaTabuleiro] = HABILIDADE;
                }
            }
        }
    }

    /*
        Sobreposição da habilidade Octaedro no tabuleiro.

        O mesmo processo da cruz:
        - percorremos a matriz da habilidade
        - se a posição vale 1, calculamos sua posição no tabuleiro
        - validamos os limites
        - marcamos com 5, desde que não exista navio naquela posição
    */
    for (int linha = 0; linha < TAMANHO_HABILIDADE; linha++) {
        for (int coluna = 0; coluna < TAMANHO_HABILIDADE; coluna++) {
            if (octaedro[linha][coluna] == 1) {
                int linhaTabuleiro = origemOctaedroLinha + linha - (TAMANHO_HABILIDADE / 2);
                int colunaTabuleiro = origemOctaedroColuna + coluna - (TAMANHO_HABILIDADE / 2);

                if (
                    linhaTabuleiro >= 0 &&
                    linhaTabuleiro < TAMANHO_TABULEIRO &&
                    colunaTabuleiro >= 0 &&
                    colunaTabuleiro < TAMANHO_TABULEIRO &&
                    tabuleiro[linhaTabuleiro][colunaTabuleiro] != NAVIO
                ) {
                    tabuleiro[linhaTabuleiro][colunaTabuleiro] = HABILIDADE;
                }
            }
        }
    }

    /*
        Exibição final do tabuleiro.
    */
    if (posicaoValida) {
        printf("Tabuleiro Batalha Naval com Habilidades:\n\n");

        for (int linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
            for (int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
                printf("%d ", tabuleiro[linha][coluna]);
            }

            printf("\n");
        }
    } else {
        printf("Erro: posicionamento inválido de navios.\n");
    }

    return 0;
}