toto: clean main

FLAGS= -I include

clean : 
	rm -f src/*.o main

%.o : %.c
	gcc -c $< -o $@ ${FLAGS}

main : src/main.o src/sudoku.o
	gcc -o $@ $^