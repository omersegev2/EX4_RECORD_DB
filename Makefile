FLAGS=-Wall -pedantic-errors -std=c99
RDB_DIR= /home/omer/Desktop/for_linux-main
CC=gcc

VALGRIND=valgrind --leak-check=full --show-leak-kinds=all -s

all: test1 test2

test1: main.c $(RDB_DIR)/*.c
	$(CC) $(FLAGS) -DTEST1 $(RDB_DIR)/*.c -L$(RDB_DIR) -lprog2 -o $@
	./$@ > $@.out 2> $@.err
 
test2: main.c $(RDB_DIR)/*.c
	$(CC) $(FLAGS) -DTEST2 $(RDB_DIR)/*.c -L$(RDB_DIR) -lprog2 -o $@
	./$@ > $@.out 2> $@.err
 
valgrind_test1: test1
	$(VALGRIND) ./$< > $<.out 2> $<.err

valgrind_test2: test2
	$(VALGRIND) ./$< > $<.out 2> $<.err
 
clean:
	rm -f *.o test1 test2

.PHONY: test1 test2 g_test clean

