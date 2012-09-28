#ifndef SUDOKU_H
#define SUDOKU_H

#include "typedefs.h"
int solveSudoku(int [9][9]);

matrix newPMatrix(matrix);

int sudokuWorker(matrix);

void freePMatrix(matrix);

int checkState(matrix);

int getLowest(matrix);
#endif
