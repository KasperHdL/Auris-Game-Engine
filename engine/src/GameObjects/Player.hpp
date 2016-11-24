#pragma once

#include "GameObject.hpp"
#include "Components/Sprite.hpp"
#include "Components/Animation.hpp"

#include "../Systems/RenderSystem.hpp"
#include "../Constants.hpp"
#include <iostream>
#include "../Systems/Input.hpp"
#include "Components/Material.hpp"

#include "Components/SpriteSheet.hpp"
#include "../Utility/Resource.hpp"
#include "../Utility/BodyStandard.hpp"


using namespace std;
class Player : public GameObject{
    public:
	shared_ptr<Animation> anim;

    Player(vec2 position = vec2(0,0)):GameObject(){
        name = "Player";

        SpriteSheet* ss = new SpriteSheet(SRE::Texture::createFromFile(Resource::getPath("MarioPacked.png").c_str(),false),Resource::getPath("MarioPacked.json"));

        sprite = ss->getSprite("mario_10",this);

        auto a = RenderSystem::getAnim(this, 4.0f);
        a->setSheet(ss);

		anim = a;

        b2CircleShape shape;
        shape.m_radius = (19 * Constants::PIXELS_TO_METERS);
        body = Utility::BodyStandard::getDynamicBody(&shape, position);

        enableCollisionEvents();
    }

	float force;
	Keys keys;
	void Init() {
		force = 10000.0f;
	}

    void Update(float dt){
        anim->setSprite(sprite);
		if (Input::keyHeld(keys.getKey("up"))) {
			body->ApplyForceToCenter(b2Vec2(0, force), true);
		}
		if (Input::keyHeld(keys.getKey("down"))) {
			body->ApplyForceToCenter(b2Vec2(0, -force), true);
		}
		if (Input::keyHeld(keys.getKey("left"))) {
			body->ApplyForceToCenter(b2Vec2(-force, 0), true);
		}
		if (Input::keyHeld(keys.getKey("right"))) {
			body->ApplyForceToCenter(b2Vec2(force, 0), true);
		}
    }

    void OnCollisionEnter(GameObject* other) {
        cout << name << " hit " << other->name << endl;
    }

    void OnCollisionExit(GameObject* other) {
        cout << name << " is longer colliding with " << other->name << endl;
    }
};
