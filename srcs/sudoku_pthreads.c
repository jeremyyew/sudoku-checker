#include <stdlib.h>
#include <stdio.h>
#include <sudoku_internal.h>
#include <pthread.h>

struct CheckerArgs
{
    int *sudoku;
    int start, end;
};

void *checkEveryRowColGridInRangeWithStruct(void *a)
{
    printf("*** Starting a thread... ***\n");
    struct CheckerArgs *args = (struct CheckerArgs *)a;
    int *S = args->sudoku;
    int returnVal = checkEveryRowColGridInRange(S, args->start, args->end);
    return ((void *)returnVal);
}

int check_sudoku(int *S)
{
    // Reference: http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html

    struct CheckerArgs thread1Args = (struct CheckerArgs){S, 0, DIM / 2};
    struct CheckerArgs thread2Args = (struct CheckerArgs){S, DIM / 2, DIM};

    pthread_t thread1, thread2;
    int ret;
    ret = pthread_create(&thread1, NULL, &checkEveryRowColGridInRangeWithStruct, &thread1Args);
    ret = pthread_create(&thread2, NULL, &checkEveryRowColGridInRangeWithStruct, &thread2Args);
    if (ret)
    {
        fprintf(stderr, "Error - some pthread_create() failed with return code: %d\n", ret);
        exit(EXIT_FAILURE);
    }
    void *flags[2];
    pthread_join(thread1, &flags[0]);
    printf("Thread 1 terminated!\n");
    pthread_join(thread2, &flags[1]);
    printf("Thread 2 terminated!\n");

    if (!(int)flags[0] || !(int)flags[1])
    {
        return 0;
    }
    return 1;
}