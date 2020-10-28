#pragma once
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;


class MatrixProxy{
    //Прокси класс - строка матрицы
private:
    int *rowPtr;//указатель на строку
    size_t rowLen;//длина строки

public:
    MatrixProxy(int *rowPtr, size_t rowLen):
		rowPtr(rowPtr),
		rowLen(rowLen){}

    int& operator[](size_t col);
    int operator[](size_t col) const;
	
};
	

class Matrix{
	
private:
	int *Matr;
	size_t rowCount, colCount;
	
public:
        //Конструкторы
        Matrix(size_t row, size_t col);
        Matrix(size_t row, size_t col, vector<int> in_matr);
	Matrix(const Matrix &X);
	
        //Операторы
        MatrixProxy operator[](size_t row) const;
	
        Matrix& operator=(const Matrix& rMatrix);
	
        Matrix operator+(const Matrix& rMatrix) const;
        Matrix operator*(const int mult) const;

        Matrix& operator+=(const Matrix& rMatrix);
        Matrix& operator*=(const int mult);

        int getRows() const;
        int getColumns() const;

        bool operator==(const Matrix& rMatrix)const;
        bool operator!=(const Matrix& rMatrix)const;

	~Matrix();
	
};

//Вывод в ostream
ostream& operator<<(ostream& stream, const Matrix& X);
