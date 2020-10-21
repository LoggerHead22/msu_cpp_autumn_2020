#include <iostream>
#include <functional>
#include <vector>
#include <cctype>
#include <string>
using namespace std;

using TokenCallback = function<string (const string &token)>;
using InitCallback = function<void (void)>;


class TokenParser
{
    public:
        TokenParser();
        ~TokenParser();

        void setStartCallback(InitCallback);
        void setDigitTokenCallback(TokenCallback);
        void setStringTokenCallback(TokenCallback);
        void setFinishCallback(InitCallback);
        vector<string> parseText(const string &text);

    private:
        TokenCallback _editTokenDefault = [](const string &token){
        //Функция будет считать число символов в токене - она будет базовой
        //для обоих типов токенов
            string res = to_string(token.size());
            return res;
        };

        InitCallback _startParse = [](){ cout<<"Привет, я Парсер!\n"; };
        InitCallback _finishParse = [&](){
        //По умолчанию, закрывающая Callback функция будет возвращать Callback'и для токенов на значения по умолчанию.
            this->_editDigitToken = this->_editTokenDefault;
            this->_editStringToken = this->_editTokenDefault;
            cout<<"Пока, было приятно поработать!\n\n";
        };

        TokenCallback _editDigitToken = _editTokenDefault;
        TokenCallback _editStringToken = _editTokenDefault;
        bool _isDigit(const string &token);
};



