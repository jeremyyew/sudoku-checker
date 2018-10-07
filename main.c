#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include <sudokuAPI.h>

int main(int argc, char **argv)
{

    int (*SOLUTIONS[])(int *) = {checkSudokuSequential,
                                 checkSudokuProcess,
                                 checkSudokuPthreads,
                                 checkSudokuOpenMP};
    const char *SOLUTION_NAMES[] = {"sequential",
                                    "process",
                                    "pthreads",
                                    "openmp"};

    int WHICH_SOLUTION = 0;
    WHICH_SOLUTION = atoi(argv[1]);
    int (*check_sudoku)(int *) = SOLUTIONS[WHICH_SOLUTION];
    const char *solution_name = SOLUTION_NAMES[WHICH_SOLUTION];

    printf("Start %s sudoku program.\n", solution_name);
    for (int i = 2; i < argc; i++)
    {
        char *filename = argv[i];
        int *grid = (int *)malloc(9 * 9 * sizeof(int));

        if (load_sudoku(filename, grid) == EXIT_SUCCESS)
        {

            struct timeval start;
            struct timeval stop;

            gettimeofday(&start, NULL);
            int res = check_sudoku(grid);
            gettimeofday(&stop, NULL);

            float duration = ((stop.tv_sec - start.tv_sec) * 1000000u + stop.tv_usec - start.tv_usec) / 1.e6;

            if (res)
            {
                printf("%s: Valid (%f)\n", filename, duration);
            }
            else
            {
                printf("%s: Invalid (%f)\n", filename, duration);
            }
        }
        else
        {
            printf("%s: Invalid\n", filename);
        }

        free(grid);
    }
}
