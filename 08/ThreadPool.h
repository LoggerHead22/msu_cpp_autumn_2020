#pragma once
#include <thread>
#include <iostream>
#include <queue>
#include <mutex>
#include <future>
using namespace std;




class ThreadPool
{
public:

	
    explicit ThreadPool(size_t poolSize)
	:poolSize_(poolSize)
	{
		for(size_t i = 0; i < poolSize_; i++)
		{
			threads_.push_back(thread([=] {exec_tasks();}));
		}	
			
	}
	void exec_tasks(){
		
	}

     // pass arguments by value
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;


	
private:
	size_t poolSize_ = thread::hardware_concurrency();
	vector<thread> threads_;
	
};