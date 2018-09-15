# 1. Sequential Solution

## What I did 
I implemented a library `sudoku.o` with the function `int checkSudoku(int *S)` which can test if a sudoku grid is valid. I also implemented a frontend binary `main` which tests the library against a number of programatically generated positive and negative test cases (the function `int * generateSudoku(int offset, int valid)`). 

For example:

```
$ make clean
$ make
$ main 18 #argument for number of test cases
```

Note that the function expects a conventional 9x9 sudoku grid. 

## How it works

`int *generateSudoku(int offset, int valid)`: 

- Generates a valid grid iteratively. 
- With an offset of range 0-9 on all values of this original grid, we can produce 9 valid grids. 
- We produce 9 more valid grids by filling in the grid column-wise instead. 
- Can be used to create an invalid grid for every valid grid. Transforms a valid grid to invalid simply by 'swapping' the values of the last two elements. 

`int checkSudoku(int *S)`: 

- Checks that every row, every column, then every grid is unique. Returns 0 if any section is non-unique (contains duplicates), returns 1 otherwise. 
- Uniqueness is implemented simply by checking if the sum of every member is equal to 45.
  - Assumes that a conventional sudoku puzzle only contains digits 1-9.
- Makes use of functions `getNthRowKthIndex`, `getNthColKthIndex`, `getNthGridKthIndex` to obtain relevant index at any point in time. 
  - Traversal is then a simple nested loop which iterates through 1st to 9th element of the 1st to 9th section (row, column, or grid).
  - Also avoids copying data. 

## What was difficult 

- Initially, the logic to traverse the array as a grid and collect values per subgrid to test for uniqueness was tricky. 
- Afterwards, when I decided to index directly into the original array, the difficult part was finding a mathematical function to express the index of an element belonging to a subgrid. 

# Potential improvements for this iteration  
- [ ] Allow input of file location containing an input grid.
- [ ] Refactor to allow sudoku grid of dimension n (where n is a square)?
- [ ] Come up with more positive test cases? 
- [X] Free memory after generating and testing each individual test case? 

# 2. Parallel Solution: Processes

## What I did 
Added `checkSudokuProcess` to `sudoku.o`, which has the same functionality as `checkSudoku`, but forks a child process which carries out half the processing. The print output attempts to display the interleaving of the processing of different parts of the grid. 

To run, provide argument for solution type (0 = sequential, 1 = processes), and number of valid sudoku solutions to test (max 18). For example:
```
$ make clean
$ make
$ main 1 18 
```

### Some other important changes: 
- Changed testing method in frontend - do not store in list. 
- I make sure to free the memory allocated to each sudoku generated by the `generateSudoku` function.
- Question: Do I also have to make sure to free the memory allocated to each shared-memory created by `mmap`? I couldn't find this online.

## How it works
Traversal of grid and uniqueness test remain the same. 

`checkEverySection` as well as `checkEveryRow`, `checkEveryCol`, etc now take parameters `start` and `end` which determine the range of the grid sections checked. Slight refactoring to compose the calling of different functions with different `start` and `end` via `checkEveryRowColGridInRange`. 

## What was difficult 
Initially in the parallel processing lab I made a careless mistake of assigning shared memory *after* forking the process, which got me stuck for awhile. 

Besides that the implementation was pretty straightforward. 

# Potential improvements for this iteration  
- [ ] Compare time taken for each solution