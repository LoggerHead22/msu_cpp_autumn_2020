#include "allocator.h"
#include <cassert>


void MakeAllocTest()
{
    Allocator my_alloc;
    assert(my_alloc.makeAllocator(0) == -1);
    // нельзя выделить 0 байт
    assert(my_alloc.makeAllocator(10) == 0);
    //нельзя вызывать makeAllocator 2 раза
    //иначе будет 2 new и 1 delete
    assert(my_alloc.makeAllocator(20) == -1);
}


void AllocTest()
{
    Allocator my_alloc;
    my_alloc.makeAllocator(10); //Выделили 10
    assert(my_alloc.alloc(3) != nullptr); //3
    assert(my_alloc.alloc(3) != nullptr); //6
    assert(my_alloc.alloc(3) != nullptr); //9
    assert(my_alloc.alloc(3) == nullptr); //12!
    assert(my_alloc.alloc(0) == nullptr); //нельзя получить 0 байт
    assert(my_alloc.alloc(1) != nullptr); //10
    assert(my_alloc.alloc(1) == nullptr); //11!
}

void NoMakeAllocTest()
{
    Allocator my_alloc;
    assert(my_alloc.alloc(3) == nullptr);
    //нельзя вызывать alloc до makeAllocator
    my_alloc.makeAllocator(10);
    assert(my_alloc.alloc(3) != nullptr);
}


void ResetTest()
{
    Allocator my_alloc;
    my_alloc.makeAllocator(10);
    assert(my_alloc.alloc(5) != nullptr); //5
    assert(my_alloc.alloc(5) != nullptr); //10
    assert(my_alloc.alloc(3) == nullptr); //13!
    my_alloc.reset();                  //0
    assert(my_alloc.alloc(3) != nullptr); //3
}


int main()
{
    MakeAllocTest();
    AllocTest();
    NoMakeAllocTest();
    ResetTest();
    std::cout << "Success!\n";

    return 0;
}
