#pragma once

#include "Auris/GameObjects/GameObject.hpp"
#include "Auris/GameObjects/Components/SpriteSheet.hpp"
#include "Auris/Constants.hpp"
#include "Auris/Utilities/Resource.hpp"
#include "Auris/Utilities/BodyStandard.hpp"

using namespace Auris;
using namespace Constants;

class Wall : public GameObject{
public:
    Wall(vec2 position = vec2(0,0)):GameObject() {
        name = "Wall";    

        SpriteSheet* spriteSheet = new SpriteSheet(Resource::getPath("MarioPacked.json"));

        sprite = spriteSheet->getSprite("brick",this);

        b2PolygonShape shape; 
        shape.SetAsBox(20.0f * Constants::PIXELS_TO_METERS, 20.0f * PIXELS_TO_METERS);

        body = Auris::Utilities::BodyStandard::getStaticBody(&shape, position, 30.0f);

        // Physics properties
        setCollisionEvents(true);
    }

    ~Wall(){

    }

    void Update(float dt){

    }

    void OnCollisionEnter(GameObject* other) {

    }

    void OnCollisionExit(GameObject* other) {

    }

    void OnCollisionStay(GameObject* other) {

    }
};
