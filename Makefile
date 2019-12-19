default: prog

dictionary.o: dictionary.c
	gcc -Wall -c dictionary.c dictionary.h

spell.o: spell.c
	gcc -Wall -c spell.c

test.o: test_main.c
	gcc -Wall -c test_main.c

main.o: main.c
	gcc -Wall -c main.c

test: dictionary.o spell.o test_main.o
	gcc -Wall -o test_main test_main.o spell.o dictionary.o -lcheck
	./test_main

fuzzer: dictionary.c spell.c fuzzer.c
	clang -g -fsanitize=address,fuzzer dictionary.c
	spell.c fuzzer.c -o fuzzer

prog: dictionary.o spell.o main.o
	gcc -Wall -o spell_check dictionary.o spell.o main.o

clean:
	rm -f *.o

cleanall:clean
	rm spell_check
	
