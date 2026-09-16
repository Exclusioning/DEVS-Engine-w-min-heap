#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED
#include <vector>
#include "Event.h"

using namespace std;
template <typename T>

class Heap{
public:
    vector<T> data;

    void swap(int a, int b){
        T temp = data[a];
        data[a] = data[b];
        data[b] = temp;
    }

    void shiftUp(int i){
        while(i > 0){
            int heapParent = (i - 1) / 2;
            if(data[i] < data[heapParent]){
                swap(i, heapParent);
                i = heapParent;
            } else {
                break;
            }
        }
    }

    void shiftDown(int i){
        int size = data.size();
        while(true){
            int left = i * 2 + 1;
            int right = i * 2 + 2;
            int smallest = i;

            if(left < size && data[left] < data[smallest]){
                smallest = left;
            }

            if(right < size && data[right] < data[smallest]){
                smallest = right;
            }

            if(smallest == i){
                break;
            }

            swap(i, smallest);
            i = smallest;
        }
    }

    bool isEmpty(){
        return data.empty();
    }

    void insert(const T& value){
        data.push_back(value);
        shiftUp(data.size() - 1);
    }

    T extractMin(){

        T min = data[0];
        T last = data.back();
        data.pop_back();

        if(!data.empty()){
            data[0] = last;
            shiftDown(0);
        }
        return min;
    }
};


#endif // HEAP_H_INCLUDED
