#ifndef THREAD_POOL_PRIORITY_QUEUE_H
#define THREAD_POOL_PRIORITY_QUEUE_H

#include"task.h"
#include<vector>
#include<algorithm>

template<
    typename T, 
    typename Array=std::vector<T>, 
    typename compare_T=std::less<T>
>
class PriorityQueue{
public:
    PriorityQueue(){
        elems.clear();
    }

    T front(){
        return elems[0];
    }
    void push(const T &val){
        elems.push_back(val);
        up_heapify();
    }
    void pop(){
        int n = size();
        swap(elems[0],elems[n-1]);
        elems.pop_back();
        donw_heapify();
    }
    int size(){
        return elems.size();
    }

private:
    void up_heapify(){
        int n = size()-1;
        int parent=0;
        while(n > 0){
            parent = (n-1)/2;
            if (compare(elems[parent],elems[n])){
                std::swap(elems[parent], elems[n]);
                n = parent;
            }
        }
    }
    void donw_heapify(){
        int n = size();
        int ind = 0;
        while(ind *2 +1 < n){
            int tmp = ind;
            int left = ind * 2 + 1;
            if(compare(elems[ind], elems[left])){
                tmp = left;
            }
            int right  = ind*2 +2;
            if (right < n && compare(elems[ind], elems[right])){
                tmp = right;
            }

            if (tmp == ind){
                break;
            }

            std::swap(elems[tmp],elems[ind]);
            ind = tmp;
        }
    }

private:
    Array elems;
    compare_T compare;
};




#endif
