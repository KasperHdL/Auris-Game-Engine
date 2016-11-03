#pragma once 
#include <stdlib.h>
#include <iostream>
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
        occupied = (bool*) calloc(capacity, sizeof(bool));

        //objects = new (std::nothrow) T[capacity];
        //occupied = new (std::nothrow) bool[capacity];

        if(objects == nullptr || occupied == nullptr){
            //could not allocate memory
            std::cout << "Could not allocate memory" << std::endl;
        }
    }

    ~Pool(){
        free(objects);
        free(occupied);
    }


    T* operator [] (std::size_t index){
        if(index < 0 || index >= capacity){
            std::cout << "Index out of range, returning nullptr" << std::endl;
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


    /*
    void tempTest(){
    float deltaTimeSec;
    int num = 10000;
    Uint64 END = SDL_GetPerformanceCounter();
    Uint64 START = SDL_GetPerformanceCounter();

    Pool<Sprite> sprites = Pool<Sprite>(num);
    Pool<glm::vec2> positions = Pool<glm::vec2>(num);
    END = SDL_GetPerformanceCounter();

    deltaTimeSec = (END - START) / (float)SDL_GetPerformanceFrequency();

    cout << "construction took " << deltaTimeSec<< endl;
    r.getCamera()->setWindowCoordinates();

    START = SDL_GetPerformanceCounter();
    for(int i = 0;i< sprites.capacity;i++){
        Sprite* s = sprites.create();
        glm::vec2* p = positions.create();

        s->mesh = Mesh::createCube();
        s->color = vec4(1,0,1,1);
        s->scale = glm::vec2(10,10);

        *p = glm::vec2(i*10,i * 10);

    }

    END = SDL_GetPerformanceCounter();
    deltaTimeSec = (END - START) / (float)SDL_GetPerformanceFrequency();

    cout << "values initialized " << deltaTimeSec << endl;

    
    START = SDL_GetPerformanceCounter();

    r.clearScreen(vec4(0.3f,0.3f,0.3f,1));
    for(int i = 0;i< sprites.capacity;i++){
        Shader* shader = Shader::getUnlitSprite();
        shader->set("color", sprites[i]->color);
        SimpleRenderEngine::instance->draw(sprites[i]->mesh, glm::translate(glm::mat4(1), vec3(*positions[i], 0)), shader);
    
    }

    END = SDL_GetPerformanceCounter();
    deltaTimeSec = (END - START) / (float)SDL_GetPerformanceFrequency();
    cout << "values drawn " << deltaTimeSec << endl;
    r.swapWindow();
    SDL_Delay(2000); 
    cout << "running engine" << endl;




    }
    */
};
