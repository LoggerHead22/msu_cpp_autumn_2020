#include <cassert>
#include <iostream>
#include <vector>
#include "myVector.h"
#include "iterator.h"


//Тестовая структура 1
struct Data
{
public:
    int a_ = 0;
    bool b_ = false;
    string c_ = "";


    Data(){}
    Data(int a, bool b, string c) :a_(a), b_(b), c_(c){}

    Data(Data&& other) :
        a_(move(other.a_)),
        b_(move(other.b_)),
        c_(move(other.c_)){}

    Data(const Data& other) :
        a_(other.a_),
        b_(other.b_),
        c_(other.c_){}

    Data& operator=(const Data& other){
        a_ = other.a_;
        b_ = other.b_;
        c_ = other.c_;
        return *this;
    }

    Data& operator=(Data&& other){
        a_ = move(other.a_);
        b_ = move(other.b_);
        c_ = move(other.c_);
        other.a_ = 0;
        other.b_ = false;
        other.c_ = "";
        return *this;
    }

};



void TestCase1(){
    //resize, reserve, size, capacity
    Vector<int> v;

    for (int i = 0; i < 100; ++i)
    {
        v.push_back(i);
    }

    assert(v.size() == 100);
    assert(v.capacity() == 128);

    v.reserve(512);

    assert(v.size() == 100);
    assert(v.capacity() == 512);

    v.resize(10);

    assert(v.size() == 10);
    assert(v.capacity() == 512);

    v.clear();

    assert(v.size() == 0);
    assert(v.capacity() == 512);
}

void TestCase2(){
    //[], pop_back, push_back
    Vector<int> v;

    for (int i = 0; i < 100; ++i)
    {
        v.push_back(i * i);
    }

    for (int i = 0; i < 100; ++i)
    {
        assert(v[i] == i * i);
        v[i] += 100;
        assert(v[i] == 100 + i * i);
    }

    v.pop_back();
    v.pop_back();
    v.pop_back();

    assert(v.size() == 97);
    assert(v.capacity() == 128);

    v.clear();

    assert(v.size() == 0);
    assert(v.capacity() == 128);
    assert(v.empty() == true);
}

void TestCase3(){
    //конструктор, присваивание
    Vector<int> v(20);

    for (int i = 0; i < 20; ++i)
    {
        v[i] = i * i;
    }

    for (int i = 0; i < 20; ++i)
    {
        assert(v[i] == i * i);
        v[i] += 100;
        assert(v[i] == 100 + i * i);
    }

    assert(v.size() == 20);
    assert(v.capacity() == 32);

    v[21] = 0; //в std::vector так можно

    bool catch_error = false;
    try{
        v[40] = -1;
    }catch(const std::out_of_range&){
        catch_error = true;
    }

    assert(catch_error);
}

void TestCase4(){
    //Произвольный тип, перемещения
    Vector<Data> v;

    Data d1(3, true, "first elem");
    Data d2(2, false, "second elem");
    Data d3(7, true, "third elem");

    v.push_back(d1);
    v.push_back(move(d2));
    v.push_back(move(d3));

    assert(v.size() == 3);
    assert(v.capacity() == 4);

    v.emplace_back(11, false, "fourth elem");

    //просто копия
    assert(v[0].a_ == d1.a_);
    assert(v[0].b_ == d1.b_);
    assert(v[0].c_ == d1.c_);

    //тут переместили
    assert(v[1].a_ != d2.a_);
    assert(v[1].c_ != d2.c_);

    assert(v[v.size() - 1].a_ == 11);
    assert(v[v.size() - 1].b_ == false);
    assert(v[v.size() - 1].c_ == "fourth elem");

    assert(v.size() == 4);
    assert(v.capacity() == 4);

    v.resize(6, Data(-1, true, "default elem")); //новые 2 элемента по умолчанию

    assert(v[4].c_ == "default elem");
    assert(v[5].c_ == "default elem");
}

void TestCase5(){
    //begin, end
    Vector<int> v(20);

    for (int i = 0; i < 20; ++i)
    {
        v[i] = i * i;
    }

    int k = 0;
    for (Vector<int>::iterator it = v.begin() ; it != v.end(); ++it){
        *it += k;
        k++;
    }

    k = 0;
    for (int i = 0; i < 20; ++i)
    {
        assert(v[i] == k +  i * i);
        k++;
    }

    for (Vector<int>::iterator it = v.end() - 1 ; it != v.begin(); --it){
        *it -= 10;
    }

    k = 1;
    for (int i = 1; i < 20; ++i)
    {
        assert(v[i] == k - 10 + i * i);
        k++;
    }

    cout<<"For each:"<<endl;
    for_each(v.begin(), v.end(), [](int x) { std::cout << x << ' '; });
    cout<<endl;

}


void TestCase6(){

    //rbegin, rend
    Vector<int> v;
    v.resize(20, 0);

    int k = 1;
    for (Vector<int>::my_reverse_iterator it = v.rbegin() ; it != v.rend(); ++it){
        //заполнили с конца, т.е большие числа в начале
        *it = k * k;
        k++;
    }

    k = 20;
    for (int i = 0; i < 20; ++i)
    {
        assert(v[i] == k * k);
        k--;
    }

}

void TestCase7(){
    //Конструкторы
    Vector<int> v1(5);
    for(size_t i = 0 ; i < 5; i++){
        v1[i] = i * i;
    }
    
    Vector<int> v2 = v1; //конструктор копирования

    assert(v2[0] == 0);
    assert(v2[1] == 1);
    assert(v2[2] == 4);
    assert(v2[3] == 9);
    assert(v2[4] == 16);
    assert(v2.size() == v1.size());
    assert(v2.capacity() == v1.capacity());
    
    for(size_t i = 0 ; i < 5; i++){
        v2[i] += 1;
    }
    
    v2.push_back(-1);
    v2.push_back(-2);
    

    v1 = v2; //оператор копирования
    
    assert(v2[0] == 1);
    assert(v2[1] == 2);
    assert(v2[2] == 5);
    assert(v2[3] == 10);
    assert(v2[4] == 17);
    assert(v2[5] == -1);
    assert(v2[6] == -2);
    assert(v2.size() == v1.size());
    assert(v2.capacity() == v1.capacity());

    Vector<int> v3 = move(v1); //конструктор перемещения
    
    assert(v3[0] == 1);
    assert(v3[1] == 2);
    assert(v3[2] == 5);
    assert(v3[3] == 10);
    assert(v3[4] == 17);
    assert(v3[5] == -1);
    assert(v3[6] == -2);
    assert(v3.size() == 7);
    assert(v3.capacity() == 8);
    
    assert(v1.size() == 0);
    assert(v1.capacity() == 0);

    Vector<int> v4;
    
    v4 = move(v2); //оператор перемещения
    
    assert(v4[0] == 1);
    assert(v4[1] == 2);
    assert(v4[2] == 5);
    assert(v4[3] == 10);
    assert(v4[4] == 17);
    assert(v4[5] == -1);
    assert(v4[6] == -2);
    assert(v4.size() == 7);
    assert(v4.capacity() == 8);
    
    assert(v2.size() == 0);
    assert(v2.capacity() == 0);

}

int main()
{

    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();
    TestCase5();
    TestCase6();
    TestCase7();

    cout<<"Success!"<<endl;
    return 0;
}
