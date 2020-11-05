CC=g++
FLAGS= -std=c++17 -Wall -Wno-unused-variable -Wextra
all: bigint_test

bigint_test: test.o bigint.o
	$(CC) $(FLAGS) -o bigint_test test.o bigint.o
	
bigint.o: bigint.cpp bigint.h
	$(CC) $(FLAGS) -c bigint.cpp

test.o: test.cpp bigint.h
	$(CC) $(FLAGS) -c test.cpp
	
test: bigint_test 
	./bigint_test

clean:
	rm -rf *.o bigint_test
