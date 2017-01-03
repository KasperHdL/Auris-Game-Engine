#pragma once

#include "SRE/Texture.hpp"

#include "Auris/Auris.hpp"

#include "Crosshair.hpp"
#include "Bullet.hpp"
#include "Grenade.hpp"

#include <glm/gtc/random.hpp>

using namespace std;
using namespace Auris;

class GrenadeUI : public Entity{
public:

    Sprite* sprite;
    vec2 scale;
    vec2 position;

    GrenadeUI(vec2 position,vec2 scale, vec4 color){
        this->scale = scale;
        this->position = position;
        transform->setPosition(position);
        transform->setScale(scale);

        sprite = RenderSystem::getSprite(this, AssetManager::getTexture("grenade.png"));

        sprite->material.color = color;

    }

    void setScale(float amount){
        vec2 temp = vec2(scale.x*amount,scale.y);
        transform->setPosition(vec2(position.x+((temp.x-scale.x))*Constants::PIXELS_TO_METERS,position.y));
        transform->setScale(temp);
    }
};


class Bar : public Entity{
public:

    Sprite* sprite;
    vec2 scale;
    vec2 position;

    Bar(vec2 position,vec2 scale, vec4 color){
        this->scale = scale;
        this->position = position;
        transform->setPosition(position);
        transform->setScale(scale);

        sprite = RenderSystem::getSprite(this);

        sprite->material.color = color;

    }

    void setScale(float amount){
        vec2 temp = vec2(scale.x*amount,scale.y);
        transform->setPosition(vec2(position.x+((temp.x-scale.x))*Constants::PIXELS_TO_METERS,position.y));
        transform->setScale(temp);
    }

};

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

    Bar* healthFrontBar;
    Bar* healthBackbar;
    Bar* fuelFrontBar;
    Bar* fuelBackbar;
    Bar* respawnBar;

    GrenadeUI* grenadeUI;

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
    int groupIndex;

    vec4 playerColor;
    Player(vec2 position = vec2(0,0), vec4 color = vec4(1,1,1,1), int index = 0) : PhysicsEntity(){
        type = "Player";
        playerColor = color;
        groupIndex = -(index+1);

        spriteSheet = AssetManager::getSpriteSheet("player.json", true);

        lower = RenderSystem::getSprite(this);
        spriteSheet->setSpriteTo(lower, "lower_run_3");

        upper = RenderSystem::getSprite(this);
        spriteSheet->setSpriteTo(upper, "upper_3", true);


        healthFrontBar = new Bar(vec2(0,3.3f),vec2(15,1),vec4(1,0,0,1));
        addChild(healthFrontBar);
        healthBackbar = new Bar(vec2(0,3.3f),vec2(15,1),vec4(1,0,0,0.5f));
        addChild(healthBackbar);

        fuelFrontBar = new Bar(vec2(0,3.1f),vec2(15,1),vec4(0,1,1,1));
        addChild(fuelFrontBar);
        fuelBackbar = new Bar(vec2(0,3.1f),vec2(15,1),vec4(0,1,1,0.5f));
        addChild(fuelBackbar);

        respawnBar = new Bar(vec2(0,0),vec2(10,1),vec4(1,1,1,1));
        addChild(respawnBar);
        respawnBar->setScale(0);

        grenadeUI = new GrenadeUI(vec2(3,-2),vec2(1.5f,1.5f),vec4(1,1,1,0.75f));

        anim = RenderSystem::getAnim(this, 1.0f);
        anim->makeSequence(spriteSheet, "lower_run", true);

        upper->offset = vec3(3,6,0) * Constants::PIXELS_TO_METERS;
        lower->offset = vec3(3,4,0) * Constants::PIXELS_TO_METERS;

        b2PolygonShape shape;
        //shape.m_p.Set(0,0);
        //shape.m_radius = 2;
        shape.SetAsBox(((lower->getWidth()/3) * Constants::PIXELS_TO_METERS),(upper->getHeight() + lower->getHeight()-9)/3 * Constants::PIXELS_TO_METERS);

        b2Filter filter;
        filter.groupIndex = groupIndex;

        body = Auris::Utilities::BodyStandard::getDynamicBody(&shape, false, 1.0f, 20.0f, 0.0f, &filter);

        // Physics properties
        setCollisionEvents(true);
        setPosition(position);
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
        audioPlayer = (AudioPlayer*) Game::instance->addEntity(make_shared<AudioPlayer>(Game::instance->camera, 5));
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
        crosshair->addChild(grenadeUI);

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
        healthFrontBar->setScale(0);
        fuelFrontBar->setScale(0);
        healthBackbar->setScale(0);
        fuelBackbar->setScale(0);
        //Game::instance->destroyEntity(crosshair);
    }

    void respawn(){
        alive = true;
        healthPoints = 100;
        //setRotation(0);
        setFixedRotation(true);
        setGravity(1);
        crosshair->transform->setScale(vec2(0.5f,0.5f));
        healthBackbar->setScale(1);
        fuelBackbar->setScale(1);

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
        vec2 pos = transform->getPosition();
        auto bullet = (Bullet*) Game::instance->addEntity(make_shared<Bullet>(pos + vec2(3,6)*Constants::PIXELS_TO_METERS, rotation, vec2(direction.x, -direction.y), this, groupIndex));
        bullet->player = this;
    }

    void throwGrenade(vec2 direction) {
        vec2 pos = transform->getPosition();
        auto grenade = (Grenade*) Game::instance->addEntity(make_shared<Grenade>(pos + vec2(3,6)*Constants::PIXELS_TO_METERS, vec2(direction.x,-direction.y), grenadeForce, groupIndex));
        grenadeForce = 1;
    }

    float map (float value, float from1, float to1, float from2, float to2) {
        return (value - from1) / (to1 - from1) * (to2 - from2) + from2;
    }

    void update(float deltaTime){
        this->deltaTime = deltaTime;
        pistolReload.update(deltaTime);
        grenadeReload.update(deltaTime);
        respawnTime = respawnTimer.getCurrentTime();
        if (alive){
            healthFrontBar->setScale((float)healthPoints/100);
            fuelFrontBar->setScale(map(fuel,0,2,0,1));
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
            }
            if ((Input::getControllerButtonState(controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER))) {
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

            if (glm::length<float>(rightStick) > .1f) {
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
            healthPoints = 0;
            respawnTimer.update(deltaTime);
            respawnBar->setScale(map((float)respawnTimer.getCurrentTime(),0,10,1,0));
        }

        if(respawnTimer.time()){
            respawn();
        }

        if (pistolReload.time())
            canFire = true;

        if (grenadeReload.time()){
            grenadeUI->setScale(1);
            canThrow = true;
        }else{
            grenadeUI->setScale(0);
        }
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
            }
        }

        if (other->type == "Explosion") {
            Grenade* grenade = (Grenade*) other;
            vec2 delta = transform->getGlobalPosition() - grenade->transform->getGlobalPosition();
            float absDelta = abs(delta.x + delta.y);
            float distance = grenade->explosionRadius / (absDelta/4);

            if(absDelta < 25)
                healthPoints -= (int)grenade->damage*((25.0f-absDelta)/25.0f);
            applyForce(normalize(delta) * distance * jumpHeight, true);
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
