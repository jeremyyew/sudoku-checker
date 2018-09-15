#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

int DIM = 9;

int *generateSudoku(int offset, int valid)
{
    int n_squared = (int)pow((double)9, 2);
    int *grid = malloc(n_squared * sizeof(int));
    if (valid == 1)
    {
        printf("Valid Sudoku grid %d:\n\n", offset);
    }
    else
    {
        printf("Invalid Sudoku grid %d:\n\n", offset);
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

int checkSudoku(int *S)
{
    return checkEveryRowColGridInRange(S, 0, DIM);
};

int checkSudokuProcess(int *S)
{
    // Assign sudoku grid to shared memory. We avoid needlessly copying the grid. This is safe because we will not be mutating the grid.
    int *sharedSudoku = mmap(NULL, 81 * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    sharedSudoku = S;
    // Store results in shared memory.
    int *flags = mmap(NULL, 2 * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    int childStart = 0;
    int childEnd = DIM / 2;
    int parentStart = DIM / 2;
    int parentEnd = DIM;
    int pid = fork();
    if (pid == 0) //child
    {
        printf("------STARTING CHILD PROCESSING------\n");
        flags[0] = checkEveryRowColGridInRange(sharedSudoku, childStart, childEnd);
        printf("------ENDING CHILD PROCESSING------\n");
        exit(0);
    }
    else //parent
    {
        printf("------STARTING PARENT PROCESSING------\n");
        flags[1] = checkEveryRowColGridInRange(sharedSudoku, parentStart, parentEnd);
        printf("------ENDING PARENT PROCESSING------\n");
        // need to wait otherwise we might print the shared memory before child has modified it.
        wait(NULL);
    }
    // only parent runs the rest of the code because child would have exited already
    if (!flags[0] || !flags[1])
    {
        return 0;
    }
    return 1;
}