#pragma once

#include "Auris/GameObjects/GameObject.hpp"
#include "Auris/GameObjects/Components/SpriteSheet.hpp"
#include "Auris/Constants.hpp"
#include "Auris/Utilities/Resource.hpp"
#include "Auris/Utilities/BodyStandard.hpp"

using namespace Constants;

class Wall : public GameObject{
public:
    shared_ptr<Animation> anim;
    Wall(vec2 position = vec2(0,0)):GameObject() {
        name = "Wall";

        SpriteSheet* ss = new SpriteSheet(Resource::getPath("MarioPacked.json"));

        sprite = ss->getSprite("brick",this);

        anim = RenderSystem::getAnim(this, 4.0f);
        anim->setSheet(ss);

        b2PolygonShape shape; 
        shape.SetAsBox(30.0f * PIXELS_TO_METERS, 30.0f * PIXELS_TO_METERS); 

        body = Auris::Utilities::BodyStandard::getStaticBody(&shape, position);

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
