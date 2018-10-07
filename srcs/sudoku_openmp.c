#include <stdlib.h>
#include <stdio.h>
#include <sudoku_internal.h>

int checkEverySectionParallelized(int *S, int (*getNthSectionKthIndex)(int, int), int start, int end)
{
    int flag = 1;
#pragma omp parallel for
    for (int n = start; n < end; n++)
    {
        int flags[9] = {0};
        for (int k = 0; k < 9; k++)
        {
            int val = S[getNthSectionKthIndex(n, k)];
            if (val >= 1 && val <= 9) //we already validate inputs, but just to make sure no seg fault
            {
                flags[val - 1] += 1;
            }
        }
        if (exactlyOneEach(flags) == 0)
        {
            // printf("Failed at %dth ", n + 1);
            flag = 0;
        }
    }
    return flag;
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
    // printf("checking row %d to %d\n", start, end - 1);
    int rowsAreValid = checkEveryRowParallelized(S, start, end);
    if (!rowsAreValid)
    {
        // printf("row.\n");
    }
    // printf("checking col to %d to %d\n", start, end - 1);
    int colsAreValid = checkEveryColParallelized(S, start, end);
    if (!colsAreValid)
    {
        // printf("column.\n");
    }
    // printf("checking grid to %d to %d\n", start, end - 1);
    int gridsAreValid = checkEveryGridParallelized(S, start, end);
    if (!gridsAreValid)
    {
        // printf("grid.\n");
    }
    if (!rowsAreValid || !colsAreValid || !gridsAreValid)
    {
        return 0;
    }
    return 1;
}

int check_sudoku(int *S)
{
    return checkEveryRowColGridInRangeParallelized(S, 0, DIM);
};
