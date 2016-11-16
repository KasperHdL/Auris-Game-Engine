#pragma once

#include "SRE/imgui_sre.hpp"
#include "../../Systems/ParticleSystem.hpp"
#include <glm/gtc/random.hpp>

namespace Showcase{
class ParticleSystemShowcase{
public:
    ParticleSystem particleSystem;
    Texture* cartman;

    ParticleSystemShowcase(){
        cartman = SRE::Texture::createFromFile("data/cartman.png",false);

    }
    ~ParticleSystemShowcase(){}

    //startup properties
    bool useTexture = false;
    int maxNumParticles = 10000;
    float particleDuration = 1;;

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

    void startup(){
        particleSystem.startup(maxNumParticles, particleDurationq,(useTexture ? cartman : SRE::Texture::getWhiteTexture()));

     }

    void shutdown(){
        particleSystem.shutdown();

    }

    void makeGui(){
    
        ImGui::Text("Startup Properties");
        ImGui::Checkbox("Use texture", &useTexture);
        ImGui::DragInt("num particles allocated", &maxNumParticles);
        ImGui::DragFloat("particle Duration", &particleDuration);

        if(ImGui::Button("Startup")){
            shutdown();
            startup();
        }

        ImGui::Separator();

        ImGui::Text("Update Properties");
        ImGui::DragInt("Num Emit Particles", &numEmitParticles);
        ImGui::DragFloat2("Position", &position.x);
        ImGui::DragFloat2("Velocity", &velocity.x);
        ImGui::DragFloat("Rotation", &rotation);
        ImGui::DragFloat("Angular Velocity", &angularVelocity);
        ImGui::ColorEdit4("Color", &color.x);
        ImGui::DragFloat("Size", &size);
        ImGui::DragFloat4("End Color", &endColor.x);
        ImGui::DragFloat("End Size", &endSize);
     
        ImGui::Separator();

        ImGui::Text("Randomess");
        ImGui::DragFloat("Position(circular)", &random_position);
        ImGui::DragFloat("Velocity(circular)", &random_velocity);
        ImGui::DragFloat("Rotation(linear)", &random_rotation);
        ImGui::DragFloat("Angular Velocity(linear)", &random_angularVelocity);
        ImGui::DragFloat("Color(spherical)", &random_color);
        ImGui::DragFloat("Size(linear)", &random_size);
        ImGui::DragFloat("End Color(spherical)", &random_endColor);
        ImGui::DragFloat("End Size(linear)", &random_endSize);
     

    }

    void update(float dt){
        for(int i = 0; i < numEmitParticles; i++)
        particleSystem.emit(
                position + vec3(glm::circularRand<float>(random_position),0),
                velocity + vec3(glm::circularRand<float>(random_velocity),0),
                rotation + glm::linearRand<float>(0,random_rotation),
                angularVelocity + glm::linearRand<float>(0,random_angularVelocity),
                color + vec4(glm::sphericalRand<float>(random_color),0),
                size + glm::linearRand<float>(0,random_size),
                endColor + vec4(glm::sphericalRand<float>(random_endColor),0),
                endSize + glm::linearRand<float>(0,random_endSize)
                );
        particleSystem.update(dt);
    }

    void draw(){
        particleSystem.draw();
    }

};
}
