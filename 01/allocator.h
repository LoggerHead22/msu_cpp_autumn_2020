#include <iostream>
using namespace std;



class Allocator
{
public:
    Allocator();
    ~Allocator();
    int makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();

private:
    char* start_ptr = nullptr;
    size_t offset = 0, maxSize;

};



