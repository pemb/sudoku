
int singles(int *** pMatrix)
{
  int i, j, k, digit = 0, count = 0;
  for (i = 0; i < 9; i++)
    {
      for (j = 0; j < 9; j++)
	{
	  /* tests square for single prob */
	  if (pMatrix[i][j][0] == 1)
	    {
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
