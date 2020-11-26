#pragma once
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>

template <class T>
class RandAccIterator
    : public std::iterator<std::forward_iterator_tag, T>
{
private:
    T* ptr_;

public:
	using difference_type =  typename std::iterator<std::random_access_iterator_tag, T>::difference_type;
    
	RandAccIterator() : ptr_(nullptr) {}
    RandAccIterator(T* rhs) : ptr_(rhs) {}
    RandAccIterator(const RandAccIterator &rhs)
		: ptr_(rhs.ptr_) {}

    T& operator*() { return *ptr_; }
	T operator*() const { return *ptr_; }
	
    RandAccIterator& operator++() { ++ptr_; return *this;}
	RandAccIterator& operator--() { --ptr_; return *this;}
	
	RandAccIterator& operator+=(difference_type rhs) 
	{
		ptr_ += rhs; 
		return *this;
	}
	
    RandAccIterator& operator-=(difference_type rhs) 
	{
		ptr_ -= rhs; 
		return *this;
	}
	
	RandAccIterator operator+(difference_type rhs) const 
	{ 
	    return RandAccIterator(ptr_+rhs); 
	}
    
	RandAccIterator operator-(difference_type rhs) const 
	{
		return RandAccIterator(ptr_-rhs);
	}
	
    bool operator==(const RandAccIterator& other) const
    {
        return ptr_ == other.ptr_;
    }
    bool operator!=(const RandAccIterator& other) const
    {
        return !(*this == other);
    }
	
};
