#include <stdlib.h>
#include <stdio.h>
#include <sudoku.h>

int checkEverySectionParallelized(int *S, int (*getNthSectionKthIndex)(int, int), int start, int end)
{
    int sum;
#pragma omp parallel for
    for (int n = start; n < end; n++)
    {
        sum = 0;
        for (int k = 0; k < 9; k++)
        {
            sum += S[getNthSectionKthIndex(n, k)];
        }
        if (sum != 45)
        {
            printf("Failed at %dth ", n + 1);
            return 0;
        }
    }
    return 1;
};

int checkEveryGridParallelized(int *S, int start, int end)
{
    return checkEverySectionParallelized(S, getNthGridKthIndex, start, end);
};

int checkEveryColParallelized(int *S, int start, int end)
{
    return checkEverySectionParallelized(S, getNthColKthIndex, start, end);
};

int checkEveryRowParallelized(int *S, int start, int end)
{
    return checkEverySectionParallelized(S, getNthRowKthIndex, start, end);
};

int checkEveryRowColGridInRangeParallelized(int *S, int start, int end)
{
    printf("checking row %d to %d\n", start, end - 1);
    int rowsAreValid = checkEveryRowParallelized(S, start, end);
    if (!rowsAreValid)
    {
        printf("row.\n");
    }
    printf("checking col to %d to %d\n", start, end - 1);
    int colsAreValid = checkEveryColParallelized(S, start, end);
    if (!colsAreValid)
    {
        printf("column.\n");
    }
    printf("checking grid to %d to %d\n", start, end - 1);
    int gridsAreValid = checkEveryGridParallelized(S, start, end);
    if (!gridsAreValid)
    {
        printf("grid.\n");
    }
    if (!rowsAreValid || !colsAreValid || !gridsAreValid)
    {
        return 0;
    }
    return 1;
}

int checkSudokuOpenMP(int *S)
{
    return checkEveryRowColGridInRangeParallelized(S, 0, DIM);
};
