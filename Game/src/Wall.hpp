#pragma once

#include "Auris/Entities/PhysicsEntity.hpp"
#include "Auris/Entities/Nuggets/Sprite.hpp"
#include "Auris/Entities/Nuggets/SpriteSheet.hpp"
#include "Auris/Constants.hpp"
#include "Auris/Utilities/Resource.hpp"
#include "Auris/Utilities/BodyStandard.hpp"

using namespace Constants;

class Wall : public PhysicsEntity{
public:

    Sprite* sprite;

    Wall(vec2 position = vec2(0,0)):PhysicsEntity() {
        name = "Wall";    

        SpriteSheet* ss = new SpriteSheet(Resource::getPath("MarioPacked.json"));

        sprite = ss->getSprite("brick",this);

        b2PolygonShape shape; 
        shape.SetAsBox(sprite->getWidth() * PIXELS_TO_METERS/2, sprite->getHeight() * PIXELS_TO_METERS/2); 

        body = Auris::Utilities::BodyStandard::getStaticBody(&shape, position, 30.0f);

        setCollisionEvents(true);
    }

    ~Wall(){
        Auris::RenderSystem::deleteSprite(sprite);
    }

    void Update(float dt){
        //anim->setSprite(sprite);
    }

    void OnCollisionEnter(PhysicsEntity* other) {

    }

    void OnCollisionExit(PhysicsEntity* other) {

    }

    void OnCollisionStay(PhysicsEntity* other) {

    }
};
