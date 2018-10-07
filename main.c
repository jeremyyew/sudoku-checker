#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include <sudoku.h>

int main(int argc, char **argv)
{

    printf("Start sudoku program.\n");

    for (int i = 1; i < argc; i++)
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
