#include "parser.h"
#include <cassert>


void print_vector(vector<string> tokens){
    for(auto token: tokens){
        cout<<token<<" ";
    }
    cout<<endl;
}

string reverseDigits(const string& token){
    //Функция переворачивает число
    string reverse = "";
    for(auto c: token){
        reverse.insert(reverse.begin(), c);
    }
    return reverse;
}


string deleteDigitsInString(const string& token){
    //Функция удаляет цифры из строки
    string new_str = "";
    for(auto c: token){
        if(!isdigit(c)){
            new_str += c;
        }
    }
    return new_str;
}


string upperCaseAlphas(const string& token){
    //Функция удаляет цифры из строки
    string new_str = "";
    for(auto c: token){
        if(isalpha(c)){
            new_str += toupper(c);
        }else{
            new_str += c;
        }
    }
    return new_str;
}


void setsCallbackTest(){
    TokenParser parser;
    vector<string> result, real_tokens;
    parser.setStartCallback([](){ cout<<"Привет, пользователь!\n"; });

    string test_string_1 = "123 anh34 Qwert 0l \n 6783 \t";

    result = parser.parseText(test_string_1);
    //Базовые функции считают число символов в токене.
    real_tokens = {"3", "5", "5", "2", "4"};
    assert(result == real_tokens);

    parser.setDigitTokenCallback(reverseDigits); //Перевернет числа
    parser.setStringTokenCallback(upperCaseAlphas);//Сделает буквы в верхнем регистре


    result = parser.parseText(test_string_1);
    real_tokens = {"321", "ANH34", "QWERT", "0L", "3876"};

    assert(result == real_tokens);
}

void finishCallBackTest1(){
    TokenParser parser;
    vector<string> result, real_tokens;

    string test_string_1 = "123 anh34 Qwert 0l \n 6783 \t";

    parser.setDigitTokenCallback(reverseDigits); //перевернет число
    parser.setStringTokenCallback(deleteDigitsInString);//удалит цифры из строк


    result = parser.parseText(test_string_1);
    real_tokens = {"321", "anh", "Qwert", "l", "3876"};
    assert(result == real_tokens);

    //После работы parseText _finishCallback вернет функции на базовые
    result = parser.parseText(test_string_1);
    real_tokens = {"3", "5", "5", "2", "4"};
    assert(result == real_tokens);
}



void finishCallBackTest2(){
    TokenParser parser;
    vector<string> result, real_tokens;

    string test_string_1 = "123 anh34 Qwert 0l \n 6783 \t";
    string test_string_2 = "-123 hello  24my friend, 1q2w3e4r5t \n";

    parser.setDigitTokenCallback(reverseDigits); //перевернет число
    parser.setStringTokenCallback(deleteDigitsInString); //удалит цифры из строк

    //Но если мы поменяем _finishCallback, то методы обработки токенов останутся
    parser.setFinishCallback([](){cout<<"Прощай, друг!\n";});
    result = parser.parseText(test_string_2);
    real_tokens = {"-", "hello", "my", "friend,", "qwert"};
    assert(result == real_tokens);

    //получается, для следующего parseText будут применяться, те же методы.
    result = parser.parseText(test_string_1);
    real_tokens = {"321", "anh", "Qwert", "l", "3876"};
    assert(result == real_tokens);
}

void noTokenTest(){
    TokenParser parser;
    vector<string> result, real_tokens;

    string test_string= "  \t \n \t   ";

    parser.setDigitTokenCallback(reverseDigits); //перевернет число
    parser.setStringTokenCallback(deleteDigitsInString);//удалит цифры из строк

    result = parser.parseText(test_string);
    assert(result.empty());
}

int main()
{
    setsCallbackTest();
    finishCallBackTest1();
    finishCallBackTest2();
    noTokenTest();

    std::cout << "Success!\n";

    return 0;
}
