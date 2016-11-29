#pragma once 
#include <stdlib.h>
#include <iostream>


template <class T>
class Pool{

    size_t objectSize = sizeof(T);
    T* objects;
    bool* occupied;

public:

    T* begin() { return &objects[0]; }
    T* end() { return &objects[capacity]; }

    int count = 0;
    int capacity;

    Pool(){}
    Pool(int capacity){
        initialize(capacity);
    }

    ~Pool(){
        free(objects);
        free(occupied);
    }

    void initialize(int capacity){
        this->capacity = capacity;

        objects = (T*) malloc(objectSize * capacity);
        occupied = (bool*) calloc(capacity, sizeof(bool));

        //objects = new (std::nothrow) T[capacity];
        //occupied = new (std::nothrow) bool[capacity];

        if(objects == nullptr || occupied == nullptr){
            //could not allocate memory
            std::cout << "Could not allocate memory" << std::endl;
        }
    }


    T* operator [] (std::size_t index){
        if(index < 0 || index >= capacity){
            std::cout << "Index out of range, returning nullptr" << std::endl;
            return nullptr;
        }

        if(occupied[index] == false){
            //std::cout << "Index is not occupied, returning nullptr" << std::endl;
            return nullptr;
        }

        return &objects[index];
    }


    T* create(){
        int index = 0;
        for(;index <= capacity;index++){
            if(index == capacity){
                std::cout << "Pool is completly occupied, returning nullptr" << std::endl;
                return nullptr;

            }
            if(occupied[index] == false){
                occupied[index] = true;
                break;
            }
        }

        count++;

        return &objects[index];
    }

    void remove(T* ptr){
        for(int i = 0;i < capacity;i++){
            if(occupied[i] && ptr == &objects[i]){
                remove(i);
                break;
            }
        }
    }

    void remove(int index){
        occupied[index] = false;
        count--;
    }
};
