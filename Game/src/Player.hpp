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

    bool canJump;
    Sprite* upper;

    Player(vec2 position = vec2(0,0)):GameObject(){
        name = "Player";

        spriteSheet = new SpriteSheet(Resource::getPath("player.json"));
        upper = spriteSheet->getSprite("upper_3", this);
        anim = RenderSystem::getAnim(this, 1.0f);
        anim->makeSequence(spriteSheet, "lower_run");
        sprite = spriteSheet->getSprite("lower_run_3",this);

        b2PolygonShape shape;
        shape.SetAsBox(10.0f * Constants::PIXELS_TO_METERS, 10.0f * Constants::PIXELS_TO_METERS);

        body = Auris::Utilities::BodyStandard::getDynamicBody(&shape, position);

        sprite->scale = vec2(2.0f, 2.0f);

        // Physics properties
        setCollisionEvents(true);
        setFixedRotation(true);
        setGravity(3.0f);
    }

    ~Player(){
        delete spriteSheet;
    }

    float movementSpeed;
    float jumpHeight;
    float maxSpeed;

	Keys keys;

	void Init() {
        movementSpeed = 1000.0f;
        jumpHeight = 2000.0f;
        maxSpeed = 30.0f;
	}

    void Update(float dt){

        if (Input::keyDown(keys.getKey("up")) & canJump) {
            applyForce(up * jumpHeight, true);
            canJump = false;
		}

        if (Input::keyHeld(keys.getKey("down"))) {
            // CROUCH;
		}

        if (Input::keyHeld(keys.getKey("left"))) {
            anim->setSprite(sprite);
            if (getLinearVelocity()[0] > -maxSpeed)
                applyForce(left * movementSpeed, true);
		}

		if (Input::keyHeld(keys.getKey("right"))) {
            anim->setSprite(sprite);
            if (getLinearVelocity()[0] < maxSpeed)
                applyForce(right * movementSpeed, true);
		}
    }

    void OnCollisionEnter(GameObject* other) {
        if (other->name == "Wall")
            canJump = true;
    }

    void OnCollisionExit(GameObject* other) {

    }
};
