#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int *generateSudoku(int offset, int valid)
{
    int n_squared = (int)pow((double)9, 2);
    int *grid = malloc(n_squared * sizeof(int));
    if (valid == 1)
    {
        printf("Valid Sudoku grid %d:\n", offset);
    }
    else
    {
        printf("Invalid Sudoku grid %d:\n", offset);
    }

    for (int row = 0; row < 9; row++)
    {
        const int rowStart = row * 9;
        printf("\t\t");

        int startVal = (row / 3);
        int vertOffset = (row % 3) * 3;
        for (int col = 0; col < 9; col++)
        {
            int currentIndex = rowStart + col;
            if (offset > 9)
            {
                //fill by column instead
                currentIndex = row + col * 9;
            }
            int val = ((startVal + vertOffset + col) + offset) % 9 + 1;
            // Switch the last two numbers. This makes last two columns incorrect.
            if (valid != 1 && currentIndex == n_squared - 1)
            {
                val--;
            }
            else if (valid != 1 && currentIndex == n_squared - 2)
            {
                val++;
            }

            grid[currentIndex] = val;
            printf("%d ", val);
        };
        printf("\n");
    };
    printf("\n");
    return grid;
};

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
    return n + k * 9;
};

int checkEverySection(int *S, int (*getNthSectionKthIndex)(int, int))
{
    int sum;
    for (int n = 0; n < 9; n++)
    {
        sum = 0;
        for (int k = 0; k < 9; k++)
        {
            sum += S[getNthSectionKthIndex(n, k)];
        }
        if (sum != 45)
        {
            printf("\tFailed at %dth ", n + 1);
            return 0;
        }
    }
    return 1;
};

int checkEveryGrid(int *S)
{
    return checkEverySection(S, getNthGridKthIndex);
};

int checkEveryCol(int *S)
{
    return checkEverySection(S, getNthColKthIndex);
};

int checkEveryRow(int *S)
{
    return checkEverySection(S, getNthRowKthIndex);
};

int checkSudoku(int *S)
{

    int rowsAreValid = checkEveryRow(S);
    if (!rowsAreValid)
    {
        printf("row.\n");
    }
    int colsAreValid = checkEveryCol(S);
    if (!colsAreValid)
    {
        printf("column.\n");
    }
    int gridsAreValid = checkEveryGrid(S);
    if (!gridsAreValid)
    {
        printf("grid.\n");
    }
    if (!rowsAreValid || !colsAreValid || !gridsAreValid)
    {
        return 0;
    }
    return 1;
};