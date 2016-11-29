#pragma once

#include "Auris/GameObjects/GameObject.hpp"
#include "Auris/GameObjects/Components/SpriteSheet.hpp"
#include "Auris/Constants.hpp"
#include "Auris/Utility/Resource.hpp"
#include "Auris/Utility/BodyStandard.hpp"

using namespace Constants;

class Wall : public GameObject{
public:
    shared_ptr<Animation> anim;
    Wall(vec2 position = vec2(0,0)):GameObject() {
        name = "Wall";

        SpriteSheet* ss = new SpriteSheet(SRE::Texture::createFromFile(Resource::getPath("MarioPacked.png").c_str(),false),Resource::getPath("MarioPacked.json"));

        sprite = ss->getSprite("brick",this);

        anim = RenderSystem::getAnim(this, 4.0f);
        anim->setSheet(ss);

        b2PolygonShape shape; 
        shape.SetAsBox(30.0f * PIXELS_TO_METERS, 30.0f * PIXELS_TO_METERS); 

        body = Utility::BodyStandard::getStaticBody(&shape, position);

        enableCollisionEvents();
    }

    ~Wall(){
        RenderSystem::deleteAnim(anim);
    }

    void Update(float dt){
        anim->setSprite(sprite);
    }

    void OnCollisionEnter(GameObject* other) {
        cout << name << " hit " << other->name << endl;
    }

    void OnCollisionExit(GameObject* other) {
        cout << name << " is longer colliding with " << other->name << endl;
    }

    void OnCollisionStay(GameObject* other) {
        cout << name << " IS STILL TOUCHING " << other->name << endl;
    }
};
