#pragma once
#include <iostream>
#include <cmath>
#include "iterator.h"
using namespace std;


template<class T>
class my_allocator
{
    //my_allocator и vector будут хранить один и тот же указатель.
    //при необходимости allocator будет расширять размер выделенной памяти и
    //копировать предыдущие данные
    //my_allocator будет выделять чуть больше памяти чм нужно вектору.
    //По аналогии с std::vector будет выделяться память - наименьшая степень 2ки >= требуемого количества
public:    

    template <class, class> friend class Vector;
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;

    pointer allocate(size_type count){
        if(ptr_ == nullptr){ //если мы еще ничего не выделяли
            ptr_ = allocate_new_block(count);
        }else if(count > max_size_){//если уже есть данные,
                                    //то нужно перекопировать в больший массив.
            size_type prev_max_size = max_size_;
            pointer new_ptr = allocate_new_block(count);
            if(prev_max_size > 0){
                move(ptr_, ptr_ + prev_max_size, new_ptr);
            }
            delete[] ptr_;
            ptr_ = new_ptr;
        }
        //если от нас хотят меньше памяти чем есть, то мы ничего не делаем
        return ptr_;
    }

    pointer allocate_new_block(size_type count){
        if(count == 0){
            max_size_ = 1;
        }else{  //наибольшая степень 2 >=count
            max_size_ = pow(2, ceil(log(count)/log(2)));
        }

        pointer new_ptr_ = new value_type[max_size_];
        return new_ptr_;
    }
    
    void deallocate(pointer ptr){
        //можно очищать только тот указатель который мы храним
        if(ptr == ptr_){
            delete[] ptr_;
            ptr_ = nullptr;
            max_size_ = 0;
        }
    }
    
    size_type max_size(){
        return max_size_;
    }

    ~my_allocator(){
        deallocate(ptr_);
    }

private:
    size_type max_size_ = 0;
    pointer ptr_ = nullptr;
};


template<class T, class Alloc = my_allocator<T>>
class Vector
{
public:
    using size_type = size_t;
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;

    using iterator = RandAccIterator<T>;
    using my_reverse_iterator = reverse_iterator<RandAccIterator<T>>;

    using allocator_type = Alloc;
 
    Vector(){}
    Vector(size_type count){
        data_ = alloc.allocate(count);
        size_ = count;
        capacity_ = alloc.max_size();
    }
    
    Vector(const Vector<T>& other)
    {    
        data_ = alloc.allocate(other.size_),
        size_ = other.size_,
        capacity_ = alloc.max_size();
        copy(other.data_, other.data_ + other.capacity_, data_);
    }
    
    Vector(Vector<T>&& other):
        data_(move(other.data_)),
        size_(move(other.size_)),
        capacity_(move(other.capacity_))
    {
        alloc.ptr_ = data_;
        alloc.max_size_ = capacity_;
        
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    
    Vector<T>& operator=(const Vector<T>& other){
        if(this == &other){
            return *this;
        }
        alloc.deallocate(data_); //очистим память
        
        data_ = alloc.allocate(other.size_); //выделим новую
        size_ = other.size_;
        capacity_ = alloc.max_size();
        
        copy(other.data_, other.data_ + other.capacity_, data_); //скопируем данные 
        return *this;
    }

    Vector<T>& operator=(Vector<T>&& other){
        if(this == &other){
            return *this;
        }
        alloc.deallocate(data_); //очистим память
        
        data_ = other.data_; 
        size_ = other.size_;
        capacity_ = other.capacity_;
        
        alloc.ptr_ = data_;
        alloc.max_size_ = capacity_;
        
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

        return *this;
    }
    
    ~Vector(){}

    reference operator[](size_type ind){
        if(ind >= capacity_){
            throw std::out_of_range("Input ind > vector capacity_");
        }
        return data_[ind];
    }

    const_reference operator[](size_type ind) const{
        if(ind >= capacity_){
            throw std::out_of_range("Input ind > vector capacity_");
        }
        return data_[ind];
    }

    void push_back(const T& val){
        if(size_ == capacity_){ //нет лишнего места
            data_ = alloc.allocate(++size_);//выделяем столько, чтобы влез еще хотя бы 1
            capacity_ = alloc.max_size(); //минимальная степень двойки >= size_
            data_[size_ - 1] = val;
        }else if(size_ < capacity_){ //место есть, то просто записываем
            data_[size_++] = val;
        }
    }

    void push_back(T&& val){
        if(size_ == capacity_){ //нет лишнего места
            data_ = alloc.allocate(++size_);//выделяем столько, чтобы влез еще хотя бы 1
            capacity_ = alloc.max_size(); //минимальная степень двойки <= size_
            data_[size_ - 1] = move(val);
        }else if(size_ < capacity_){ //место есть, то просто записываем
            data_[size_++] = move(val);
        }
    }

    void pop_back(){
        if(size_ > 0){
            size_--;
        }
    }

    template<class... Args>
    void emplace_back(Args&&... args){
        push_back(value_type(forward<Args>(args)...));
    }

    bool empty() const noexcept{
        return bool(size_ == 0);
    }

    size_t size() const noexcept{
        return size_;
    }

    size_t capacity() const noexcept{
        return capacity_;
    }

    void clear() noexcept{
        size_ = 0;
    }

    void resize(size_type n){
        if(n > capacity_){
            data_ = alloc.allocate(n);
            capacity_ = alloc.max_size();
        }
        size_ = n;
    }

    void resize(size_type n, const value_type& val){
        if(n > capacity_){
            data_ = alloc.allocate(n);
            capacity_ = alloc.max_size();
        }

        if(n > size_){
            for(size_type i = size_; i < n; i++){
                data_[i] = value_type(val);
            }
        }
        size_ = n;
    }

    void reserve(size_type n){
        if(n > capacity_){
            data_ = alloc.allocate(n);
            capacity_ = alloc.max_size();
        }
    }

    iterator begin(){
        return iterator(data_);
    }
    iterator end(){
        return iterator(data_ + size_);
    }


    my_reverse_iterator rbegin(){
        return my_reverse_iterator(end());
    }

    my_reverse_iterator rend(){
        return my_reverse_iterator(begin());
    }

private:
    T* data_ = nullptr;
    size_type size_ = 0;
    size_type capacity_ = 0;
    allocator_type alloc;
};



