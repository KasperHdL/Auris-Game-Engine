#pragma once
#include "ParticleSystem.hpp"
#include "SRE/imgui_sre.hpp"


class Showcases{

    int previousItem = 0;
    int selectedItem = 0;
    static const int numItems = 2;
    const char* items[numItems] = {"No Showcase", "ParticleSystem"};

    bool toggle_particleSystem;
    Showcase::ParticleSystemShowcase particleSystem;

public:
    Showcases(){}
    ~Showcases(){}

    void startup(){

    }

    void shutdown(){

    }

    void makeGui(){
        ImGui::Combo("Select Showcase", &selectedItem, items, numItems);

        switch(previousItem){
            case 1:
                //particle system
                if(selectedItem != 1){
                    particleSystem.shutdown();
                }

            break;

        }


        switch(selectedItem){
            case 0:
                //nothing

            break;
            case 1:
                //particle system
                if(previousItem != 1){
                    particleSystem.startup();
                }

                particleSystem.makeGui();

            break;
        }



        previousItem = selectedItem;
    }

    void update(float dt){
        switch(selectedItem){
            case 0:
                //nothing
            break;
            case 1:
                particleSystem.update(dt);
            break;
        }
    }

    void draw(){

        switch(selectedItem){
            case 0:
                //nothing
            break;
            case 1:
                particleSystem.draw();
            break;
        }
    }


};
