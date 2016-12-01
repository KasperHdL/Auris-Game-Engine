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

    Player(vec2 position = vec2(0,0)):GameObject(){
        name = "Player";

        SpriteSheet* ss = new SpriteSheet(SRE::Texture::createFromFile(Resource::getPath("MarioPacked.png").c_str(),false),Resource::getPath("MarioPacked.json"));

        sprite = ss->getSprite("mario_0",this);

        b2PolygonShape shape;
        shape.SetAsBox(10.0f * Constants::PIXELS_TO_METERS, 10.0f * Constants::PIXELS_TO_METERS);

        body = Auris::Utilities::BodyStandard::getDynamicBody(&shape, position);

        // Physics properties
        setCollisionEvents(true);
        setFixedRotation(true);
        setGravity(3.0f);
        setFriction(2.0f);
    }

    ~Player(){
        delete spriteSheet;
    }

    float movementSpeed;
    float jumpHeight;
    float maxSpeed;

	Keys keys;

	void Init() {
        movementSpeed = 300.0f;
        jumpHeight = 2000.0f;
        maxSpeed = 50.0f;
	}

    void Update(float dt){
        if (Input::keyHeld(keys.getKey("up")) & canJump) {
            applyForce(up * jumpHeight, true);
            canJump = false;
		}
		if (Input::keyHeld(keys.getKey("down"))) {
            // CROUCH;
		}
		if (Input::keyHeld(keys.getKey("left"))) {
            if (getLinearVelocity()[0] > -maxSpeed)
                applyForce(left * movementSpeed, true);
		}
		if (Input::keyHeld(keys.getKey("right"))) {
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
