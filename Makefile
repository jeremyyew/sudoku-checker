FLAGS= -I include -openmp

toto: clean main2 main

clean : 
	rm -f src/*.o *.o main main2

%.o : %.c
	gcc ${FLAGS} -c $< -o $@  -O3 

main2 : main2.o src/sudoku.o src/sudoku-process.o src/sudoku-pthreads.o src/sudoku-openmp.o src/utils.o
	gcc ${FLAGS} $^ -o $@ 

main: main.o src/sudoku.o src/sudoku-process.o src/sudoku-pthreads.o src/sudoku-openmp.o src/utils.o
	gcc ${FLAGS} $^ -o $@ 