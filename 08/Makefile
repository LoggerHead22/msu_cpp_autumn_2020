CC=g++
FLAGS= -std=c++17 -Wall -Wno-unused-variable -Wextra
all: thread_pool_test

thread_pool_test: test.o 
	$(CC) $(FLAGS) -o thread_pool_test test.o

test.o: test.cpp ThreadPool.h
	$(CC) $(FLAGS) -c test.cpp
	
test: thread_pool_test 
	./thread_pool_test

clean:
	rm -rf *.o thread_pool_test
