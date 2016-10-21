#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>
#include <vector>
#include <SRE/SimpleRenderEngine.hpp>
#include <SRE/Mesh.hpp>
#include <SRE/Shader.hpp>

using namespace glm;
using namespace std;

class Component;
class CTransform;
class CSprite;
class CSpriteTexture;
class CDynamicBody;
class CFixedBody;

class GameObject{
public:

    shared_ptr<CTransform> transform;
    shared_ptr<CSprite> sprite;

    vector<shared_ptr<Component>> components;

    GameObject();

    void update(float dt);
    void draw();

    bool removeComponent(shared_ptr<Component> ptr);

    shared_ptr<CSprite> addComponentSprite();
    shared_ptr<CSpriteTexture> addComponentSpriteTexture();

    template<typename C>
    shared_ptr<C> addComponent(){
        C* c = new C(this);
        auto res = shared_ptr<C>(c);
        components.push_back(res);
        return res;
    }

    template<typename C>
    shared_ptr<C> getComponent(){
        if(dynamic_pointer_cast<C>(sprite) != nullptr)
            return sprite;

        for(auto c : components){
            auto castPtr = dynamic_pointer_cast<C>(c);
            if(castPtr != nullptr){
                return castPtr;
            }
        }
        //not ofund
        return nullptr;

    }

private:


};
