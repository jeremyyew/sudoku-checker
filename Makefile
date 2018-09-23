toto: clean main

FLAGS= -I include

clean : 
	rm -f src/*.o main

%.o : %.c
	gcc -c $< -o $@ ${FLAGS} -O3

main : src/main.o src/sudoku.o src/sudoku-process.o src/sudoku-pthreads.o src/sudoku-openmp.o
	gcc -o $@ $^