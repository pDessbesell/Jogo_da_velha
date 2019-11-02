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
int pode_jogar(int tab[], int coluna, int linha);
void versus_computador(FILE *f);
void versus_jogador(FILE *f);
void configura_tabela(int tab[], int n);

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
void transfere_dados(FILE *g, FILE *f);

void gen_random(char *, const int);


/* -----------------------------------------------------------------------------
 * -----------------------------------------------------------------------------
 * MAIN
 * /////////////////////////////////////////////////////////////////////////////
 */
int main(int argc, char **argv) {
    int tab[9];

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

	printf("\n   (1) (2) (3)\n\n");

	for (i = 0; i < 3; i++) {
        printf("(%d)", i+1);
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
				printf("\n\n");
		}
	}
	printf("\n");
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
				printf("É preciso primeiramente carregar um arquivo!");
			}
			else {
				exibir_resultado(f);
			}
			break;

		case 3:
			if (f == NULL) {
						printf("É preciso primeiramente carregar um arquivo!");
			}
			else {
				exibir_duracao(f);
			}
			break;

		case 4:
			if (f == NULL) {
						printf("É preciso primeiramente carregar um arquivo!");
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
		break;

	case 2:
		versus_computador(f);
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
		    printf("\nFinalizando...!");
			printf("\nPrograma finalizado!");
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
	int i, j = 0;

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
		return tab[2];
	}
	else{
        j = 0;
        for (i = 0; i < 9; i++){
            if (tab[i] != 1 && tab[i] != 2){
                j++;
            }
        }
	}
	if(j==0){
        return 3; //empate, deu velha
        }

	return -1; //nao acabou
}
/* ----------------------------------------------------------------------------
 * PODE JOGAR
 * Verifica se sera possivel realizar determinada jogada
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

int pode_jogar(int tab[], int coluna, int linha){
    int i;

    if(linha == 1){
        if (tab[coluna - 1 + 0] == 0 || tab[coluna - 1 + 0] == 1)
            return 0;

    }else if(linha == 2){
        if (tab[coluna - 1 + 3] == 0 || tab[coluna - 1 + 3] == 1)
            return 0;

    }else if(linha == 3){
        if (tab[coluna - 1 + 6] == 0 || tab[coluna - 1 + 6] == 1)
            return 0;
    }
    return 1;
}


/* -----------------------------------------------------------------------------
 * VERSUS COMPUTADOR
 * Jogar Versus Computador
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void versus_computador(FILE *f) {
    FILE *temp; //Arquivo temporario para salvar somente as jogadas
	int tab[9], verifica, coluna, linha, cpu, vez = 1, njogadas = 0, i;
	configura_tabela(tab, 9);
	time_t t;

	f = fopen("jogo.dat", "w");
	if (f == NULL)
        return;
	temp = fopen("jogadas.dat", "w");
	if (temp == NULL)
        return;


    do{
        system("cls");
        imprimir_tabuleiro(tab);

        if(vez == 1){
            do{
                do{
                    printf("Entre com a COLUNA: ");
                    scanf("%d", &coluna);
                }while(coluna > 3 || coluna <= 0);

                do{
                    printf("Entre com a LINHA: ");
                    scanf("%d", &linha);
                }while(linha > 3 || linha <= 0);
                pode_jogar(tab, coluna, linha);
            }while (!pode_jogar(tab, coluna, linha));


            if(linha == 1){
                tab[coluna - 1 + 0] = 1;

            }else if(linha == 2){
                tab[coluna - 1 + 3] = 1;

            }else if(linha == 3){
                tab[coluna - 1 + 6] = 1;
            }
        }
        if(vez == -1)
        {
            srand((unsigned)time(NULL));
            do{
                cpu = ((rand()) % 9);
            }while (tab[cpu] == 0 || tab[cpu] == 1);

            tab[cpu] = 0;
        }
        vez *= -1;

        fwrite(tab, sizeof(tab), 1, temp);
        verifica = terminou_jogo(tab);
        njogadas++;
    }while(verifica == -1);

    system("cls");
    imprimir_tabuleiro(tab);

    if(verifica == 1)
        printf("\n *** X venceu ***\n\n");
    if(verifica == 0)
        printf("\n *** O venceu ***\n\n");
    if(verifica != 0 && verifica != 1)
        printf("\n * Deu velha *\n\n");

    //Abrindo o arquivo temporario para modo de leitura
    fclose(temp);
    temp = fopen("jogadas.dat", "r");

    //Escrevendo o vencedor e o numero de jogadas para o arquivo principal
    salvar_resultado(f, verifica);
    salvar_duracao(f, njogadas);

    //Copiando os dados do arquivo temporario para o arquivo principal
    transfere_dados(temp, f);

    fclose(f);
    fclose(temp);
}

/* -----------------------------------------------------------------------------
 * VERSUS JOGADOR
 * Jogar Versus Jogador
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void versus_jogador(FILE *f) {
    FILE *temp;
    int tab[9], verifica, coluna, linha, vez = 1, nJogadas = 0;
    configura_tabela(tab, 9);

    f = fopen("jogo.dat", "w");
	if (f == NULL)
        return;
	temp = fopen("jogadas.dat", "w");
	if (temp == NULL)
        return;

    do{
        system("cls");
        imprimir_tabuleiro(tab);

        do{
            do{
                printf("Entre com a COLUNA: ");
                scanf("%d", &coluna);
            }while(coluna > 3 || coluna <= 0);

            do{
                printf("Entre com a LINHA: ");
                scanf("%d", &linha);
            }while(linha > 3 || linha <= 0);
            pode_jogar(tab, coluna, linha);
        }while (!pode_jogar(tab, coluna, linha));

        if(linha == 1){
            if(vez == 1){
                tab[coluna - 1] = 1;
            }else
                tab[coluna - 1] = 0;
            vez *= -1;

        }else if(linha == 2){
            if(vez == 1){
                tab[coluna - 1 + 3] = 1;
            }else
                tab[coluna - 1 + 3] = 0;
            vez *= -1;

        } else if(linha == 3){
            if(vez == 1){
                tab[coluna - 1 + 6] = 1;
            }else
                tab[coluna - 1 + 6] = 0;
            vez *= -1;

        }
            fwrite(tab, sizeof(tab), 1, temp);
            verifica = terminou_jogo(tab);
            nJogadas++;
    }while(verifica == -1);

    system("cls");
    imprimir_tabuleiro(tab);

    if(verifica == 1)
        printf("\n *** X venceu ***\n\n");
    if(verifica == 0)
        printf("\n *** O venceu ***\n\n");
    if(verifica != 0 && verifica != 1)
        printf("\n * Deu velha *\n\n");

    //Abrindo o arquivo temporario para modo de leitura
    fclose(temp);
    temp = fopen("jogadas.dat", "r");

    //Escrevendo o vencedor e o numero de jogadas para o arquivo principal
    salvar_resultado(f, verifica);
    salvar_duracao(f, nJogadas);

    //Copiando os dados do arquivo temporario para o arquivo principal
    transfere_dados(temp, f);

    fclose(f);
    fclose(temp);
}

// -----------------------------------------------------------------------------

/* -----------------------------------------------------------------------------
 * CARREGAR ARQUIVO
 * Abre o arquivo com o nome fornecido como parametro
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
FILE *carregar(char *filename) {
	FILE *f;
	f = fopen(filename, "r");
}

/* -----------------------------------------------------------------------------
 * EXIBIR DURACAO
 * Le do arquivo e exibe a duracao (numero de jogadas)
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void exibir_duracao(FILE* f) {
	int dur;
	fseek(f, 1 * sizeof(int), SEEK_SET);
    fread(&dur, sizeof(int), 1, f);
    printf("Total de %d jogadas\n", dur);
}

/* -----------------------------------------------------------------------------
 * EXIBIR JOGADA
 * Le do arquivo e exibe na tela o estado do tabuleiro na jogada n fornecida
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void exibir_jogada(FILE* f, int n) {
	int tab[9], i;

    fseek(f, 2*sizeof(int), SEEK_SET);
    fseek(f, (n-1) * sizeof(tab), SEEK_CUR);

    //for(i = 0; i < 9; i++){
        fread(tab, sizeof(int), 9, f);
    //}

    imprimir_tabuleiro(tab);
}

/* -----------------------------------------------------------------------------
 * EXIBIR RESULTADO
 * Le do arquivo e exibe o resultado da partida
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void exibir_resultado(FILE* f) {
	int res;
	fread(&res, sizeof(int), 1, f);
	if(res == 1)
        printf("\n *** X venceu ***\n\n");
    if(res == 0)
        printf("\n *** O venceu ***\n\n");
    if(res != 0 && res != 1)
        printf("\n * Deu velha *\n\n");
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
 * Salva a duração (numero de jogadas) da partida no arquivo
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void salvar_duracao (FILE *f, int dur) {
	fwrite(&dur, sizeof(int), 1, f);
}

/* -----------------------------------------------------------------------------
 * SALVAR JOGADA
 * Salva a jogada (estado do tabuleiro) no arquivo
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void salvar_jogada (FILE *f, int tab[]) {
	fwrite(tab, sizeof(tab), 1, f);
}

/* -----------------------------------------------------------------------------
 * SALVAR RESULTADO
 * Salva o resultado do jogo no arquivo
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void salvar_resultado (FILE *f, int res) {
	fwrite(&res, sizeof(int), 1, f);
}

/* -----------------------------------------------------------------------------
 * GEN RANDOM
 * Gera uma string aleatoria com o tamanho len passado como parametro
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void transfere_dados(FILE *g, FILE *f){
    char c;
    c = fgetc(g);
    while (c != EOF)
    {
        fputc(c, f);
        c = fgetc(g);
    }
 }

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
void configura_tabela(int tab[], int n){ //Apenas para garantir que o tabuleiro nao inicie com valores iguais
    int i;
    for(i = 0; i < n; i++){
        tab[i] = i + 65;
    }
}
