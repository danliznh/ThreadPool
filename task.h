#ifndef THREAD_POOL_TASK_H
#define THREAD_POOL_TASK_H

#include<functional>
#include<utility>
class Task{
public:
    template<typename FUNC, typename ...ARGS>
    Task(FUNC func, ARGS ...args){
        this->func = std::bind(func,std::forward<ARGS>(args)...);
    }

    void run(){
        this->func();
    }
private:
    std::function<void()> func;
};

#endif
