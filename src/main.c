#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sudokuAPI.h>

int main(int argc, char **argv)
{

    int (*SOLUTIONS[])(int *) = {checkSudokuSequential,
                                 checkSudokuProcess,
                                 checkSudokuPthreads};
    const char *SOLUTION_NAMES[] = {"sequential",
                                    "process",
                                    "pthreads"};

    int WHICH_SOLUTION = 0;
    int NUM_TEST_CASES = DIM;
    if (argc == 3)
    {
        WHICH_SOLUTION = atoi(argv[1]);
        NUM_TEST_CASES = atoi(argv[2]);
    }
    else
    {
        printf("Please provide argument for solution type (0 = sequential, 1 = processes, 2 = pthreads),\n and number of valid sudoku solutions to test (max 18).\n For example: ./main 0 18\n");
        return 0;
    }

    printf("\n**** Using %s solution ****\n\n", SOLUTION_NAMES[WHICH_SOLUTION]);

    printf("\nGenerating %d sudoku grids for test cases...\n\n", NUM_TEST_CASES * 2);
    printf("Testing %d positive cases...\n", NUM_TEST_CASES);
    int FAILURES = 0;
    int (*check)(int *) = SOLUTIONS[WHICH_SOLUTION];
    for (int i = 0; i < NUM_TEST_CASES; i++)
    {
        int *validSudoku = generateSudoku(i, 1);
        if (!check(validSudoku))
        {
            printf("Positive test case %d/%d failed!\n", i + 1, NUM_TEST_CASES);
            FAILURES++;
            continue;
        }
        printf("Positive test case %d/%d passed!\n", i + 1, NUM_TEST_CASES);
        free(validSudoku);
    };
    printf("\n");
    printf("Testing %d negative cases...\n", NUM_TEST_CASES);
    for (int i = 0; i < NUM_TEST_CASES; i++)
    {
        int *invalidSudoku = generateSudoku(i, 0);
        if (check(invalidSudoku))
        {
            printf("Negative test case %d/%d failed!\n", i + 1, NUM_TEST_CASES);
            FAILURES++;
            continue;
        }
        printf("Negative test case %d/%d passed!\n", i + 1, NUM_TEST_CASES);
        free(invalidSudoku);
    };
    if (FAILURES > 0)
    {
        printf("%d/%d test cases failed.\n", FAILURES, NUM_TEST_CASES * 2);
    }
    else
    {
        printf("\n*******************\nAll %d/%d test cases passed!\n*******************\n", NUM_TEST_CASES * 2, NUM_TEST_CASES * 2);
    }
};
