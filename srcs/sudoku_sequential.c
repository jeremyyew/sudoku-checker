#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <sudoku_internal.h>

int check_sudoku(int *S)
{
    return checkEveryRowColGridInRange(S, 0, DIM);
};
