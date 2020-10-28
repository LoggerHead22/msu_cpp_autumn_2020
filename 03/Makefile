CC=g++
FLAGS= -std=c++17 -Wall -Wno-unused-variable -Wextra
all: matrix_test

matrix_test: test.o matrix.o
	$(CC) $(FLAGS) -o matrix_test test.o matrix.o
	
matrix.o: matrix.cpp matrix.h
	$(CC) $(FLAGS) -c matrix.cpp

test.o: test.cpp matrix.h
	$(CC) $(FLAGS) -c test.cpp
	
test: matrix_test 
	./matrix_test

clean:
	rm -rf *.o matrix_test
