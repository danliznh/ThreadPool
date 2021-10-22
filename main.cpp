
#include"pool.h"

void func(int a, int b) {
    cout << a << " + " << b << endl;
    return ;
}

int main(){
    shared_ptr<ThreadPool<PriorityQueue< shared_ptr<Task> > > >tp(new ThreadPool<PriorityQueue< shared_ptr<Task> > >());
    tp->init(5);
    this_thread::sleep_for(chrono::seconds(2));
    tp->put_task(  shared_ptr<Task>(new  Task(func, 3, 4)) );
    tp->put_task(shared_ptr<Task>(new Task(func, 5, 10)));
    tp->put_task(shared_ptr<Task>(new Task(func, 14, 60)));
    this_thread::sleep_for(chrono::seconds(2));
    return 0;
}