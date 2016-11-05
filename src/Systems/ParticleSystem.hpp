#pragma once


#include "glm/glm.hpp"
#include <vector>

#include "SRE/ParticleMesh.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include <SRE/Shader.hpp>
#include <SRE/Texture.hpp>


using namespace std;
using namespace glm;
using namespace SRE;
class ParticleSystem{
    vector<vec3> finalPositions;
    vector<vec4> finalColors;
    vector<float> finalSizes;

    //particle properties
    vector<vec3> positions;
    vector<vec3> velocities;

    vector<vec4> startColors;
    vector<float> startSizes;

    vector<vec4> endColors;
    vector<float> endSizes;

    vector<float> startTimes;

    float currentTime;
    float particleDuration;

    SRE::Texture* texture;
    
    SRE::ParticleMesh* mesh;
    SRE::Shader* shader;

    vec4 lerpColor(vec4 start, vec4 end, float t){
        return vec4(
                mix(start[0], end[0], t),
                mix(start[1], end[1], t),
                mix(start[2], end[2], t),
                mix(start[3], end[3], t)
                );
    }

public:
    vec3 acceleration;
    int particleIndex = 0;

    ParticleSystem(){};

    void startup(int numParticles, float particleDuration, Texture* texture = Texture::getWhiteTexture()){
        currentTime = 0;
        this->particleDuration = particleDuration;
        this->texture = texture;
        
        shader = SRE::Shader::getStandardParticles();
        acceleration = vec3(0,-10,0);

        finalPositions.reserve(numParticles);

        positions.reserve(numParticles);
        velocities.reserve(numParticles);
        startColors.reserve(numParticles);
        endColors.reserve(numParticles);
        startSizes.reserve(numParticles);
        endSizes.reserve(numParticles);
        startTimes.reserve(numParticles);

        //zero arrays
        for(int i = 0; i < numParticles; i++){
            finalPositions.push_back(vec3(0,0,0));
            finalColors.push_back(vec4(0));
            finalSizes.push_back(0);

            positions.push_back(vec3(0,0,0));
            velocities.push_back(vec3(0,0,0));
            startColors.push_back(vec4(1,1,1,1));
            endColors.push_back(vec4(0));
            startSizes.push_back(0.1f);
            endSizes.push_back(0);
            startTimes.push_back(-999);
        }

        update(0);
    }


    void emit(vec3 position, vec3 velocity, vec4 color, float size, vec4 endColor, float endSize){
        if(startTimes[particleIndex] + particleDuration < currentTime){
            startTimes[particleIndex] = currentTime;
            positions[particleIndex] = position;
            velocities[particleIndex] = velocity;
            startColors[particleIndex] = color;
            startSizes[particleIndex] = size;
            endColors[particleIndex] = endColor;
            endSizes[particleIndex] = endSize;
            
            particleIndex = (particleIndex + 1) % positions.size();
        }
    }

    void update(float dt){

        for (int i = 0; i < positions.size(); i++){
            float t = currentTime - startTimes[i];
            if(t > particleDuration){
                finalPositions[i] = vec3(0,0,-1000);
                continue;
            }

            auto a = .5f * acceleration * t*t;
            auto v = velocities[i] * t;
            auto p0 = positions[i];

            finalPositions[i] = a + v + p0;

            
            float p = t / particleDuration;
            finalColors[i] = lerpColor(startColors[i], endColors[i], p); 
            finalSizes[i] = glm::mix<float>(startSizes[i], endSizes[i], p);
            
        }

        vector<vec2> uvs;
        vector<float> uvSize;
        vector<float> uvRotation;

        if(mesh == nullptr){
            mesh = new SRE::ParticleMesh(finalPositions, startColors, uvs, uvSize, uvRotation, startSizes);
        }else{
            mesh->update(finalPositions, finalColors, uvs, uvSize, uvRotation, finalSizes);
        }

        currentTime += dt;

    }

    void draw(){
        shader->set("tex", texture);
        SRE::SimpleRenderEngine::instance->draw(mesh, glm::mat4(1), shader);

    }



};
