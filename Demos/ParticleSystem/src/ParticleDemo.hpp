#pragma once

#include "Auris/Engine.hpp"
#include "Auris/Systems/ParticleSystem.hpp"
#include "Auris/Utilities/Interpolation.hpp"
#include "Auris/Utilities/AssetManager.hpp"

#include "SRE/imgui_sre.hpp"
#include "SRE/Texture.hpp"

#include "glm/glm.hpp"
#include <glm/gtc/random.hpp>

using namespace glm;
using namespace Auris;

class Scene1 : public Scene{
    public:
        void init(){}
};

class ParticleDemo : public Game {

    ParticleSystem particleSystem;
    Texture* cartman;

    //startup properties
    bool useTexture = false;
    int maxNumParticles = 10000;
    float particleDuration = 1;

    //update properties
    int numEmitParticles = 1;
    vec3 position = vec3(500,100,0);
    vec3 velocity = vec3(0,300,0);
    float rotation = 0;
    float angularVelocity = .5f;
    vec4 color = vec4(1,0,0,1);
    float size = 0.25f;
    vec4 endColor = vec4(0.5f,0.5f,0,0);
    float endSize = 1;

    //random properties
    float random_position = 0;
    float random_velocity = 100;
    float random_rotation = 3.14f;
    float random_angularVelocity = 1;
    float random_color = .25f;
    float random_size = .5f;
    float random_endColor = 0;
    float random_endSize = 0.5f;

    int selectedItemInterpolate = 0;
    static const int numInterpolateItems = 5;
    const char* interpolateItems[numInterpolateItems] = {"Acceleration", "Velocity", "AngularVelocity", "Color", "Size"};

    int selectedItemInterpolateType = 0;
    static const int num_interpolationTypeItems = 5;
    const char* interpolationTypeItems[num_interpolationTypeItems] = {"Linear", "Bezier", "Hermite", "CatmullRom", "BSpline"};

    static const int arrSize = 600;
    float arr_interpolation[arrSize] = {};
    



    void init() {
        cartman = AssetManager::getTexture("cartman.png");
 
        start();
    }

    void start(){
        particleSystem.startup(maxNumParticles, particleDuration,(useTexture ? cartman : SRE::Texture::getWhiteTexture()));
    }

    void earlyUpdate(float dt){

    }

    void update(float dt){
        for(int i = 0; i < numEmitParticles; i++){
            particleSystem.emit(
                    position + vec3(glm::circularRand<float>(glm::linearRand<float>(0,random_position)),0),
                    velocity + vec3(glm::circularRand<float>(glm::linearRand<float>(0,random_velocity)),0),
                    rotation + glm::linearRand<float>(0,random_rotation),
                    angularVelocity + glm::linearRand<float>(0,random_angularVelocity),
                    color + vec4(glm::sphericalRand<float>(glm::linearRand<float>(0,random_color)),0),
                    size + glm::linearRand<float>(0,random_size),
                    endColor + vec4(glm::sphericalRand<float>(glm::linearRand<float>(0,random_endColor)),0),
                    endSize + glm::linearRand<float>(0,random_endSize)
            );
        }
        particleSystem.update(dt);
        particleSystem.draw();
 
    }

    void lateUpdate(float dt){

    }

    void debugDraw(){
        ImGui::Begin("Showcases"); 
 
        ImGui::Text("Startup Properties");
        ImGui::Checkbox("Use texture", &useTexture);
        ImGui::DragInt("num particles allocated", &maxNumParticles);
        ImGui::DragFloat("particle Duration", &particleDuration, 0.1f);

        if(ImGui::Button("Startup")){
            particleSystem.shutdown();
            start();
        }
        ImGui::Separator();
        ImGui::DragFloat2("Global Acceleration", &particleSystem.acceleration.x, 0.1f);
        //ImGui::DragFloat2("TimeScale", &particleSystem.timeScale, 0.1f);
        ImGui::Separator();

        ImGui::Text("Update Properties");
        ImGui::DragInt("Num Emit Particles", &numEmitParticles);
        ImGui::DragFloat2("Position", &position.x);
        ImGui::DragFloat2("Velocity", &velocity.x, 0.1f);
        ImGui::DragFloat("Rotation", &rotation,0.01f);
        ImGui::DragFloat("Angular Velocity", &angularVelocity, 0.01f);
        ImGui::ColorEdit4("Color", &color.x);
        ImGui::DragFloat("Size", &size, 0.1f);
        ImGui::ColorEdit4("End Color", &endColor.x);
        ImGui::DragFloat("End Size", &endSize, 0.1f);
     
        ImGui::Separator();

        ImGui::Text("Randomess");
        ImGui::DragFloat("Position(circular)", &random_position);
        ImGui::DragFloat("Velocity(circular)", &random_velocity);
        ImGui::DragFloat("Rotation(linear)", &random_rotation, 0.1f);
        ImGui::DragFloat("Angular Velocity(linear)", &random_angularVelocity, 0.1f);
        ImGui::DragFloat("Color(spherical)", &random_color);
        ImGui::DragFloat("Size(linear)", &random_size, 0.1f);
        ImGui::DragFloat("End Color(spherical)", &random_endColor);
        ImGui::DragFloat("End Size(linear)", &random_endSize, 0.1f);
      
        ImGui::Separator();

        ImGui::Combo("Interpolation", &selectedItemInterpolate, interpolateItems, numInterpolateItems);
        ImGui::PlotLines("", arr_interpolation, arrSize);
        drawSelectedInterpolate();
    
        maxNumParticles = glm::clamp<int>(maxNumParticles, 1, 1000000);
        particleDuration = glm::clamp<float>(particleDuration, 0, 120);

        ImGui::End(); 

    }

    void shutdown(){

        delete cartman;
        cartman = nullptr;
 
    }



    void drawSelectedInterpolate(){
        switch(selectedItemInterpolate){
            case 0:
                //acceleration
                selectedItemInterpolateType = (int)particleSystem.interpolation_acceleration.getInterpolationType();
                ImGui::Combo("Type", &selectedItemInterpolateType, interpolationTypeItems, num_interpolationTypeItems); 
                ImGui::DragFloat2("p1", &particleSystem.interpolationPoints_acceleration[0].x);
                ImGui::DragFloat2("p2", &particleSystem.interpolationPoints_acceleration[1].x);
                ImGui::DragFloat2("p3", &particleSystem.interpolationPoints_acceleration[2].x);
                ImGui::DragFloat2("p4", &particleSystem.interpolationPoints_acceleration[3].x);

                particleSystem.interpolation_acceleration.setInterpolation((InterpolationType)selectedItemInterpolateType);

                for(int i = 0; i < arrSize;i++)
                    arr_interpolation[i] = particleSystem.interpolation_acceleration.interpolate((float)i/arrSize).y;

                break;
            case 1:
                //velocity
                selectedItemInterpolateType = (int)particleSystem.interpolation_velocity.getInterpolationType();
                ImGui::Combo("Type", &selectedItemInterpolateType, interpolationTypeItems, num_interpolationTypeItems); 
                ImGui::DragFloat2("p1", &particleSystem.interpolationPoints_velocity[0].x);
                ImGui::DragFloat2("p2", &particleSystem.interpolationPoints_velocity[1].x);
                ImGui::DragFloat2("p3", &particleSystem.interpolationPoints_velocity[2].x);
                ImGui::DragFloat2("p4", &particleSystem.interpolationPoints_velocity[3].x);
                particleSystem.interpolation_velocity.setInterpolation((InterpolationType)selectedItemInterpolateType);

                for(int i = 0; i < arrSize;i++)
                    arr_interpolation[i] = particleSystem.interpolation_velocity.interpolate((float)i/arrSize).y;



                break;
            case 2:
                //angularvelocity
                selectedItemInterpolateType = (int)particleSystem.interpolation_angularVelocity.getInterpolationType();
                ImGui::Combo("Type", &selectedItemInterpolateType, interpolationTypeItems, num_interpolationTypeItems); 
                ImGui::DragFloat2("p1", &particleSystem.interpolationPoints_angularVelocity[0].x);
                ImGui::DragFloat2("p2", &particleSystem.interpolationPoints_angularVelocity[1].x);
                ImGui::DragFloat2("p3", &particleSystem.interpolationPoints_angularVelocity[2].x);
                ImGui::DragFloat2("p4", &particleSystem.interpolationPoints_angularVelocity[3].x);

                particleSystem.interpolation_angularVelocity.setInterpolation((InterpolationType)selectedItemInterpolateType);

                for(int i = 0; i < arrSize;i++)
                    arr_interpolation[i] = particleSystem.interpolation_angularVelocity.interpolate((float)i/arrSize).y;



                break;
            case 3:
                //color
                selectedItemInterpolateType = (int)particleSystem.interpolation_color.getInterpolationType();
                ImGui::Combo("Type", &selectedItemInterpolateType, interpolationTypeItems, num_interpolationTypeItems); 
                ImGui::DragFloat2("p1", &particleSystem.interpolationPoints_color[0].x);
                ImGui::DragFloat2("p2", &particleSystem.interpolationPoints_color[1].x);
                ImGui::DragFloat2("p3", &particleSystem.interpolationPoints_color[2].x);
                ImGui::DragFloat2("p4", &particleSystem.interpolationPoints_color[3].x);

                particleSystem.interpolation_color.setInterpolation((InterpolationType)selectedItemInterpolateType);

                for(int i = 0; i < arrSize;i++)
                    arr_interpolation[i] = particleSystem.interpolation_color.interpolate((float)i/arrSize).y;



                break;
            case 4:
                //size
                selectedItemInterpolateType = (int)particleSystem.interpolation_size.getInterpolationType();
                ImGui::Combo("Type", &selectedItemInterpolateType, interpolationTypeItems, num_interpolationTypeItems); 
                ImGui::DragFloat2("p1", &particleSystem.interpolationPoints_size[0].x);
                ImGui::DragFloat2("p2", &particleSystem.interpolationPoints_size[1].x);
                ImGui::DragFloat2("p3", &particleSystem.interpolationPoints_size[2].x);
                ImGui::DragFloat2("p4", &particleSystem.interpolationPoints_size[3].x);

                particleSystem.interpolation_size.setInterpolation((InterpolationType)selectedItemInterpolateType);

                for(int i = 0; i < arrSize;i++)
                    arr_interpolation[i] = particleSystem.interpolation_size.interpolate((float)i/arrSize).y;

                break;
     
        }

    }


};
