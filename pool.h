#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include"task.h"
#include"priority_queue.h"

#include<queue>
#include<mutex>
#include<condition_variable>
#include<thread>
#include<memory>
#include<iostream>

using namespace std;

template<typename QUEUETYPE = std::queue<shared_ptr<Task> > >
class ThreadPool
{
private:
    vector<thread *> threads;
    QUEUETYPE tasks;
    mutex m_mutex;
    condition_variable m_cond;
    bool is_running;
public:
    explicit ThreadPool(int size){
        is_running = true;
        for (size_t i = 0; i < size; i++)
        {
            threads.push_back(new thread(&ThreadPool::start, this));
        }
    }

    void start(){
        cout << "threads start"<<endl;
        while(is_running){
            shared_ptr<Task> t = get_task();
            if (t){
                
                t->run();
            }
            
        }
        cout << "threads end"<<endl;
    }

    shared_ptr<Task> get_task(){
        unique_lock<mutex> lock(m_mutex);
        while(is_running &&tasks.size() == 0){
            m_cond.wait(lock);
        }

        shared_ptr<Task> t = nullptr;
        if (is_running){
            t = tasks.front();
            tasks.pop();
        }

        return t;
    }

    void put_task(shared_ptr<Task> t){
        unique_lock<mutex> lock(m_mutex);
        tasks.push(t);
        m_cond.notify_all();
    }

    ~ThreadPool(){
        {// 唤醒所有的线程
            is_running = false;
            unique_lock<mutex> lock(m_mutex);
            m_cond.notify_all();
        }
        for (int i = 0; i < threads.size(); i++) {
            threads[i]->join();
            delete threads[i];
        }
    }
};



#endif

