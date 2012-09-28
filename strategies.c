#include <string.h>
#include <stdio.h>
#include "strategies.h"

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

int onlypossible(matrix pMatrix)
{
  cell i, j, k, l, map[3][10], count = 0;
  /* return 0;   */
  for (i = 0; i < 9; i++)
    {
      memset(map, 0, sizeof(cell)*30);
      for (j = 0; j < 9; j++)
	{
	  for (k = 1; k < 10; k++)
	    {
	      map[0][k] += pMatrix[i][j][k];
	      map[1][k] += pMatrix[j][i][k];
	      map[2][k] += pMatrix[i/3*3+j/3][i%3*3+j%3][k];
	    }
	}
      for (k = 1; k < 10; k++)
	{
	  if (map[0][k] == 1)
	    {
	      for (j = 0; j < 9; j++)
		{
		  if (pMatrix[i][j][0] > 1 && pMatrix[i][j][0] < 10 && pMatrix[i][j][k])
		    {
		      count++;
		      pMatrix[i][j][0] = 1;
		      for (l = 1; l < 10; l++)
			pMatrix[i][j][l] = (l == k);
		    }
		  break;
		}
	    }
	  if (map[1][k] == 1)
	    {
	      for (j = 0; j < 9; j++)
		{
		  if (pMatrix[j][i][0] > 1 && pMatrix[j][i][0] < 10 && pMatrix[j][i][k])
		    {
		      count++;
		      pMatrix[j][i][0] = 1;
		      for (l = 1; l < 10; l++)
			pMatrix[j][i][l] = (l == k);
		    }
		  break;
		}
	    }
	  if (map[2][k] == 1)
	    {
	      for (j = 0; j < 9; j++)
		{
		  if (pMatrix[i/3*3+j/3][i%3*3+j%3][0] > 1 && pMatrix[i/3*3+j/3][i%3*3+j%3][0] < 10 && pMatrix[i/3*3+j/3][i%3*3+j%3][k])
		    {
		      
		      count++;
		      pMatrix[i/3*3+j/3][i%3*3+j%3][0] = 1;
		      for (l = 1; l < 10; l++)
			pMatrix[i/3*3+j/3][i%3*3+j%3][l] = (l == k);
		    }
		  break;
		}
	    }
	}
    }
   /* if (count)  */
   /*   printf("AEAE\n"); */
  return count;
}
