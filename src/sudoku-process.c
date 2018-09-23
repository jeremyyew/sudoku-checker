#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sudoku.h>

int checkSudokuProcess(int *S)
{
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
        flags[0] = checkEveryRowColGridInRange(S, childStart, childEnd);
        printf("------ENDING CHILD PROCESSING------\n");
        exit(0);
    }
    else //parent
    {
        printf("------STARTING PARENT PROCESSING------\n");
        flags[1] = checkEveryRowColGridInRange(S, parentStart, parentEnd);
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