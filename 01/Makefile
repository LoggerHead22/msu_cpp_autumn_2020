CC=g++
FLAGS= -std=c++17 -Wall -Wno-unused-variable -Wextra
all: alloc_test

alloc_test: test.o allocator.o
	$(CC) $(FLAGS) -o alloc_test test.o allocator.o
	
allocator.o: allocator.cpp allocator.h
	$(CC) $(FLAGS) -c allocator.cpp

test.o: test.cpp allocator.h
	$(CC) $(FLAGS) -c test.cpp
	
test: alloc_test 
	./alloc_test

clean:
	rm -rf *.o alloc_test
