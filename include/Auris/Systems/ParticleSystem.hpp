#pragma once


#include "glm/glm.hpp"
#include <vector>

#include "SRE/ParticleMesh.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include <SRE/Shader.hpp>
#include <SRE/Texture.hpp>

#include "Auris/Utilities/Interpolation.hpp"

namespace Auris{
using namespace std;
using namespace glm;
using namespace SRE;

//! The ParticleSystem class
    /*! Handles all particles
    */
class ParticleSystem{

    vector<vec3> finalPositions; /*!< A vector of vec3 values: finalPositions. The final positions of the particle. */
    vector<vec4> finalColors; /*!< A vector of vec4 values: finalColors. The final colors of the particle. */
    vector<float> finalSizes; /*!< A vector of float values: finalSizes. The final sizes of the particle. */
    vector<float> finalRotation; /*!< A vector of float values: finalRotation. The final rotations of the particle. */
    

    //particle properties
    vector<vec3> positions;  /*!< A vector of vec3 values: positions. The positions of the particles. */
    vector<vec3> velocities; /*!< A vector of vec3 values: velocities. The rotations of the particles. */
    vector<float> rotations; /*!< A vector of float values: rotations. The rotations of the particles. */
    vector<float> angularVelocities; /*!< A vector of float values: AngularVelocities. The angular velocities of the particles. */

    vector<vec4> startColors; /*!< A vector of vec4 values: startColors. The start colors of the particles. */
    vector<float> startSizes; /*!< A vector of float values: startSizes. The start sizes of the particles. */

    vector<vec4> endColors; /*!< A vector of vec4 values: endColors. The end colors of the particles. */
    vector<float> endSizes; /*!< A vector of float values: endSizes. The end sizes of the particles. */

    vector<float> startTimes; /*!< A vector of float values: startTimes. The start times of the particles. */

    float currentTime; /*!< A float value: currentTime. The current Particle time in the particle system. */
    float particleDuration; /*!< A float value: particleDuration. The duration of each particle. */

    SRE::Texture* texture; /*!< A Texture pointer: texture. An instance of the texture of the particle. */
    
    SRE::ParticleMesh* mesh = nullptr; /*!< A Mesh pointer: mesh. An instance of the mesh of the particle */
    SRE::Shader* shader; /*!< A shader pointer:shader. An instance of the shader of the particle. */

    //empty
    vector<vec2> uvs; /*!< A vector of vec2: uvs. Empty, as it is not needed in 2D. */
    vector<float> uvSize; /*!< A vector of float: uvSize. Empty, as it is not needed in 2D. */

    //! A lerpColor method, taking 3 arguments.
        /*!
         * Lerps from one color to the other, based on the float
         * \param start a vec4 value, that is the start color
         * \param end a vec4 value, that is the end color
         * \param t a float value, that is the current lerp differentiater (between 0-1)
         * \return vec4, as the color between the two colors
        */
    vec4 lerpColor(vec4 start, vec4 end, float t){
        return vec4(
                mix<float>(start[0], end[0], t),
                mix<float>(start[1], end[1], t),
                mix<float>(start[2], end[2], t),
                mix<float>(start[3], end[3], t)
                );
    }

public:
    float timeScale = 1; /*!< A float value: timeScale. The time scale of the particle (default is 1). */
    vec3 acceleration = vec3(0,0,0); /*!< A vec3 value: acceleration. The acceleration of the particle (default is vec3(0)). */
    int particleIndex = 0; /*!< An int value: particleIndex. The index of the particle */


    //interpolation
 
    vector<vec2> interpolationPoints_acceleration; /*!< A vector of vec2 values: interpolationPoints_acceleration. The acceleration points to interpolate between */
    vector<vec2> interpolationPoints_velocity; /*!< A vector of vec2 values: interpolationPoints_velocity. The velocity points to interpolate between */
    vector<vec2> interpolationPoints_angularVelocity; /*!< A vector of vec2 values: interpolationPoints_angularVelocity. The angular velocity points to interpolate between */
    vector<vec2> interpolationPoints_color; /*!< A vector of vec2 values: interpolationPoints_color. The color points to interpolate between */
    vector<vec2> interpolationPoints_size; /*!< A vector of vec2 values: interpolationPoints_size. The size points to interpolate between */
   
    Interpolation  interpolation_acceleration; /*!< An Interpolation value: interpolation_acceleration. The acceleration interpolation. */
    Interpolation  interpolation_velocity; /*!< An Interpolation value: interpolation_velocity. The velocity interpolation. */
    Interpolation  interpolation_angularVelocity; /*!< An Interpolation value: interpolation_angularVelocity. The angular velocity acceleration interpolation. */
    Interpolation  interpolation_color; /*!< An Interpolation value: interpolation_color. The color interpolation. */
    Interpolation  interpolation_size; /*!< An Interpolation value: interpolation_size. The size interpolation. */

    //! The ParticleSystem constructor.
        /*!
         * Reserves space in all the arrays, and creates all the initial values
         * \sa startup()
        */
    ParticleSystem()
    :
        interpolation_acceleration(&interpolationPoints_acceleration), 
        interpolation_velocity(&interpolationPoints_velocity),
        interpolation_angularVelocity(&interpolationPoints_angularVelocity),
        interpolation_color(&interpolationPoints_color),
        interpolation_size(&interpolationPoints_size)


    {
        interpolationPoints_acceleration.reserve(4);
        interpolationPoints_velocity.reserve(4);
        interpolationPoints_angularVelocity.reserve(4);
        interpolationPoints_color.reserve(4);
        interpolationPoints_size.reserve(4);
    
        interpolationPoints_acceleration.push_back(vec2(0,0));
        interpolationPoints_velocity.push_back(vec2(0,0));
        interpolationPoints_angularVelocity.push_back(vec2(0,0));
        interpolationPoints_color.push_back(vec2(0,0));
        interpolationPoints_size.push_back(vec2(0,0));
        
        for(int i = 0;i<3;i++){
            interpolationPoints_acceleration.push_back(vec2(1,1));
            interpolationPoints_velocity.push_back(vec2(1,1));
            interpolationPoints_angularVelocity.push_back(vec2(1,1));
            interpolationPoints_color.push_back(vec2(1,1));
            interpolationPoints_size.push_back(vec2(1,1));
        }
    }

    //! The ParticleSystem destructor.
        /*!
         * Shuts down the particle system, and deletes all the mesh and texture pointers
         * \sa shutdown()
        */
    ~ParticleSystem(){
        shutdown();
        delete mesh;
        mesh = nullptr;

    }

    //! A startup method, taking 2-3 arguments.
        /*!
         * Starts the particle system, and initializes all the particles to their initial position
         * \param numParticles an int value. The number of particles in the particle system.
         * \param particleDuration a float value. Each particles duration.
         * \param texture a Texture pointer. The texture of the particle (default is a white texture).
        */
    void startup(int numParticles, float particleDuration, Texture* texture = Texture::getWhiteTexture()){
        currentTime = 0;
        this->particleDuration = particleDuration;
        this->texture = texture;
        
        shader = SRE::Shader::getStandardParticles();

        finalPositions.reserve(numParticles);
        finalColors.reserve(numParticles);
        finalSizes.reserve(numParticles);
        finalRotation.reserve(numParticles);

        positions.reserve(numParticles);
        velocities.reserve(numParticles);
        rotations.reserve(numParticles);
        angularVelocities.reserve(numParticles);
        startColors.reserve(numParticles);
        endColors.reserve(numParticles);
        startSizes.reserve(numParticles);
        endSizes.reserve(numParticles);
        startTimes.reserve(numParticles);


        //zero arrays
        for(int i = 0; i < numParticles; i++){
            finalPositions.push_back(vec3(0,0,-1000));
            finalColors.push_back(vec4(0));
            finalSizes.push_back(0);
            finalRotation.push_back(0);

            positions.push_back(vec3(0));
            velocities.push_back(vec3(0));
            rotations.push_back(0);
            angularVelocities.push_back(0);
            startColors.push_back(vec4(0));
            endColors.push_back(vec4(0));
            startSizes.push_back(0);
            endSizes.push_back(0);
            startTimes.push_back(-999);
        }


        if(mesh == nullptr)
            mesh = new SRE::ParticleMesh(finalPositions, startColors, uvs, uvSize, finalRotation, startSizes);
        else
            mesh->update(finalPositions, finalColors, uvs, uvSize, finalRotation, finalSizes);
    }

    //! A shutdown method.
        /*!
         * Shuts down the particle system, meaning that it clears all the values and paremeters of each particle
         */
    void shutdown(){
        finalPositions.clear();
        finalColors.clear();
        finalSizes.clear();
        finalRotation.clear();

        positions.clear();
        velocities.clear();
        rotations.clear();
        angularVelocities.clear();
        startColors.clear();
        endColors.clear();
        startSizes.clear();
        endSizes.clear();
        startTimes.clear();

        update(0);
    }


    //! An emit method, taking 8 arguments.
        /*!
         * Emits one particle with the properties inputted, has to be called multiple times, if more than one particle is neeeded.
         * \param position a vec3 value. The position of the particle.
         * \param velocity a vec3 value. The velocity of the particle.
         * \param angle a float value. The angle of the particle.
         * \param angularRotation a float value. The angular rotation of the particle.
         * \param color a vec4 value. The start color of the particle.
         * \param size a float value. The start size of the particle.
         * \param endColor a vec4 value. The end color of the particle.
         * \param endSize a float value. The end size of the particle
        */
    void emit(vec3 position, vec3 velocity, float angle, float angularRotation, vec4 color, float size, vec4 endColor, float endSize){
        if(startTimes[particleIndex] + particleDuration < currentTime){
            startTimes[particleIndex] = currentTime;
            positions[particleIndex] = position * Constants::METERS_TO_PIXELS;
            rotations[particleIndex] = angle;
            angularVelocities[particleIndex] = angularRotation;
            velocities[particleIndex] = velocity * Constants::METERS_TO_PIXELS;
            startColors[particleIndex] = color;
            startSizes[particleIndex] = size;
            endColors[particleIndex] = endColor;
            endSizes[particleIndex] = endSize;
            
            particleIndex = (particleIndex + 1) % positions.size();
        }
    }

    //! An update method, taking 1 argument.
        /*!
         * Updates all particles in the particle system, called once per frame.
         * \param dt a float value. The delta time in seconds.
         * \sa draw()
        */
    void update(float dt){

        for (int i = 0; i < positions.size(); i++){
            float t = (currentTime - startTimes[i]) * timeScale;
            if(t > particleDuration){
                finalPositions[i] = vec3(0,0,-1000);
                continue;
            }

            float p = t / particleDuration;
            float it = interpolation_acceleration.interpolate(p).y;
            auto a = acceleration * Constants::METERS_TO_PIXELS * it*it;
            it = interpolation_velocity.interpolate(p).y * particleDuration;
            auto v = velocities[i] * it;
            auto p0 = positions[i];

            finalPositions[i] = a + v + p0;
            finalRotation[i] = rotations[i] + angularVelocities[i] * it;

            it = interpolation_color.interpolate(p).y;
            finalColors[i] = lerpColor(startColors[i], endColors[i], it); 
            it = interpolation_size.interpolate(p).y;
            finalSizes[i] = glm::mix<float>(startSizes[i], endSizes[i], it);
            
        }

        mesh->update(finalPositions, finalColors, uvs, uvSize, finalRotation, finalSizes);

        currentTime += dt;

    }

    //! A draw method.
        /*!
         * Draws all particles in the particle system, called once per frame, after update
         * \sa update()
        */
    void draw(){
        shader->set("tex", texture);
        SRE::SimpleRenderEngine::instance->draw(mesh, glm::mat4(1), shader);

    }



};
}
