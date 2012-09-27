#include <stdio.h>
#include <string.h>
#include "sudoku.h"
/*******************************************************************************
Pedro Emílio Machado de Brito - RA 137264
25/09/2012 - MC202 turma B

lab04 - Sudoku

principal.c

Resolve um tabuleiro de sudoku, caso exista solução.
*******************************************************************************/


/*Funcao que imprime a matriz 9x9 que armazena o jogo de Sudoku (opcionalmente a matriz pode ser global e nao passada por parametro)*/
void imprime(int mat[9][9]){
	int i, j;
	for(i=0; i<9; i++){
		if(i%3 == 0)
			printf("--------------------------\n");
		for(j=0; j<9; j++){
			if(j%3 == 0)
				printf(" |");
			printf(" %d", mat[i][j]);
		}
		printf(" |\n");
	}
	printf("--------------------------\n");
	return;
}


int sudoku(int mat[9][9])
{
  int x,y, v, casas;
  /* loop de inicialização */
  for (scanf (" %d", &casas); casas > 0; casas--)
    {
      scanf(" %d %d %d", &x, &y, &v);
      mat[x-1][y-1] = v;
    }
  /* chamada inicia a recursão */
  return solveSudoku(mat);
}

int main()
{
  /* matriz que guarda o tabuleiro */
  int tabuleiro[9][9] = {{0}};
  if (sudoku(tabuleiro))
    imprime(tabuleiro);
  else
    printf("Sem solucao\n");
  return 0;
}

