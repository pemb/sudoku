#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sudoku.h"
#include "strategies.h"


int solveSudoku (int grid[9][9] )
{
  int *** pMatrix = newPMatrix(NULL), i, j, k, retVal;
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

int sudokuWorker(int *** pMatrix)
{
  int * temp, k = 0, i, j, l;  
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
  i = getLowest(pMatrix);
  j = i%10;
  i /= 10;
  k = 1;
  temp = malloc(9*9*10*sizeof(int));
  memcpy(temp, **pMatrix, 9*9*10*sizeof(int));
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
      memcpy(**pMatrix, temp, 9*9*10*sizeof(int));
    }
  free(temp);
  return k == 11; 
}

int checkState(int *** pMatrix)
{
  int i, j, flag = 1;
  for (i = 0; i < 9; i++)
    {
      for (j = 0; j < 9; j++)
	{
	  switch (pMatrix[i][j][0])
	    {
	    case 0:
	      return -1;
	    case 1:
	      break;
	    default:
	      flag = 0;
	    }
	}
    }
  return flag;  
}

int getLowest(int *** pMatrix)
{
  int i, j, count = 9, retVal = 0;
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

int *** newPMatrix(int *** original)
{
  int *** pMatrix =  malloc (9*sizeof (int**)), i, j;
  *pMatrix = malloc (9*9*sizeof(int*));
  **pMatrix = calloc (9*9*10,sizeof(int));
  if (original != NULL)
    memcpy( **pMatrix, **original, 9*9*10*sizeof(int));
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

void freePMatrix(int *** pMatrix)
{
  free(**pMatrix);
  free(*pMatrix);
  free(pMatrix);
}

