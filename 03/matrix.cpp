#include "matrix.h"

//Перегрузка операторов прокси класса
int& MatrixProxy::operator[](size_t col)
{
        if(col >= MatrixProxy::rowLen){
                throw std::out_of_range("Input out of col count");
        }
        return MatrixProxy::rowPtr[col];
}

int MatrixProxy::operator[](size_t col) const
{
        if(col >= MatrixProxy::rowLen){
                throw std::out_of_range("Input out of col count");
        }
        return MatrixProxy::rowPtr[col];
}


//Конструкторы Matrix
Matrix::Matrix(size_t row, size_t col):
        rowCount(row),
        colCount(col)
{
        if(row == 0 || col == 0){
            throw std::out_of_range("Input args has 0 value");
        }
        Matr = new int[row * col];
        memset(Matr, 0, sizeof(int)*row*col);//инициализируем 0
}

Matrix::Matrix(size_t row, size_t col, vector<int> in_matr):
	Matrix(row, col)
{
	if(in_matr.size() != row * col){

            throw std::out_of_range("Input vector<int> has incorrect size");
	}
        for(size_t i = 0; i < in_matr.size(); i++){
            Matrix::Matr[i] = in_matr[i];
	}
}


Matrix::Matrix(const Matrix &rMatrix):
        Matrix(rMatrix.rowCount, rMatrix.colCount)
{
        for(size_t i = 0; i < rMatrix.rowCount * rMatrix.colCount; i++){
                this->Matr[i] = rMatrix.Matr[i];
	}
}

//Перегрузка операторов Matrix
Matrix& Matrix::operator=(const Matrix& rMatrix){
        if(this->rowCount * this->colCount != rMatrix.rowCount * rMatrix.colCount){
		delete[] this->Matr;
                this->Matr = new int[rMatrix.rowCount * rMatrix.colCount];
	}
	
        this->rowCount=rMatrix.rowCount;
        this->colCount=rMatrix.colCount;
	
        for(size_t i = 0;i<this->rowCount * this->colCount; i++){
                this->Matr[i]=rMatrix.Matr[i];
	}
	return *this;
}

MatrixProxy Matrix::operator[](size_t row) const  //Взять строку матрицы
{
        if(row >= Matrix::rowCount){
                throw std::out_of_range("Input out of row count");
        }
        return MatrixProxy(Matrix::Matr + Matrix::colCount * row, Matrix::colCount);
}
	
Matrix Matrix::operator+(const Matrix& rMatrix){
        if((this->rowCount != rMatrix.rowCount) || (this->colCount != rMatrix.colCount)){
                throw std::out_of_range("Input Matrix has different shape");
	}
	
	Matrix M(this->rowCount,this->colCount);
        for(size_t i = 0;i<this->rowCount * this->colCount; i++){
                M.Matr[i] = this->Matr[i] + rMatrix.Matr[i];
	}
	return M;
}
	
Matrix Matrix::operator*(const int mult){
	Matrix M(this->rowCount,this->colCount);
        for(size_t i = 0;i<this->rowCount * this->colCount; i++){
                M.Matr[i] = this->Matr[i] * mult;
	}
	return M;
}

Matrix& Matrix::operator+=(const Matrix& rMatrix){
    *this = *this + rMatrix;
    return *this;
}

Matrix& Matrix::operator*=(const int mult){
    *this = *this * mult;
    return *this;
}


bool Matrix::operator==(const Matrix& rMatrix){
        bool res = true;
        if((this->rowCount != rMatrix.rowCount) || (this->colCount != rMatrix.colCount)){
		res = false;
	}else{
                for(size_t i = 0; i < this->rowCount * this->colCount; i++){
                        if(this->Matr[i] != rMatrix.Matr[i]){
				res = false;
				break;
			}				
		}
	}
	return res;	
}


int Matrix::getRows() const
{
	return Matrix::rowCount;
}
	
int Matrix::getColumns() const
{
	return Matrix::colCount;
}


Matrix::~Matrix()
{
    delete[] Matrix::Matr;
}


ostream& operator<<(ostream& stream, const Matrix& rMatrix){
        for(int i = 0; i < rMatrix.getRows(); i++){
                for(int k = 0; k < rMatrix.getColumns(); k++){
                        stream<<rMatrix[i][k]<<" ";
		}
            stream<<endl;
	}
	return stream;
} 

