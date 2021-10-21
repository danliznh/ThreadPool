#ifndef THREAD_POOL_TASK_H
#define THREAD_POOL_TASK_H

#inclue<function>

class Task{
public:
    template<typename FUNC, typename ...ARGS>
    Task(FUNC func, ARGS ...args){
        this->func = std::bind(&func,forward<ARGS>(args)...);
    }

    void run(){
        this->func();
    }
private:
    function<void()> func;
};

#endif
