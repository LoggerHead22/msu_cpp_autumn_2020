CC=g++
FLAGS= -std=c++17 -Wall -Wno-unused-variable -Wextra
all: test

test: test.o allocator.o
	$(CC) $(FLAGS) -o test test.o allocator.o
	
allocator.o: allocator.cpp allocator.h
	$(CC) $(FLAGS) -c allocator.cpp

test.o: test.cpp allocator.h
	$(CC) $(FLAGS) -c test.cpp
	
clean:
	rm -rf *.o allocator test
