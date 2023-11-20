/*O código implementa um jogo da velha em C. Os jogadores ('X' e 'O') alternam turnos,	
inserindo suas jogadas em um tabuleiro 3x3. O jogo verifica vitória em linhas, colunas e diagonais.
Há opções no menu para jogar, ver créditos ou finalizar o jogo.
O código é modular e utiliza alocação dinâmica de memória para o tabuleiro.*/

/*A principal dificuldade foi a implementação do ranking, que não pode ser feito.*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Função para imprimir o tabuleiro
void imprimeTabuleiro(char** tabuleiro, int tamanho) {
    printf("  ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < tamanho; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < tamanho; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Função para verificar se há um vencedor
char verificaVencedor(char** tabuleiro, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2] && tabuleiro[i][0] != ' ') {
            return tabuleiro[i][0]; // Vencedor na linha i
        }
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i] && tabuleiro[0][i] != ' ') {
            return tabuleiro[0][i]; // Vencedor na coluna i
        }
    }

    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2] && tabuleiro[0][0] != ' ') {
        return tabuleiro[0][0]; // Vencedor na diagonal principal
    }
    if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0] && tabuleiro[0][2] != ' ') {
        return tabuleiro[0][2]; // Vencedor na diagonal secundária
    }

    return ' '; // Nenhum vencedor ainda
}

// Função para verificar se o tabuleiro está cheio (empate)
int tabuleiroCheio(char** tabuleiro, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (tabuleiro[i][j] == ' ') {
                return 0; // Ainda há espaço vazio
            }
        }
    }
    return 1; // Tabuleiro cheio (empate)
}

// Função para criar um tabuleiro dinâmico
char** criaTabuleiro(int tamanho) {
    char** tabuleiro = (char**)malloc(tamanho * sizeof(char*));
    for (int i = 0; i < tamanho; i++) {
        tabuleiro[i] = (char*)malloc(tamanho * sizeof(char));
        for (int j = 0; j < tamanho; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
    return tabuleiro;
}

// Função para liberar a memória do tabuleiro dinâmico
void liberaTabuleiro(char** tabuleiro, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        free(tabuleiro[i]);
    }
    free(tabuleiro);
}

// Função para exibir o menu
void exibeMenu() {
    printf("Bem-vindo ao Jogo da velha, por favor selecione uma opção:\n");
    printf("1. Jogar\n");
    printf("2. Créditos\n");
    printf("3. Finalizar Operação\n\n");
}

//Função para reiniciar o jogo
void reiniciaJogo(char*** tabuleiro, int tamanho) {
    liberaTabuleiro(*tabuleiro, tamanho); // Libera a memória do tabuleiro atual
    *tabuleiro = criaTabuleiro(tamanho); // Cria um novo tabuleiro
}

int main() {
    int tamanho = 3;
    char** tabuleiro = criaTabuleiro(tamanho);
    int linha, coluna;
    char jogador = 'X';
    int escolha;

	setlocale(LC_ALL, "Portuguese_Brazil.1252");

    do {
        exibeMenu();
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                // Loop do jogo da velha
                do {
                    imprimeTabuleiro(tabuleiro, tamanho);

                    // Solicita a jogada do jogador atual
                    printf("Jogador %c, insira a linha e a coluna (1-3) separadas por espaço: ", jogador);
                    scanf("%d %d", &linha, &coluna);

                    // Convertendo de 1 a 3 para 0 a 2
                    linha--;
                    coluna--;

                    // Verifica se a jogada é válida
                    if (linha < 0 || linha >= tamanho || coluna < 0 || coluna >= tamanho || tabuleiro[linha][coluna] != ' ') {
                        printf("Jogada inválida. Tente novamente.\n");
                        continue;
                    }

                    // Atualiza o tabuleiro com a jogada
                    tabuleiro[linha][coluna] = jogador;

                    // Verifica se há um vencedor
                    char vencedor = verificaVencedor(tabuleiro, tamanho);
                    if (vencedor != ' ') {
                        imprimeTabuleiro(tabuleiro, tamanho);
                        printf("Jogador %c venceu!\n\n", vencedor);
                        reiniciaJogo(&tabuleiro, tamanho); // Reinicia o jogo
                        break;
                    }

                    // Verifica se o tabuleiro está cheio (empate)
                    if (tabuleiroCheio(tabuleiro, tamanho)) {
                        imprimeTabuleiro(tabuleiro, tamanho);
                        printf("Empate! O jogo terminou sem vencedor.\n");
                        reiniciaJogo(&tabuleiro, tamanho); // Reinicia o jogo
                        break;
                    }

                    // Alterna para o próximo jogador
                    jogador = (jogador == 'X') ? 'O' : 'X';

                } while (1); // Loop do jogo
                break;
            case 2:
                printf("Créditos:\n");
                printf("Desenvolvido por: \n-Gabriel de andrade \n-Julio Oliveira \n-Dyego Almeida \n-Juan Domingos \n\n");
                break;
            case 3:
                printf("Operação finalizada. Muito obrigado!\n");
                liberaTabuleiro(tabuleiro, tamanho);
                return 0; // Sair do programa
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (1); // Loop do menu

    return 0;
}
