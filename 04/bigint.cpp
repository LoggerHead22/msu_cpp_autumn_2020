#include "bigint.h"

BigInt::BigInt(const string& strnum)
{
	size_t len = strnum.size();
	
	if(!_isDigit(strnum)){
		throw "Bad string for BigInt constructor";
	}

	if(strnum[0] == '-'){
		isNegative = true;
		len--;
	}
	numberSize = len;
	blockCount = (len % blockSize == 0) ? len / blockSize : len / blockSize + 1;
	numBlocks = new int[blockCount];
	
	size_t shift = len - (blockCount - 1)*blockSize;
	int minus_shift = static_cast<int>(isNegative);
	
	numBlocks[0] = stoi(strnum.substr(minus_shift, shift));

	for(size_t i = 0; i < blockCount - 1; i++){
		numBlocks[i + 1] = 	stoi(strnum.substr(minus_shift + shift + i*blockSize, blockSize));
	}
	
}

BigInt::BigInt(const BigInt& other):
	blockCount(other.blockCount),
	numberSize(other.numberSize),
	isNegative(other.isNegative)
{
	numBlocks = new int[blockCount];
	
	copy(other.numBlocks, other.numBlocks + blockCount, numBlocks);
}

BigInt::BigInt(BigInt&& other):
	blockCount(move(other.blockCount)),
	numberSize(move(other.numberSize)),
	isNegative(move(other.isNegative))
{
	numBlocks = other.numBlocks;
	other.numBlocks = nullptr;
	other.blockCount = 0;
	other.numberSize = 0;
}

BigInt::BigInt(const int&other){
	
	*this = BigInt(to_string(other));
}

BigInt::BigInt(int&& other){
	
	*this = BigInt(to_string(move(other)));
}

//Операторы
BigInt& BigInt::operator=(const BigInt& other){
	if(this == &other){
		return *this;
	}
	if(blockCount != other.blockCount){
		blockCount = other.blockCount;
		delete[] numBlocks;
		numBlocks = new int[blockCount];
	}
	numberSize = other.numberSize;
	isNegative = other.isNegative;
	
	copy(other.numBlocks, other.numBlocks + blockCount, numBlocks);
	return *this;
}

BigInt& BigInt::operator=(BigInt&& other){
	if(this == &other){
		return *this;
	}
	delete[] numBlocks;
	blockCount = move(other.blockCount);
	numberSize = move(other.numberSize);
	isNegative = move(other.isNegative);
	numBlocks = other.numBlocks;
	
	other.numBlocks = nullptr;
	other.blockCount = 0;
	other.numberSize = 0;
	
	return *this;
}

BigInt& BigInt::operator=(int&& other){
	*this = BigInt(to_string(move(other)));
	return *this;
}
	
//Деструктор
BigInt::~BigInt(){
	delete[] numBlocks;
}

//Аддитивные операции
BigInt BigInt::operator+(const BigInt& other) const{
	string newNumber = "";
	int sign = -1, buffer = 0;
	const BigInt *bigNum, *smallNum;
	
	if(!(*this)._absLessEq(other)){
		bigNum =  this;
		smallNum = &other;
	}else{
		bigNum =  &other;
		smallNum = this;
	}
	
	if((bigNum->isNegative && smallNum->isNegative) ||
		(!bigNum->isNegative && !smallNum->isNegative)){
		sign = 1;
	}		

	for(size_t i = 0; i < bigNum->blockCount; i++){
		buffer += bigNum->numBlocks[bigNum->blockCount - 1 - i];
		
		if(i < smallNum->blockCount){
			buffer = buffer + sign * smallNum->numBlocks[smallNum->blockCount - 1 - i];
		}
		if(buffer > 0){
			string substr_buffer = to_string( buffer % static_cast<int>(pow(10, blockSize)));
			newNumber = string(blockSize - substr_buffer.size(),'0') +  substr_buffer + newNumber;
			buffer = buffer > pow(10, blockSize) ? 1 : 0;
		}else if (buffer < 0){
			newNumber = to_string(pow(10, blockSize) + buffer) + newNumber;
			buffer = -1;
		}else{
			newNumber = to_string(pow(10, blockSize)).substr(1, blockSize) + newNumber;
		}
	}

	size_t nonZeroChar = newNumber.find_first_not_of("0");

	if(nonZeroChar == string::npos){
		newNumber = "0";
	}else{
		newNumber = newNumber.substr(nonZeroChar, newNumber.size() - nonZeroChar);  
		if(bigNum->isNegative){
			newNumber = "-" + newNumber;
		}
	}
	return BigInt(newNumber);
}

BigInt BigInt::operator+(const int& other) const{
	return *this + BigInt(to_string(other));
}

BigInt BigInt::operator-(const BigInt& other) const{
	return *this + (-other);
}

BigInt BigInt::operator-(const int& other) const{
	return *this + (-BigInt(to_string(other)));
}


BigInt& BigInt::operator+=(const BigInt& other){
	*this = *this + other;
	return *this;
}

BigInt& BigInt::operator+=(const int& other){
	*this = *this + other;
	return *this;
}

BigInt& BigInt::operator-=(const BigInt& other){
	*this = *this - other;
	return *this;
}

BigInt& BigInt::operator-=(const int& other){
	*this = *this - other;
	return *this;
}

//Мультипликативные операции
BigInt BigInt::operator*(const BigInt& other) const{
	string newNumber = "";
	int sign = -1, buffer = 0;
	const BigInt *bigNum, *smallNum;
	
	if(!(*this)._absLessEq(other)){
		bigNum =  this;
		smallNum = &other;
	}else{
		bigNum =  &other;
		smallNum = this;
	}
	
	if((bigNum->isNegative && smallNum->isNegative) ||
		(!bigNum->isNegative && !smallNum->isNegative)){
		sign = 1; //знак итогового числа
	}		

	size_t newNmberSize = (bigNum->numberSize + smallNum->numberSize) / blockSize + 1;
	for(size_t i = 0; i < newNmberSize; i++){
		size_t start = (0 < static_cast<int>(i + 1 - bigNum->blockCount)? 
							static_cast<int>(i + 1 - bigNum->blockCount): 0); 
		size_t stop = i < bigNum->blockCount ? i + 1: bigNum->blockCount;

		if(stop == start){
			break;
		}

		for(size_t k = 0; k < stop - start; k++){
			if(static_cast<int>((smallNum->blockCount - 1) - (stop - k - 1)) >= 0){
				buffer += bigNum->numBlocks[(bigNum->blockCount - 1) - k - start] * 
						  smallNum->numBlocks[(smallNum->blockCount - 1) - (stop - k - 1)];
			}
		}
		string substr_buffer = to_string( buffer % static_cast<int>(pow(10, blockSize)));
		newNumber = string(blockSize - substr_buffer.size(),'0') + substr_buffer + newNumber;//дополним незначащими нулями в начале 
		buffer /= static_cast<int>(pow(10, blockSize));
	}
	newNumber = to_string(buffer) + newNumber;
	
	size_t nonZeroChar = newNumber.find_first_not_of("0"); //найдем первый не 0 символ, чтобы обрезать строку

	if(nonZeroChar == string::npos){
		newNumber = "0";
	}else{
		newNumber = newNumber.substr(nonZeroChar, newNumber.size() - nonZeroChar);  
	}
	
	if(sign == -1){
		//если число отрицательное - добавим минус
		newNumber = "-" + newNumber;
	}
	return BigInt(newNumber);
}

BigInt BigInt::operator*(const int& other) const{
	return (*this * BigInt(to_string(other)));
}

BigInt& BigInt::operator*=(const BigInt& other){
	*this = *this * other;
	return *this;
}

BigInt& BigInt::operator*=(const int& other){
	*this = *this * other;
	return *this;
}


//Операции сравнения
bool BigInt::operator<(const BigInt& other) const{
	bool res;
	if(isNegative && !other.isNegative){ //- +
		res = true;	
	}else if(!isNegative && other.isNegative){//+ -
		res = false;
	}else if(!isNegative && !other.isNegative){//+ +
		res = (_absLessEq(other) && (*this != other));
	}else if(isNegative && other.isNegative){//- - 
		res = (!_absLessEq(other));
	}
	return res;
}

bool BigInt::operator<=(const BigInt& other) const{
	return ((*this == other) || (*this < other));
}


bool BigInt::operator>(const BigInt& other) const{
	return !(*this <=other);
}

bool BigInt::operator>=(const BigInt& other) const{
	return !(*this < other);
}


bool BigInt::operator==(const BigInt& other) const{
	if(numberSize != other.numberSize){ //разная длина
		return false;
	}
	if(isNegative != other.isNegative){//разные знаки
		return false;
	}
	
	for(size_t i = 0; i < blockCount; i++){
		if(numBlocks[i] != other.numBlocks[i]){
			return false;
		}
	}
	return true;
}

bool BigInt::operator!=(const BigInt& other) const{
	return !(*this == other);
}


bool BigInt::operator<(const int& other) const{
	return (*this < BigInt(to_string(other)));
}

bool BigInt::operator<=(const int& other) const{
	return ((*this == other) || (*this < other));
}


bool BigInt::operator>(const int& other) const{
	return !(*this <= other);
}

bool BigInt::operator>=(const int& other) const{
	return !(*this < other);
}

bool BigInt::operator==(const int& other) const{
	return *this == BigInt(to_string(other));
}

bool BigInt::operator!=(const int& other) const{
	return !(*this == other);
}


//Унарный минус
BigInt BigInt::operator-() const{
	BigInt negInt = *this; 
	if(negInt != 0){
		negInt.isNegative = !negInt.isNegative;
	}		
	return negInt;
}
//Вывод
ostream& operator<<(ostream& stream, const BigInt& number){
	if(number.isNegative){
		stream<<"-";
	}
	
	stream<<number.numBlocks[0];
	
    for(size_t i = 1; i < number.blockCount; i++){
			string str_buffer = to_string(number.numBlocks[i]);
			stream<<string(number.blockSize - str_buffer.size(),'0') + str_buffer;
	}
	stream<<endl;
	return stream;
} 


//Дополнительные функции
bool BigInt::_absLessEq(const BigInt& other) const{
	// Модуль числа <= модулю числа other?
		if(numberSize < other.numberSize){
			return true;
		}else if(numberSize > other.numberSize){
			return false;
		}else{
			bool res = true;
			for(size_t i = 0; i <blockCount; i++){
				if((numBlocks[i] > other.numBlocks[i])){
					res = false;
					break;
				}					
			}
			return res;
		}
		assert(true);
}

bool BigInt::_isDigit(const string &number) const{
	//Это число?
	bool result = false;
	if(!number.empty()){
		if(number[0] == '-'){
			result = !(number.size() == 1) && find_if(number.begin() + 1, number.end(), 
						[](char c){ return !isdigit(c); }) == number.end();
		}else{
			result = find_if(number.begin(), number.end(),
							[](char c) { return !isdigit(c); }) == number.end();
		}
	}
	return result;
}
	
