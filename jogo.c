#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

/*
 * Prototipos
 */
void imprimir_tabuleiro(int []);
void menu_carregar_arquivo();
void menu_jogar();
void menu_principal();
int ler_opcao();
int terminou_jogo(int []);
void versus_computador(FILE* f);
void versus_jogador(FILE*);

/*
 * Prototipos manipulacao de arquivos
 */
void exibir_resultado(FILE* f);
void exibir_duracao(FILE* f);
void exibir_jogada(FILE* f, int n);
FILE* carregar (char *);
FILE* inicializar_arquivo();
void salvar_resultado (FILE*, int);
void salvar_duracao (FILE*, int);
void salvar_jogada (FILE*, int[]);

void gen_random(char *, const int);

/* -----------------------------------------------------------------------------
 * -----------------------------------------------------------------------------
 * MAIN
 * /////////////////////////////////////////////////////////////////////////////
 */
int main(int argc, char **argv) {

	menu_principal();

	return 0;
}

/* -----------------------------------------------------------------------------
 * LER
 * Ler opcao
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int ler_opcao () {
	int op;

	printf("Opcao: ");
	scanf(" %d", &op);

	return op;
}

/* -----------------------------------------------------------------------------
 * IMPRIMIR_TABULEIRO
 * Recebe uma matriz e imprime o tabuleiro.
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void imprimir_tabuleiro(int tab[]) {
	int i, j;

	for (i = 0; i < 3; i++) {

		for (j = 0; j < 3; j++) {
			int k = j + 3*i;

			if (tab[k] == 0)
				printf(" O ");
			else if (tab[k] == 1)
				printf(" X ");
			else
				printf("   ");

			if (j != 2)
				printf("|");
			else
				printf("\n");
		}
	}
}

/* -----------------------------------------------------------------------------
 * MENU CARREGAR ARQUIVO
 * Imprime o menu para carregar do arquivo
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void menu_carregar_arquivo() {
	FILE *f;
	int opcao, n;
	char filename[15];

	f = NULL;

	do {
		printf("~~~~~~~~~~~~~ CARREGAR ARQUIVO ~~~~~~~~~~~~~~~~~\n"
					"[1] - Carregar Arquivo\n"
					"[2] - Exibir resultado\n"
					"[3] - Exibir numero de jogadas\n"
					"[4] - Exibir jogada\n"
					"[5] - Retornar ao menu anterior\n"
					"---------\n");
		opcao = ler_opcao();

		switch(opcao) {

		case 1:
			printf("Entre com o nome do arquivo: ");
			scanf("%s", filename);

			f = carregar(filename);
			break;

		case 2:
			if (f == NULL) {
				printf("� preciso primeiramente carregar um arquivo!");
			}
			else {
				exibir_resultado(f);
			}
			break;

		case 3:
			if (f == NULL) {
						printf("� preciso primeiramente carregar um arquivo!");
			}
			else {
				exibir_duracao(f);
			}
			break;

		case 4:
			if (f == NULL) {
						printf("� preciso primeiramente carregar um arquivo!");
			}
			else {
				printf("Entre com a jogada a ser exibida: ");
				scanf("%d", &n);

				exibir_jogada(f, n);
			}
			break;

		case 5:
			return;
			break;
		}
	} while (opcao != 5);
}

/* -----------------------------------------------------------------------------
 * MENU JOGAR
 * Imprime o menu para jogar
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void menu_jogar() {
	int opcao;
	FILE *f;

	printf("~~~~~~~~~~~~~ JOGAR ~~~~~~~~~~~~~~~~~\n"
				"[1] - Versus outro jogador\n"
			    "[2] - Versus computador\n"
			    "[3] - Retornar ao menu anterior\n"
			    "---------\n");
	opcao = ler_opcao();

	switch(opcao) {
	case 1:
		f = inicializar_arquivo();
		versus_jogador(f);
		fclose(f);
		break;

	case 2:
		versus_computador();
		break;

	case 3:
		return;
		break;
	}
}

/* -----------------------------------------------------------------------------
 * MENU PRINCIPAL
 * Imprime o menu principal
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void menu_principal() {
	int opcao;

	do {
		printf("~~~~~~~~~~~~~ JOGO DA VELHA ~~~~~~~~~~~~~~~~~\n"
						"[1] - Jogar\n"
						"[2] - Carregar de um arquivo\n"
						"[9] - Sair\n"
						"---------\n");
		opcao = ler_opcao();

		switch(opcao) {
		case 1:
			menu_jogar();
			break;

		case 2:
			menu_carregar_arquivo();
			break;

		case 9:
			printf("Programa finalizado!");
			return;
			break;
		}
	} while (opcao != 9);
}

/* -----------------------------------------------------------------------------
 * TERMINOU JOGO
 * Verifica se o jogo terminou
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int terminou_jogo(int tab[]) {
	int i;

	// verificando linhas
	for (i = 0; i < 3; i++) {
		if (tab[i*3] == tab[i*3 + 1] && tab[i*3 + 1] == tab[i*3 + 2]) {
			return tab[i*3];
		}
	}

	// verificando colunas
	for (i = 0; i < 3; i++) {
		if (tab[i] == tab[i+3] && tab[i+3] == tab[i+6]) {
				return tab[i];
		}
	}

	// verificando diagonal
	if (tab[0] == tab[4] && tab[4] == tab[8]) {
		return tab[0];
	}

	// verificando diagonal
	if (tab[2] == tab[4] && tab[4] == tab[6]) {
		return tab[0];
	}

	return -1;
}

/* -----------------------------------------------------------------------------
 * VERSUS COMPUTADOR
 * Jogar Versus Computador
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void versus_computador(FILE* f) {
	// TODO
}

/* -----------------------------------------------------------------------------
 * VERSUS JOGADOR
 * Jogar Versus Jogador
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void versus_jogador(FILE* f) {
	// TODO
}

// -----------------------------------------------------------------------------

/* -----------------------------------------------------------------------------
 * CARREGAR ARQUIVO
 * Abre o arquivo com o nome fornecido como parametro
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
FILE *carregar(char *filename) {
	// TODO
}

/* -----------------------------------------------------------------------------
 * EXIBIR DURACAO
 * Le do arquivo e exibe a duracao (numero de jogadas)
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void exibir_duracao(FILE* f) {
	// TODO
}

/* -----------------------------------------------------------------------------
 * EXIBIR JOGADA
 * Le do arquivo e exibe na tela o estado do tabuleiro na jogada n fornecida
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void exibir_jogada(FILE* f, int n) {
	// TODO
}

/* -----------------------------------------------------------------------------
 * EXIBIR RESULTADO
 * Le do arquivo e exibe o resultado da partida
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void exibir_resultado(FILE* f) {
	// TODO
}

/* -----------------------------------------------------------------------------
 * INICIALIZAR ARQUIVO
 * Abre o arquivo e inicializa o arquivo com valores padroes
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
FILE* inicializar_arquivo() {
	// TODO
}

/* -----------------------------------------------------------------------------
 * SALVAR DURACAO
 * Salva a dura��o (numero de jogadas) da partida no arquivo
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void salvar_duracao (FILE *f, int dur) {
	// TODO
}

/* -----------------------------------------------------------------------------
 * SALVAR JOGADA
 * Salva a jogada (estado do tabuleiro) no arquivo
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void salvar_jogada (FILE *f, int tab[]) {
	// TODO
}

/* -----------------------------------------------------------------------------
 * SALVAR RESULTADO
 * Salva o resultado do jogo no arquivo
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void salvar_resultado (FILE *f, int res) {
	// TODO
}

/* -----------------------------------------------------------------------------
 * GEN RANDOM
 * Gera uma string aleatoria com o tamanho len passado como parametro
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void gen_random(char *s, const int len) {
	srand(time(NULL));
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}