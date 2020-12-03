#pragma once
#include <thread>
#include <iostream>
#include <queue>
#include <mutex>
#include <future>
#include <functional>
using namespace std;




class ThreadPool
{
private:
    size_t poolSize_ = thread::hardware_concurrency();
    bool terminate = false;
    vector<thread> threads_;
    queue<packaged_task<void()>> tasks_;
    mutex queue_mutex;
    condition_variable new_task;

public:

    explicit ThreadPool(size_t poolSize)
    :poolSize_(poolSize)
    {
        for(size_t i = 0; i < poolSize_; i++)
        {
            threads_.push_back(thread([this](){ exec_tasks(); }));
        }
    }

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>{

        std::packaged_task<decltype(func(args...))()> task(bind(func, forward<Args>(args)...));

        auto result = task.get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex);

            tasks_.emplace(std::move(task));
        }
        new_task.notify_one(); //сообщить потокам о новой задаче
        return result;
    }

    ~ThreadPool(){
        stop();
    }

    void stop(){
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            terminate = true;
        }

        new_task.notify_all();
        for(auto& t: threads_){
            t.join();
        }
    }

private:

    void exec_tasks(){

        while(true){
            std::packaged_task<void()> task;
            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                if (tasks_.empty()){//если очередь пустая
                    new_task.wait(lock, [&]{ return terminate || !tasks_.empty(); }); //ждем сигнала, если очередь не пуста или terminate, то идем дальше
                }
                if(terminate){
                    return;
                }
                task = std::move(tasks_.front());
                tasks_.pop();
            }
            task();
        }
    }

};
