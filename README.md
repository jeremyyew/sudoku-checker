# Report 

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
- [ ] Free memory after generating and testing each individual test case? 