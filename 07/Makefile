CC=g++
FLAGS= -std=c++17 -Wall -Wno-unused-variable -Wextra
all: myVector_test

myVector_test: test.o 
	$(CC) $(FLAGS) -o myVector_test test.o

test.o: test.cpp myVector.h iterator.h
	$(CC) $(FLAGS) -c test.cpp
	
test: myVector_test 
	./myVector_test

clean:
	rm -rf *.o myVector_test
