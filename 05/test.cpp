#include "serializer.h"
#include "deserializer.h"

//Тестовая структура 1
struct Data_1
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
	
    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};

//Тестовая структура 2
struct Data_2
{
    uint64_t a;
    bool b;
    bool c;
    uint64_t d;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c, d);
    }
	
    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c, d);
    }
};

void TestCase1(){
    //Простое копирование
    Data_1 x { 1, true, 2 };
    
    std::stringstream stream;
    
    Serializer serializer(stream);
    serializer.save(x);
    
    Data_1 y { 0, false, 3 };
    
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);
    
    assert(err == Error::NoError);
    
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}

void TestCase2(){
    //Несколько структур подряд
    Data_1 x_1 { 1, true, 2 };
    Data_2 y_1 { 0, false, true, 3};
    
    std::stringstream stream;
    
    Serializer serializer(stream);
    serializer.save(x_1);
    serializer.save(y_1);
    
    Data_1 x_2 { 5, false, 10};
    Data_2 y_2 { 0, true, false, 7};
    
    Deserializer deserializer(stream);
    
    Error err = deserializer.load(x_2);
    
    assert(err == Error::NoError);
    assert(x_1.a == x_2.a);
    assert(x_1.b == x_2.b);
    assert(x_1.c == x_2.c);

    err = deserializer.load(y_2);
    
    assert(err == Error::NoError);
    assert(y_1.a == y_2.a);
    assert(y_1.b == y_2.b);
    assert(y_1.c == y_2.c);
    assert(y_1.d == y_2.d);
}

void TestCase3(){
	//Неправильные аргументы
    Data_2 x_1 { 1, true, false, 10};
    Data_1 x_2 { 1, false, 17};
    
    stringstream ss;
    Serializer serializer(ss);
    serializer.save(x_1);
    
    Deserializer deserializer(ss);
    Error err = deserializer.load(x_2); //false not uint64_t
    assert(err == Error::CorruptedArchive);
    
    ss.clear();
    
    serializer.save(x_2);
    err = deserializer.load(x_1);
    assert(err == Error::CorruptedArchive);
}



int main(){
    TestCase1();
    TestCase2();
    TestCase3();
    
    cout<<"Success!"<<endl;
    
    return 0;
};