#include "parser.h"

TokenParser::TokenParser(){}

void TokenParser::setStartCallback(InitCallback userStartParse)
{
    TokenParser::_startParse = userStartParse;
}

void TokenParser::setFinishCallback(InitCallback userFinishParse)
{
    TokenParser::_finishParse = userFinishParse;
}

void TokenParser::setDigitTokenCallback(TokenCallback userDigitCallback)
{
    TokenParser::_editDigitToken = userDigitCallback;
}

void TokenParser::setStringTokenCallback(TokenCallback userStringCallback)
{
    TokenParser::_editStringToken = userStringCallback;
}


vector<string> TokenParser::parseText(const string &text)
{
    //Делит строку на токены. Для каждого типа токенов применяет свою функцию.
    // Выходные данные: вектор преобразованных токенов.
    TokenParser::_startParse();
    vector<string> result;
    string token = "";

    for(auto s: text){
        if(!isspace(s)){
            token += s;
        }else if(token != ""){
            result.push_back(token);
            token = "";
        }
    }

    for(auto &token: result){
        if(TokenParser::_isDigit(token)){
            token = TokenParser::_editDigitToken(token);
        }else{
            token = TokenParser::_editStringToken(token);
        }
    }

    TokenParser::_finishParse();
    return result;
}

bool TokenParser::_isDigit(const string &token){
    //Проверка токена на число
    return !token.empty() && find_if(token.begin(), token.end(),
                                     [](char c) { return !isdigit(c); }) == token.end();
}




TokenParser::~TokenParser(){}
