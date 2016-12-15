#pragma once

#include "SRE/Texture.hpp"
#include "Auris/Entities/Nuggets/Sprite.hpp"
#include "Auris/Entities/Nuggets/Animation.hpp"
#include "Auris/Systems/RenderSystem.hpp"
#include "Auris/Constants.hpp"
#include "Auris/Systems/Input.hpp"
#include "Auris/Entities/Nuggets/Material.hpp"
#include "Auris/Utilities/SpriteSheet.hpp"
#include "Auris/Utilities/BodyStandard.hpp"
#include "Auris/Utilities/AssetManager.hpp"
#include "Auris/Entities/PhysicsEntity.hpp"
#include "Auris/Action.hpp"

#include "Bullet.hpp"

using namespace std;
using namespace Auris;

class Player : public PhysicsEntity{
public:
    shared_ptr<Animation> anim;
    SpriteSheet* spriteSheet;

    Sprite* lower;
    Sprite* upper;

    bool alive = true;
    bool canJump = true;

    float maxSpeed = 50;
    float jumpHeight = 8000;
    float movementSpeed = 1000;

    int healthPoints = 100;

    int controller;

    Player(vec2 position = vec2(0,0)):PhysicsEntity(){
        type = "Player";

        spriteSheet = AssetManager::getSpriteSheet("player.json");
        upper = spriteSheet->getSprite("upper_3", this);
        anim = RenderSystem::getAnim(this, 1.0f);
        anim->makeSequence(spriteSheet, "lower_run");
        lower = spriteSheet->getSprite("lower_run_3",this);

        upper->offset = vec3(3,8,0);
        lower->offset = vec3(3,4,0);

        b2PolygonShape shape;
        shape.SetAsBox(((lower->getWidth()/3) * Constants::PIXELS_TO_METERS),(upper->getHeight() + lower->getHeight()-9)/3 * Constants::PIXELS_TO_METERS);

        body = Auris::Utilities::BodyStandard::getDynamicBody(&shape,position);


        // Physics properties
        setCollisionEvents(true);
        setFixedRotation(true);
        setGravity(3.0f);
    }

    ~Player(){
        RenderSystem::deleteAnim(anim);
        RenderSystem::deleteSprite(lower);
        RenderSystem::deleteSprite(upper);
    }

    void die() {
        alive = false;
        setFixedRotation(false);
        setGravity(0);
    }

    void setController(int controllerID){
        this->controller = controllerID;
    }

    void init() {
        movementSpeed = 1000.0f;
        jumpHeight = 8000.0f;
        maxSpeed = 30.0f;
	}

    void update(float dt){
        if (alive){
            float leftStickX = Input::getControllerAxisState(controller, SDL_CONTROLLER_AXIS_LEFTX);
            leftStickX = leftStickX/32767;

            float leftStickY = Input::getControllerAxisState(controller, SDL_CONTROLLER_AXIS_LEFTY);
            leftStickY = leftStickY/32767;

            vec2 rightStick = Input::getControllerRightStickState(controller);
            rightStick = vec2(rightStick.x / 32767, rightStick.y / 32767);

            if ((Input::getControllerButtonState(controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER) | Input::getControllerButtonState(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) & canJump) {
                applyForce(vec2(0, 1) * jumpHeight, true);
                canJump = false;
            }

            if (leftStickX < 0)  {
                anim->run(lower, dt);
                if (getLinearVelocity()[0] > -maxSpeed)
                    applyForce(vec2(1, 0) * leftStickX * movementSpeed, true);
//                cout << "Left stick: " << leftStick << endl;
            }

            if (leftStickX > 0)  {
                anim->run(lower, dt);
                if (getLinearVelocity()[0] < maxSpeed)
                    applyForce(vec2(1, 0) * leftStickX * movementSpeed, true);
//                cout << "Left stick: " << leftStick << endl;
            }

            if (Input::keyDown(Auris::Action::down)) {

            }
        }
    }

    void OnCollisionEnter(PhysicsEntity* other) {
        if (other->type == "Wall")
            canJump = true;

        if (other->type == "Bullet") {
            healthPoints -= ((Bullet*)other)->damage;
            other->setGravity(3);
            other->setFixedRotation(true);
        }
    }

    void OnCollisionExit(PhysicsEntity* other) {

    }

    void inspectorImGui(){
        PhysicsEntity::inspectorImGui();
        ImGui::Separator();

        ImGui::Checkbox("Is Alive", &alive);
        ImGui::Checkbox("Can Jump", &canJump);

        ImGui::DragInt("Health Points", &healthPoints);

        ImGui::DragFloat("MaxSpeed", &maxSpeed);
        ImGui::DragFloat("jumpHeight", &jumpHeight);
        ImGui::DragFloat("movementSpeed", &movementSpeed);

    }

};
