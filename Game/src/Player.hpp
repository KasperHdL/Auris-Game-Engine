#pragma once

#include "SRE/Texture.hpp"
#include "Auris/GameObjects/Components/Sprite.hpp"
#include "Auris/GameObjects/Components/Animation.hpp"
#include "Auris/Systems/RenderSystem.hpp"
#include "Auris/Constants.hpp"
#include "Auris/Systems/Input.hpp"
#include "Auris/GameObjects/Components/Material.hpp"
#include "Auris/GameObjects/Components/SpriteSheet.hpp"
#include "Auris/Utilities/Resource.hpp"
#include "Auris/Utilities/BodyStandard.hpp"

using namespace std;
using namespace Auris;
class Player : public GameObject{
    public:
    shared_ptr<Animation> anim;
    SpriteSheet* spriteSheet;

    Player(vec2 position = vec2(0,0)):GameObject(){
        name = "Player";

        b2PolygonShape shape;
        shape.SetAsBox(30.0f * PIXELS_TO_METERS, 30.0f * PIXELS_TO_METERS);

        body = Auris::Utilities::BodyStandard::getDynamicBody(&shape, position);

        enableCollisionEvents();
    }

    ~Player(){
        delete spriteSheet;
    }

    float movementSpeed;
    float jumpHeight;

	Keys keys;

	void Init() {
        movementSpeed = 10000.0f;
        jumpHeight = 10000.0f;
	}

    void Update(float dt){
        anim->setSprite(sprite);
		if (Input::keyHeld(keys.getKey("up"))) {
            body->ApplyLinearImpulse(b2Vec2(0, jumpHeight), b2vec2(0, 0));
		}
		if (Input::keyHeld(keys.getKey("down"))) {
            // CROUCH;
		}
		if (Input::keyHeld(keys.getKey("left"))) {
            body->ApplyForceToCenter(b2Vec2(-movementSpeed, 0), true);
		}
		if (Input::keyHeld(keys.getKey("right"))) {
            body->ApplyForceToCenter(b2Vec2(movementSpeed, 0), true);
		}
    }

    void OnCollisionEnter(GameObject* other) {

    }

    void OnCollisionExit(GameObject* other) {

    }
};
