CC=g++
FLAGS= -std=c++17 -Wall -Wno-unused-variable -Wextra
all: serialize_test

serialize_test: test.o
	$(CC) $(FLAGS) -o serialize_test test.o

test.o: test.cpp serializer.h deserializer.h
	$(CC) $(FLAGS) -c test.cpp 

test: serialize_test 
	./serialize_test

clean:
	rm -rf *.o serialize_test
