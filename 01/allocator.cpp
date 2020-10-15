#include "allocator.h"

Allocator::Allocator(){}

int Allocator::makeAllocator(size_t maxSize)
{
    //Возвращает -1 если не удалось выделить память, 0 иначе.
    if(maxSize == 0 || Allocator::start_ptr != nullptr){
        //Второе условие, чтобы нельзя было вызвать makeAllocator 2 раза
        return -1;
    }

    Allocator::start_ptr = new(std::nothrow) char[maxSize];

    if(Allocator::start_ptr == nullptr){
        return -1;
    }
    Allocator::maxSize = maxSize;
    return 0;
}

char* Allocator::alloc(size_t size)
{
    char* curr_ptr = nullptr;
    if((Allocator::start_ptr !=nullptr) && (size <= Allocator::maxSize - Allocator::offset)){
        curr_ptr = Allocator::start_ptr + Allocator::offset;
        Allocator::offset += size;
    }
    return curr_ptr;
}

void Allocator::reset(){
    Allocator::offset = 0;
}

Allocator::~Allocator()
{
    delete[] Allocator::start_ptr;
}
