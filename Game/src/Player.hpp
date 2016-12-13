#pragma once

#include "SRE/Texture.hpp"
#include "Auris/Entities/Nuggets/Sprite.hpp"
#include "Auris/Entities/Nuggets/Animation.hpp"
#include "Auris/Systems/RenderSystem.hpp"
#include "Auris/Constants.hpp"
#include "Auris/Systems/Input.hpp"
#include "Auris/Entities/Nuggets/Material.hpp"
#include "Auris/Entities/Nuggets/SpriteSheet.hpp"
#include "Auris/Utilities/Resource.hpp"
#include "Auris/Utilities/BodyStandard.hpp"

using namespace std;
using namespace Auris;
class Player : public PhysicsEntity{
    public:
    shared_ptr<Animation> anim;
    SpriteSheet* spriteSheet;

    bool canJump;
    Sprite* sprite;
    Sprite* upper;

    Player(vec2 position = vec2(0,0)):PhysicsEntity(){
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
        RenderSystem::deleteAnim(anim);
        RenderSystem::deleteSprite(sprite);
        RenderSystem::deleteSprite(upper);
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
            applyForce(glm::vec3(0,1,0) * jumpHeight, true);
            canJump = false;
		}

        if (Input::keyHeld(keys.getKey("down"))) {
            // CROUCH;
		}

        if (Input::keyHeld(keys.getKey("left"))) {
            anim->run(sprite, dt);
            if (getLinearVelocity()[0] > -maxSpeed)
                applyForce(glm::vec3(-1,0,0) * movementSpeed, true);
		}

		if (Input::keyHeld(keys.getKey("right"))) {
            anim->run(sprite, dt);
            if (getLinearVelocity()[0] < maxSpeed)
                applyForce(glm::vec3(1,0,0) * movementSpeed, true);
		}
    }

    void OnCollisionEnter(Entity* other) {
        if (other->name == "Wall")
            canJump = true;
    }

    void OnCollisionExit(Entity* other) {

    }
};
