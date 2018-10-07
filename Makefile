CFLAGS=-I./include -lpthread -openmp

all : prog_sequential prog_process prog_pthreads prog_openmp 
test : test_sequential test_process test_pthreads test_openmp 

prog_% : srcs/sudoku_%.o main.o srcs/utils.o
	gcc ${CFLAGS} -o $@ $^

test_% : prog_%
	./$< input*.txt

clean :
	rm -f prog_* *~ */*~ *.o srcs/*.o
