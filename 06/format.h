#pragma once
#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include <stdexcept>
#include<tuple>
using namespace std;


class BadStringFormat: public exception{
	//Ошибка для случая неправильного формата строки
public:  
	const char* what() const noexcept override{
		return  "Input String has bad format";
	}
};

class BadValueFormat: public exception{
	// Ошибка для случая некорректного значения внутри скобок
public:  
	const char* what() const noexcept override{
		return  "Input String has bad value in {}";
	}
};

//Функция для записи n-ого аргумента в поток
template <class T>
void stream_n_elem(ostream& stream, size_t index, T&& arg){
	if(index == 0){
		stream << arg;
	}
}

template <class T, class... ArgsT>
void stream_n_elem(ostream& stream, size_t index, T&& arg, ArgsT&&... args){
	if(index == 0){
		stream << arg;
	}else{
		stream_n_elem(stream, index - 1, args...);
	}
}


template <class... ArgsT>
string format(string in_str, ArgsT&&... args){
	stringstream sstream;
	int args_count = sizeof...(args);

	bool in_bracket = false;
	string temp_string = ""; //строка для записи значений из скобок
	for(size_t i = 0; i < in_str.size(); i++){
		if(in_str[i] == '{'){
			if(in_bracket){//если уже внутри скобок, то ошибка
				throw BadStringFormat();
			}else{
				in_bracket = true;
			}
			continue;
		}
		
		if(in_str[i] == '}'){
			if(!in_bracket){//если и так вне скобок, то ошибка
				throw BadStringFormat();
			}else{
				in_bracket = false;
				int ind;
				try{
					ind = stoi(temp_string); 
				}catch(const std::logic_error&){
					throw BadValueFormat(); //если в скобках не целое число
				}
				if(ind < 0 || ind >= args_count){
					throw BadValueFormat(); //если оно не подходит под наши аргументы
				}
				stream_n_elem(sstream, static_cast<size_t>(ind), forward<ArgsT>(args)...);
				temp_string = "";
			}
			continue;
		}
		
		if(in_bracket){
			temp_string += in_str[i];//элемент в скобках запоминаем
		}else{
			sstream << in_str[i]; //элемент вне скобок сразу пишем в поток
		}
	}
	
	return sstream.str();
	
};


