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
#include "Crosshair.hpp"
#include "Auris/Utilities/AudioPlayer.hpp"
#include "Auris/Utilities/Timer.hpp"
#include "Bullet.hpp"
#include "Grenade.hpp"

#include <glm/gtc/random.hpp>

using namespace std;
using namespace Auris;

class Player : public PhysicsEntity{
public:
    shared_ptr<Animation> anim;
    SpriteSheet* spriteSheet;

    Sprite* lower;
    Sprite* upper;

    Crosshair* crosshair;
    AudioPlayer* audioPlayer;

    Timer pistolReload;
    Timer grenadeReload;
    Timer respawnTimer;
    int respawnTime;
    int respawnPoint;

    float fuel = 2;

    bool alive = true;
    int numJumps = 0;
    bool aiming = false;
    bool canFire = true;
    bool canThrow = true;
    bool charging = false;

    vec2 aimDirection;

    float grenadeForce = 1;
    float maxSpeed = 50;
    float airHandicap = 1;
    float jumpHeight = 4000;
    float movementSpeed = 1000;
    float crosshairOffset = 10;
    float bulletOffset = 5;
    float grenadeOffset = 5;
    float aimRotation;
    float deltaTime;

    int healthPoints = 100;
    int pistolShot;
    int controller;

    vec4 playerColor;
    Player(vec2 position = vec2(0,0), vec4 color = vec4(1,1,1,1)) : PhysicsEntity(){
        type = "Player";
        playerColor = color;

        spriteSheet = AssetManager::getSpriteSheet("player.json", true);

        upper = RenderSystem::getSprite(this);
        spriteSheet->setSpriteTo(upper, "upper_3", true);

        lower = RenderSystem::getSprite(this);
        spriteSheet->setSpriteTo(lower, "lower_run_3");

        anim = RenderSystem::getAnim(this, 1.0f);
        anim->makeSequence(spriteSheet, "lower_run", true);

        upper->offset = vec3(3,8,0);
        lower->offset = vec3(3,4,0);

        b2PolygonShape shape;
        //shape.m_p.Set(0,0);
        //shape.m_radius = 2;
        shape.SetAsBox(((lower->getWidth()/3) * Constants::PIXELS_TO_METERS),(upper->getHeight() + lower->getHeight()-9)/3 * Constants::PIXELS_TO_METERS);

        body = Auris::Utilities::BodyStandard::getDynamicBody(&shape,position);

        // Physics properties
        setCollisionEvents(true);
        setFixedRotation(true);
        setGravity(3.0f);
        body->SetSleepingAllowed(false);
    }

    ~Player(){
        RenderSystem::deleteAnim(anim);
        RenderSystem::deleteSprite(lower);
        RenderSystem::deleteSprite(upper);
    }

    void init() {
        audioPlayer = (AudioPlayer*) Game::instance->addEntity(make_shared<AudioPlayer>(Game::instance->camera, this, 5));
        audioPlayer->name = audioPlayer->type + to_string(controller);

        crosshair = (Crosshair*) Game::instance->addEntity(make_shared<Crosshair>());
        crosshair->name = crosshair->type + to_string(controller);

        pistolShot = audioPlayer->addSound(AssetManager::getSound("pistolShot.wav"));

        pistolReload.start(0.2f);
        grenadeReload.start(5.0f);
        respawnTimer.start(10.0f);

        aimDirection = vec2(1, 0);

        addChild(audioPlayer);
        addChild(crosshair);

        respawnPoint = glm::linearRand<int>(0,3);
        cout << respawnPoint << endl;
        lower->material.color = playerColor;
        upper->material.color = playerColor;

    }

    void setController(int controllerID){
        controller = controllerID;
    }

    void die() {
        alive = false;
        healthPoints = 0;
        setFixedRotation(false);
        setGravity(0);
        crosshair->transform->setScale(vec2(0,0));
        respawnTimer.reset();
        //Game::instance->destroyEntity(crosshair);
    }

    void respawn(){
        alive = true;
        healthPoints = 100;
        //setRotation(0);
        setFixedRotation(true);
        setGravity(1);
        crosshair->transform->setScale(vec2(0.5f,0.5f));

        //Bow before Mathias' cancer vector
        vec2 pos = respawnPoint == 0 ? vec2(-40, -10) :
                respawnPoint == 1 ? vec2(-50, 30) :
                respawnPoint == 2 ? vec2(40, -10) :
                respawnPoint == 3 ? vec2(50, 30):
                vec2(0, 0);
        respawnPoint++;
        if(respawnPoint>3)
            respawnPoint=0;
        body->SetTransform(Convert::toB2(pos),0.0f);
        respawnTimer.reset();
    }

    void fireBullet(float rotation, vec2 direction) {
        auto bullet = (Bullet*) Game::instance->addEntity(make_shared<Bullet>(vec2(transform->getPosition().x+direction.x*bulletOffset, transform->getPosition().y-direction.y*bulletOffset), rotation, vec2(direction.x, -direction.y), this));
        bullet->player = this;
    }

    void throwGrenade(vec2 direction) {
        auto grenade = (Grenade*) Game::instance->addEntity(make_shared<Grenade>(vec2(transform->getPosition().x+direction.x*grenadeOffset, transform->getPosition().y-direction.y*grenadeOffset), vec2(direction.x, -direction.y), grenadeForce));
        grenadeForce = 1;
    }

    void update(float deltaTime){
        this->deltaTime = deltaTime;
        pistolReload.update(deltaTime);
        grenadeReload.update(deltaTime);
        respawnTime = respawnTimer.getCurrentTime();
        if (alive){
            float leftStickX = Input::getControllerAxisState(controller, SDL_CONTROLLER_AXIS_LEFTX);
            leftStickX = leftStickX/32767;

            float leftStickY = Input::getControllerAxisState(controller, SDL_CONTROLLER_AXIS_LEFTY);
            leftStickY = leftStickY/32767;

            vec2 rightStick = Input::getControllerRightStickState(controller);
            rightStick = vec2(rightStick.x / 32767, rightStick.y / 32767);

            int rightTrigger = Input::getControllerAxisState(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);

            if ((Input::getControllerButtonState(controller, SDL_CONTROLLER_BUTTON_A)) && numJumps > 0) {
                applyForce(vec2(0, 1) * jumpHeight, true);
                numJumps --;
            }else if ((Input::getControllerButtonState(controller, SDL_CONTROLLER_BUTTON_A)) && numJumps == 0) {
                if(fuel>0){
                applyForce(vec2(0, 1) * (jumpHeight+7000.0f), false);
                fuel-=deltaTime;
                }
            }else if(fuel<2){
                fuel+=deltaTime;
            }

            if (leftStickX < 0)  {
                anim->run(lower, abs(leftStickX)*deltaTime, true);
                //transform->scale = vec2(-1, 1);
                if (getLinearVelocity()[0] > -maxSpeed)
                    applyForce(vec2(1, 0) * leftStickX * movementSpeed * airHandicap, true);
            }

            if (leftStickX > 0)  {
                anim->run(lower, abs(leftStickX)*deltaTime, false);
                //transform->scale = vec2(1, 1);
                if (getLinearVelocity()[0] < maxSpeed)
                    applyForce(vec2(1, 0) * leftStickX * movementSpeed * airHandicap, true);
            }

            if (rightStick != vec2(0, 0)) {
                aimDirection = rightStick;

                aiming = true;
            }
            else {
                aiming = false;
            }

            aimRotation = (float)(atan2(aimDirection.x, -aimDirection.y));
            vec2 normalized = normalize(aimDirection);

            if (aiming) {
                float divider = 180/7;
                float absDir = abs(degrees(aimRotation));
                int aim = absDir > 180-divider ? 6 :
                    absDir > 180-divider*2 ? 5 :
                    absDir > 180-divider*3 ? 4 :
                    absDir > 180-divider*4 ? 3 :
                    absDir > 180-divider*5 ? 2 :
                    absDir > 180-divider*6 ? 1 : 0;

                string sprite   = "upper_" + to_string(aim);
                spriteSheet->setSpriteTo(upper, sprite, normalized.x < 0);
                upper->material.color = playerColor;
            }

            if (rightTrigger > 16000) {
                if (canFire) {
                    audioPlayer->playSound(pistolShot);
                    fireBullet(-aimRotation-(radians(90.0f)), normalized);
                    canFire = false;
                    pistolReload.reset();
                }
            }

            if (Input::getControllerButtonState(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) {
                if (canThrow) {
                    charging = true;
                }

                if (charging) {
                    grenadeForce += deltaTime;
                }
            }
            else if (charging) {
                charging = false;
                canThrow = false;
                grenadeReload.reset();
                throwGrenade(normalized);
            }

            if (healthPoints <= 0) {
                die();
            }

            crosshair->transform->setPosition(vec2(normalized.x*crosshairOffset, -normalized.y*crosshairOffset));
        }else{
            respawnTimer.update(deltaTime);
        }

        if(respawnTimer.time()){
            respawn();
        }

        if (pistolReload.time())
            canFire = true;

        if (grenadeReload.time())
            canThrow = true;
    }

    void OnCollisionEnter(PhysicsEntity* other) {
        if(other->type!="Roof"){
          airHandicap = 1;
        }

        if (other->type == "Floor"){
            numJumps = 1;
        }

        if (other->type == "Bullet") {
            Bullet* bullet = (Bullet*) other;
            if (bullet->player != this) {
                healthPoints -= bullet->damage;
                other->setGravity(3);
                other->setFixedRotation(false);
                other->setBullet(false);
                Game::instance->destroyEntity(other);
            }
        }

        if (other->type == "Explosion") {
            Grenade* grenade = (Grenade*) other;
            vec2 delta = transform->getGlobalPosition() - grenade->transform->getGlobalPosition();
            float distance = abs(delta.x + delta.y)/grenade->explosionRadius;

            healthPoints -= (int)grenade->damage*(1-distance);
            applyForce(delta*jumpHeight*distance, true);
        }
    }

    void OnCollisionExit(PhysicsEntity* other) {
        airHandicap = 0.1f;
        //if (other->type == "jumpable")
        //   canJump = false;
    }

    void inspectorImGui(){
        PhysicsEntity::inspectorImGui();
        ImGui::Separator();

        ImGui::Checkbox("Is Alive", &alive);
        ImGui::DragInt("Number of jumps", &numJumps);

        ImGui::DragInt("Respawn time",&respawnTime);

        ImGui::DragFloat("Fuel", &fuel);

        ImGui::DragFloat("Airhandi", &airHandicap);

        ImGui::DragInt("Health Points", &healthPoints);

        ImGui::DragFloat("MaxSpeed", &maxSpeed);
        ImGui::DragFloat("jumpHeight", &jumpHeight);
        ImGui::DragFloat("movementSpeed", &movementSpeed);

    }
};
