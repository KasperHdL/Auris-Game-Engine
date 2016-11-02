#pragma once 
#include <stdlib.h>
#include <new>


template <class T>
class Pool{

    size_t objectSize = sizeof(T);
    T* objects;
    bool* occupied;

    public:

    int count = 0;
    int capacity;

    Pool(int capacity){
        this->capacity = capacity;

        objects = (T*) malloc(objectSize * capacity);
        occupied = (bool*) malloc(sizeof(bool) * capacity);

        //objects = new (std::nothrow) T[capacity];
        //occupied = new (std::nothrow) bool[capacity];

        if(objects == nullptr || occupied == nullptr){
            //could not allocate memory
        }
    }

    ~Pool(){

    }


    T* operator [] (std::size_t index){
        return &objects[index];
    }


    T* create(){
        int index = 0;
        for(;index < capacity;index++){
            if(occupied[index] == false){
                occupied[index] = true;
                break;
            }
        }

        count++;

//        delete objects[index];// if not already deleted?

        return &objects[index];
    }

    void remove(T* ptr){
        for(int i = 0;i < count;i++){
            if(ptr == objects[i]){
                remove(i);
                break;
            }
        }
    }

    void remove(int index){
        delete objects[index];
        occupied[index] = false;
        count--;
    }
};
