#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int cell;

typedef cell *** matrix;

int singles(matrix);

int solveSudoku(int [9][9]);

matrix newPMatrix(matrix);

int sudokuWorker(matrix);

void freePMatrix(matrix);

int checkState(matrix);

int getLowest(matrix);

int (* strategies[])(matrix) = {singles};

int functions = 1;

int solveSudoku (int grid[9][9] )
{
  matrix pMatrix = newPMatrix(NULL);
  cell i, j, k;
  int retVal;
  for (i = 0; i < 9; i++)
    {
      for (j = 0; j < 9; j++)
	{
	  if (grid[i][j])
	    pMatrix[i][j][0] = pMatrix[i][j][grid[i][j]] = 1;
	  else
	    {
	      pMatrix[i][j][0] = 9;
	      for (k = 1; k < 10; k++)
		pMatrix[i][j][k] = 1;
	    }
	}
    }
  if ((retVal = sudokuWorker(pMatrix)))
    {
      for (i = 0; i < 9; i++)
	{
	  for (j = 0; j < 9; j++)
	    {
	      k = 1;
	      if(pMatrix[i][j][0]%10 )
		while (!grid[i][j])
		{
		  grid[i][j] = k * pMatrix[i][j][k];
		  k++;
		}
	    }
	}
    }
  freePMatrix(pMatrix);
  return retVal;
}

int sudokuWorker(matrix pMatrix)
{
  cell * temp, k = 0, i, j, l;
  while (k < functions)
    {
      if (strategies[k](pMatrix))
	k = 0;
      else
	k++;
    }
  switch (checkState(pMatrix))
    {
    case -1:
      return 0;
    case 1:
      return 1;      
    case 0:
      break;
    }
  /* return 1; */
  i = getLowest(pMatrix);
  j = i%10;
  i /= 10;
  k = 1;
  temp = malloc(9*9*10*sizeof(cell));
  memcpy(temp, **pMatrix, 9*9*10*sizeof(cell));
  for (k = 1; k < 10; k++)
    {
      if (!pMatrix[i][j][k])
	  continue;
      pMatrix[i][j][0] = 1;
      for (l = 1; l < 10; l++)
	pMatrix[i][j][l] = (l == k);
      if (sudokuWorker(pMatrix))
	{
	  k = 11;	  
	  break;
	}
      memcpy(**pMatrix, temp, 9*9*10*sizeof(cell));
    }
  free(temp);
  return k == 11; 
}

int checkState(matrix pMatrix)
{
  cell i, j;
  int flag = 1;
  for (i = 0; i < 9; i++)
    {
      for (j = 0; j < 9; j++)
	{
	  switch (pMatrix[i][j][0])
	    {
	    case 0:
	      return -1;
	    case 1:
	    case 11:
	      break;
	    default:
	      flag = 0;
	    }
	}
    }
  return flag;  
}

int getLowest(matrix pMatrix)
{
  cell i, j, count = 9;
  int retVal = 0;
  for (i = 0; i < 9; i++)
    {
      for (j = 0; j < 9; j++)
	{
	  if (pMatrix[i][j][0] > 1 && pMatrix[i][j][0] < count)
	    {	      
	      count = pMatrix[i][j][0];
	      retVal = 10*i + j;
	    }
	}
    }
  return retVal;
}

matrix newPMatrix(matrix original)
{
  matrix pMatrix = malloc (9*sizeof (cell**));
  cell i, j;
  *pMatrix = malloc (9*9*sizeof(cell*));
  **pMatrix = calloc (9*9*10,sizeof(cell));
  if (original != NULL)
    memcpy( **pMatrix, **original, 9*9*10*sizeof(cell));
  for (i = 0; i < 9; i++)
    {
      if (i)
	{
	  pMatrix[i] = pMatrix[i-1]+9;
	  pMatrix[i][0] = pMatrix[i-1][8]+10;
	}
      for (j = 1; j < 9; j++)
	{
	  pMatrix[i][j] = pMatrix[i][j-1] + 10;
	}
    }
  return pMatrix;  
}

void freePMatrix(matrix pMatrix)
{
  free(**pMatrix);
  free(*pMatrix);
  free(pMatrix);
}

int singles(matrix pMatrix)
{
  cell i, j, k, digit = 0, count = 0;
  for (i = 0; i < 9; i++)
    {
      for (j = 0; j < 9; j++)
	{
	  /* tests square for single prob */
	  if (pMatrix[i][j][0] == 1)
	    {
	      pMatrix[i][j][0] = 11; 
	      for (digit = 1; digit < 10; digit++)
		{
		  if (pMatrix[i][j][digit])
		    break;
		}
	      if (digit == 10)
		continue;
	      for (k = 0; k < 9; k++)
		{
		  if (pMatrix[i][k][digit] && k != j)
		    {
		      pMatrix[i][k][digit] = 0;
		      pMatrix[i][k][0]--;
		      count++;		      
		    }
		  if (pMatrix[k][j][digit] && k != i)
		    {
		      pMatrix[k][j][digit] = 0;
		      pMatrix[k][j][0]--;
		      count++;		      
		    }
		  if (pMatrix[i/3*3+k/3][j/3*3+k%3][digit] && (i/3*3+k/3 != i || j/3*3+k%3 != j))
		    {
		      pMatrix[i/3*3+k/3][j/3*3+k%3][digit] = 0;
		      pMatrix[i/3*3+k/3][j/3*3+k%3][0]--;
		      count++;		      
		    }
		}
	    }
	  /* ends testing loop */
	}
    }
  return count;
}


/*Funcao que imprime a matriz 9x9 que armazena o jogo de Sudoku (opcionalmente a matriz pode ser global e nao passada por parametro)*/
void imprime(int mat[9][9]){
  int i, j;
  for(i=0; i<9; i++)
    {
      for(j=0; j<9; j++)
	  printf("%d", mat[i][j]);
      putchar('\n');
    }
  return;
}

int main()
{
  int mat[9][9], x, y, v, casos;
  for (scanf ("%d", &casos); casos > 0; casos--)
    {
      for (x = 0; x < 9; x++)
	for (y = 0; y < 9; y++)
	  {
	    scanf(" %1d",&v);
	    mat[x][y] = v;
	  }
      solveSudoku(mat);
      imprime(mat);
    }
  return 0;
}

