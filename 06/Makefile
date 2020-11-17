CC=g++
FLAGS= -std=c++17 -Wall -Wno-unused-variable -Wextra
all: format_test

format_test: test.o
	$(CC) $(FLAGS) -o format_test test.o

test.o: test.cpp format.h
	$(CC) $(FLAGS) -c test.cpp
	
test: format_test 
	./format_test

clean:
	rm -rf *.o format_test
