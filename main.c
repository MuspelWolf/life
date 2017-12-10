/*
 *	Game of Life - 2017
 *	Eduardo Alonso Peleato <bo0404>
 */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define N 10 // Dimensiones del tablero NxN

void asignar_array(int dst[][N], int src[][N])
{
	int i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			dst[i][j] = src[i][j];
}

void inicio(int *c_vivas, int *estados, int tab[][N])
{
	int i, j;
	char azar;

	printf("\n\t|~~~Game of Life~~~|\n\n");
	printf("\nQuiere realizar una ejecucion al azar? [s|n]: ");
	scanf("%c", &azar);

	if (azar == 's') {
		srand(time(NULL));
		for (i = 0; i < N; i++)
			for (j = 0; j < N; j++)
			tab[i][j] = (rand() % 2);
	} else {
		printf("Introduzca el numero de celulas vivas inicialmente :");
		scanf("%d", c_vivas);
		
		for (i = 0; i < *c_vivas; i++) {
			int x, y;
			printf("\nIntroduzca la posicion de la celula %d [fila,columna]: ", i);
			scanf("%d,%d", &x, &y);
			tab[x][y] = 1;
		}
	}
	printf("\nIntroduzca la cantidad de estados que desea mostrar: ");
	scanf("%d", estados);
}

int vecinas(int tab[][N], int i, int j)
{
	int ii, ij, in_i, in_j, lim_i, lim_j, n = 0;

	in_i = i ? i - 1 : i;

	lim_i = (i == N - 1) ? i : i + 1;

	in_j = j ? j - 1 : j;

	lim_j = j == N - 1 ? j : j + 1;

	for (ii = in_i; ii <= lim_i; ii++)
		for (ij = in_j; ij <= lim_j; ij++)
			if (ii == i && ij == j)
				continue;
			else
				if (tab[ii][ij])
					n++;
	return n;
}

void juego(int tab[][N], int prox[][N])
{
	int i, j, viva, c_vecinas;
	asignar_array(prox, tab);
//	prox = tab;

	/* Para todas las celulas */
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++) {
		viva = tab[i][j];
		c_vecinas = vecinas(tab, i, j);

		/* Nac */
		if (!viva && c_vecinas == 3) {
			viva = 1;
		}

		/* Sup */
		if (viva)
			if (c_vecinas != 2 && c_vecinas != 3)
				viva = 0;

		/* Super pobl */
		if (c_vecinas == 4)
			viva = 0;

		prox[i][j] = viva;
	}
}

void mostrar_tablero(int tab[][N])
{
	int i, j;

	for (i = 0; i < N; i++) {
		printf("|");
		for (j = 0; j < N; j++) {
			if (tab[i][j])
				printf("*");
			else
				printf(" ");
		}
		printf("|\n");
	}
	printf("\n~~~\n");
}

int main()
{
	int c_vivas, estados, i;
	int tab[N][N] = {};
	int prox[N][N] = {};
	inicio(&c_vivas, &estados, tab);

	for (i = 0; i < estados; i++) {
		mostrar_tablero(tab);

		usleep(500000);

		juego(tab, prox);
		asignar_array(tab, prox);
	}
	return 0;
}

