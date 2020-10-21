CC=g++
FLAGS= -std=c++17 -Wall -Wno-unused-variable -Wextra
all: parser_test

parser_test: test.o parser.o
	$(CC) $(FLAGS) -o parser_test test.o parser.o
	
parser.o: parser.cpp parser.h
	$(CC) $(FLAGS) -c parser.cpp

test.o: test.cpp parser.h
	$(CC) $(FLAGS) -c test.cpp
	
test: parser_test 
	./parser_test

clean:
	rm -rf *.o parser_test
