#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/wait.h>
#include <unistd.h>

int DIM = 9;

int getNthGridKthIndex(int n, int k)
{
    int gridHorizOffset = n % 3 * 3;
    int gridVertOffset = ((n - (n % 3)) / 3) * 27;
    int elementHorizOffset = k % 3;
    int elementVertOffset = ((k - (k % 3)) / 3) * 9;
    return (gridHorizOffset + gridVertOffset + elementHorizOffset + elementVertOffset);
};

int getNthRowKthIndex(int n, int k)
{
    return (n * 9) + k;
};

int getNthColKthIndex(int n, int k)
{
    return n + (k * 9);
};

int checkEverySection(int *S, int (*getNthSectionKthIndex)(int, int), int start, int end)
{
    int sum;
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

int checkEveryGrid(int *S, int start, int end)
{
    return checkEverySection(S, getNthGridKthIndex, start, end);
};

int checkEveryCol(int *S, int start, int end)
{
    return checkEverySection(S, getNthColKthIndex, start, end);
};

int checkEveryRow(int *S, int start, int end)
{
    return checkEverySection(S, getNthRowKthIndex, start, end);
};

int checkEveryRowColGridInRange(int *S, int start, int end)
{
    printf("checking row %d to %d\n", start, end - 1);
    int rowsAreValid = checkEveryRow(S, start, end);
    if (!rowsAreValid)
    {
        printf("row.\n");
    }
    printf("checking col to %d to %d\n", start, end - 1);
    int colsAreValid = checkEveryCol(S, start, end);
    if (!colsAreValid)
    {
        printf("column.\n");
    }
    printf("checking grid to %d to %d\n", start, end - 1);
    int gridsAreValid = checkEveryGrid(S, start, end);
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

int checkSudokuSequential(int *S)
{
    return checkEveryRowColGridInRange(S, 0, DIM);
};
