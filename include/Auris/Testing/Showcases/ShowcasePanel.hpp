#pragma once
#include "Showcase.hpp"
#include "ParticleSystem.hpp"
#include "SRE/imgui_sre.hpp"


class ShowcasePanel{

    int previousItem = 0;
    int selectedItem = 0;
    static const int numItems = 2;
    const char* items[numItems] = {"No Showcase", "ParticleSystem"};

    bool toggle_particleSystem;
    Showcase* showcase = nullptr;

public:
    ShowcasePanel(){}
    ~ShowcasePanel(){
        shutdown();
    }


    void createShowcase(int num){
        switch(num){
            case 1:
                showcase = new ParticleSystemShowcase();

            break;


        }

    }

    void startup(){
        if(selectedItem > 0)
            createShowcase(selectedItem);
    }

    void shutdown(){
        delete showcase;
        showcase = nullptr;
    }

    void makeGui(){

        ImGui::Combo("Select Showcase", &selectedItem, items, numItems);

        if(previousItem != selectedItem){
            if(previousItem > 0){
                delete showcase;
                showcase = nullptr;
            }

            if(selectedItem > 0)
                createShowcase(selectedItem);
        }

        if(showcase != nullptr)
            showcase->imGui();

        previousItem = selectedItem;
    }

    void update(float dt){
        if(showcase == nullptr)return;

        showcase->update(dt);
    }

    void draw(){
        if(showcase == nullptr)return;

        showcase->draw();
    }


};
