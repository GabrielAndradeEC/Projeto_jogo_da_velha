#include <stdio.h>
#include <locale.h>

setlocale("0, Portuguese");

// Função para imprimir o tabuleiro
void imprimeTabuleiro(char tabuleiro[3][3]) {
    printf("  0 1 2\n");
    for (int i = 0; i < 3; i++) {
        printf("%d ", i);
        for (int j = 0; j < 3; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Função para verificar se há um vencedor
char verificaVencedor(char tabuleiro[3][3]) {
    // Verificar linhas e colunas
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2] && tabuleiro[i][0] != ' ') {
            return tabuleiro[i][0]; // Vencedor na linha i
        }
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i] && tabuleiro[0][i] != ' ') {
            return tabuleiro[0][i]; // Vencedor na coluna i
        }
    }

    // Verificar diagonais
    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2] && tabuleiro[0][0] != ' ') {
        return tabuleiro[0][0]; // Vencedor na diagonal principal
    }
    if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0] && tabuleiro[0][2] != ' ') {
        return tabuleiro[0][2]; // Vencedor na diagonal secundária
    }

    return ' '; // Nenhum vencedor ainda
}

// Função para verificar se o tabuleiro está cheio (empate)
int tabuleiroCheio(char tabuleiro[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[i][j] == ' ') {
                return 0; // Ainda há espaço vazio
            }
        }
    }
    return 1; // Tabuleiro cheio (empate)
}

int main() {
    char tabuleiro[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int linha, coluna;
    char jogador = 'X';

    do {
        imprimeTabuleiro(tabuleiro);

        // Solicita a jogada do jogador atual
        printf("Jogador %c, insira a linha e a coluna (0-2) separadas por espaço: ", jogador);
        scanf("%d %d", &linha, &coluna);

        // Verifica se a jogada é válida
        if (linha < 0 || linha >= 3 || coluna < 0 || coluna >= 3 || tabuleiro[linha][coluna] != ' ') {
            printf("Jogada inválida. Tente novamente.\n");
            continue;
        }

        // Atualiza o tabuleiro com a jogada
        tabuleiro[linha][coluna] = jogador;

        // Verifica se há um vencedor
        char vencedor = verificaVencedor(tabuleiro);
        if (vencedor != ' ') {
            imprimeTabuleiro(tabuleiro);
            printf("Jogador %c venceu!\n", vencedor);
            break;
        }

        // Verifica se o tabuleiro está cheio (empate)
        if (tabuleiroCheio(tabuleiro)) {
            imprimeTabuleiro(tabuleiro);
            printf("Empate! O jogo terminou sem vencedor.\n");
            break;
        }

        // Alterna para o próximo jogador
        jogador = (jogador == 'X') ? 'O' : 'X';

    } while (1); // Loop infinito (o jogo continua até que haja um vencedor ou empate)

    return 0;
}

