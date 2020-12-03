#include <cassert>
#include <cmath>
#include "ThreadPool.h"

struct A {
    int n1 = 1;
    int n2 = 21;
};

int foo(const A& a) {
   return a.n1 + a.n2;
}

string concat(string s1, string s2){
    return s1 + s2;
}

void sleeper(int time){
    this_thread::sleep_for(chrono::seconds(time));
    cout<<" Im go to sleep!"<<endl;
}

float power(float x, float y){
    return pow(x, y);
}

void TestCase1(){
    ThreadPool pool(8);

    auto task1 = pool.exec(foo, A());
    assert(task1.get() == 22);

    auto task2 = pool.exec(concat, "Techno", "Sphere");
    assert(task2.get() == "TechnoSphere");
}

void TestCase2(){
    ThreadPool pool(8);

    vector<future<float>> tasks;
    for(size_t i = 1; i < 20; i++){
        tasks.push_back(pool.exec(power, i, 2));
    }

    for(size_t i = 1; i < 20; i++){
        assert(tasks[i - 1].get() == pow(i, 2));
    }

}

void TestCase3(){
    //Хотим показать, что вывод первой функции будет после
    //вызовов возведения в степень
    ThreadPool pool(8);
    cout<<"Test Case 3"<<endl;
    auto task = pool.exec(sleeper, 2);

    vector<future<float>> tasks;
    for(size_t i = 1; i < 20; i++){
        tasks.push_back(pool.exec(power, i, 2));
    }
    cout<<" Power is ready!"<<endl;
}



int main(){
    TestCase1();
    TestCase2();
    TestCase3();

    cout<<"Success!"<<endl;
    return 0;
}
