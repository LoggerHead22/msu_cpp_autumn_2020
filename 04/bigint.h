#pragma once
#include <iostream>
#include <cstring>
#include <string.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
using namespace std;


class BigInt{
	//Число поделим на блоки. 
	//Будем хранить блоки в массиве
private:
	const size_t blockSize = 4;//размер блока
	int *numBlocks = nullptr;//массив блоков
	size_t blockCount = 0, numberSize = 0;//Число блоков, длина числа
	bool isNegative = false; //Флаг орицательности
	
public:
    //Конструкторы
    BigInt(const string& number);
	
	BigInt(const BigInt&);
	BigInt(int);
	
	BigInt(BigInt&& moved);
	//Деструктор
	~BigInt();
		
    //Операторы
	//копирующие
    BigInt& operator=(const BigInt& other);
	BigInt& operator=(int other);
	//перемещающие
    BigInt& operator=(BigInt&& moved);
	
	//Сложение, вычитание
	BigInt operator+(const BigInt& other) const;
    BigInt operator+(int other) const;
    
	BigInt operator-(const BigInt& other) const;
    BigInt operator-(int other) const;
	
    BigInt& operator+=(const BigInt& other);
    BigInt& operator+=(int other);
	
	BigInt& operator-=(const BigInt& other);
    BigInt& operator-=(int other);
	//Умножение
	BigInt operator*(const BigInt& other) const;
    BigInt operator*(int other) const;
	
	BigInt& operator*=(const BigInt& other);
    BigInt& operator*=(int other);
	
	//Сравнение
    bool operator<(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
	
	bool operator>(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;
	
    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;

    bool operator<(int other) const;
    bool operator<=(int other) const;
	
	bool operator>(int other) const;
    bool operator>=(int other) const;
		
    bool operator==(int other) const;
    bool operator!=(int other) const;
	//Унарный минус
	BigInt operator-() const;
	//Вывод
	friend ostream& operator<<(ostream& stream, const BigInt& number);
	
private:
	bool _isDigit(const string &number) const;
	bool _absLessEq(const BigInt& other) const;

};
