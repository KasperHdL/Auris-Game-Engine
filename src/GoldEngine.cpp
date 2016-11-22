#include "GoldEngine.hpp"

using namespace SRE;
using namespace glm;

DebugDraw debugDraw;


void GoldEngine::startup(SDL_Window* window){
    ImGui_SRE_Init(window);

    renderSystem.startup(64);


    world = new b2World(toB2(glm::vec2(0,0)));
    world->SetContactListener(this);

    world->SetDebugDraw(&debugDraw);
    debugDraw.SetFlags(b2Draw::e_shapeBit);

    auto sre = SimpleRenderEngine::instance;
    sre->getCamera()->setWindowCoordinates();
    sre->setLight(2, Light(LightType::Directional,{0,0,0},{1,1,1},{1,1,1},0));

    gameObjects.push_back(make_shared<Player>(world,vec2(10,10)));
    gameObjects.push_back(make_shared<Player>(world));

	//Run init on all gameobjects
	for(auto& el: gameObjects)
            el->Init();

}

void GoldEngine::shutdown(){
    renderSystem.shutdown();

    delete world;
    world = nullptr;

    gameObjects.clear();
}


void GoldEngine::run(SDL_Window* window){
    // delta time from http://gamedev.stackexchange.com/a/110831
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    quit = 0;
    float deltaTimeSec = 0;
    auto sre = SimpleRenderEngine::instance;

	//Initialize MemoryLeakDetector
	memLeakDet = MemoryLeakDetector();

    //DEBUG INFORMATION TODO should be ignored on release build

    Keys keys;
 
    keys.setKey("debug", SDL_SCANCODE_F2);
    keys.setKey("pause", SDL_SCANCODE_F3);
    keys.setKey("stepOne", SDL_SCANCODE_F4);
    keys.setKey("playOnHold", SDL_SCANCODE_F5);


    keys.setKey("arrow_up", SDL_SCANCODE_UP);
    keys.setKey("arrow_down", SDL_SCANCODE_DOWN);
    keys.setKey("arrow_left", SDL_SCANCODE_LEFT);
    keys.setKey("arrow_right", SDL_SCANCODE_RIGHT);
    

   
    int arrIndex = 0;
    const int arrSize = 600;
    float arr_deltaTime[arrSize] = {};
    float max_deltaTime = 0;

    
    float arr_virtMem[arrSize] = {};
    float max_virtMem = 0;

    float arr_physMem[arrSize] = {};
    float max_physMem = 0;

    int max_renderSprites = 0;

    bool toggle_goInspector = false;
    bool toggle_showcasePanel = false;
    bool toggle_cameraControls = false;

    while (quit == 0){
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        deltaTimeSec = clamp(((NOW - LAST) / (float)SDL_GetPerformanceFrequency() ),0.0f,1.0f);
		
        sre->clearScreen(vec4(0,0,0,1));

        Input::update();
        HandleSDLEvents();

        if (Input::keyDown(keys.getKey("quit"))) {
			quit = 1;
		}

        if(Input::keyDown(keys.getKey("debug"))){
            debug = !debug;

            if(debug == false){
                ImGui_SRE_NewFrame(window);
                ImGui::Render();
            }
        }

        if(Input::keyDown(keys.getKey("pause"))){
            pause = !pause;
        }

        bool runOneStep = false;
        if(Input::keyDown(keys.getKey("stepOne")) || Input::keyHeld(keys.getKey("playOnHold"))){
            runOneStep = true;
            pause = true;
        }

        if(debug){
            
            ImGui_SRE_NewFrame(window);

            ImGui::Checkbox("Debug(F2)", &debug);
            ImGui::SameLine();
            ImGui::Checkbox("Pause(F3)", &pause);
            if(ImGui::Button("Step One Frame(F4)")){
                runOneStep = true;
                pause = true;
            }
            ImGui::SameLine();
            ImGui::Text("Play on Hold(F5)");
//          ImGui::Checkbox("Toggle Camera Controls(Arrow Keys)",&toggle_cameraControls);

            ImGui::Separator();
            ImGui::Checkbox("Toggle GO Inspector",&toggle_goInspector);
            if(ImGui::Checkbox("Toggle Showcases Panel",&toggle_showcasePanel)){
                if(toggle_showcasePanel){
                    //toggled on
                    showcasePanel.startup();
                }else{
                    //toggled off
                    showcasePanel.shutdown();
                }

            }
            ImGui::Separator();

            arr_deltaTime[arrIndex] = deltaTimeSec;
            arr_physMem[arrIndex] = memLeakDet.getPhysMemUsedByMe();
            arr_virtMem[arrIndex] = memLeakDet.getVirtMemUsedByMe();

            if(renderSystem.spritePool.count > max_renderSprites)
                max_renderSprites = renderSystem.spritePool.count;

            ImGui::PlotLines("Physical Memory", arr_physMem, arrSize);
            ImGui::Text("Physical Memory: %f / %f", arr_physMem[arrIndex], memLeakDet.getTotalPhysMem());
            ImGui::PlotLines("Dt", arr_virtMem, arrSize);
            ImGui::Text("Virtual Memory: %f / %f", arr_virtMem[arrIndex], memLeakDet.getTotalVirtMem());

            ImGui::Separator();
            ImGui::PlotLines("Dt", arr_deltaTime, arrSize);
            ImGui::Text("Current Dt: %f",deltaTimeSec);

            ImGui::Separator();
            ImGui::Text("Num GameObjects %zu", gameObjects.size());
            ImGui::Text("Num of Sprites Allocated %d - Max %d", renderSystem.spritePool.count, max_renderSprites);

            ImGui::Separator();

            if(toggle_goInspector){
                ImGui::Begin("GameObject Inspector");
                if(ImGui::TreeNode("GameObjects")){
                    int i = 0;
                    for(auto& el: gameObjects){
                        string name = el->name;
                        if(name == "") name = &"GO " [ i];

                        ImGui::PushID(&el);
                        if(ImGui::TreeNode(el->name.c_str())){
                            vec2 pos = toGlm(el->body->GetPosition());
                            ImGui::Text("Position (%f, %f)", pos.x, pos.y);

                            ImGui::Text("Rotation (%f)", el->body->GetAngle());

                            vec2 vel = toGlm(el->body->GetLinearVelocity());
                            ImGui::Text("Velocity (%f, %f)", vel.x, vel.y);
                            
                            ImGui::Text("Angular Velocity (%f)", el->body->GetAngularVelocity());

                            ImGui::TreePop();
                        }
                        ImGui::PopID();
                        i++;
                    }
                    ImGui::TreePop();
                }
                ImGui::End();
            }

            if(toggle_showcasePanel){
                ImGui::Begin("Showcases");
                showcasePanel.makeGui();
                ImGui::End();
            }



            arrIndex++;
            if(arrIndex >= arrSize)
                arrIndex = 0;

        }

        //UPDATE
        if(!pause || runOneStep){
            for(auto& el: gameObjects)
                el->Update(deltaTimeSec);
            world->Step(deltaTimeSec, VELOCITY_ITERATIONS, POSITION_ITERATIONS);         

            if(toggle_showcasePanel){
                showcasePanel.update(deltaTimeSec);
            }
           
        }
        //DRAW
        renderSystem.update(deltaTimeSec);

        if(toggle_showcasePanel)
            showcasePanel.draw();

        if(debug)
            ImGui::Render();

        //world->DrawDebugData();
        sre->swapWindow();
    }

}

void GoldEngine::HandleSDLEvents(){
    // message processing loop
    SDL_Event event;
    /* Poll for events */
    while( SDL_PollEvent( &event ) ){
        ImGui_SRE_ProcessEvent(&event);
        
        switch( event.type ){
            case SDL_QUIT:
                quit = 1;
                break;
            default:
                break;
        }   
    }
}

void GoldEngine::BeginContact(b2Contact* contact){
    b2Body* colliderA = contact->GetFixtureA()->GetBody();
    b2Body* colliderB = contact->GetFixtureB()->GetBody();
}

void GoldEngine::EndContact(b2Contact* contact) {
    b2Body* colliderA = contact->GetFixtureA()->GetBody();
    b2Body* colliderB = contact->GetFixtureB()->GetBody();
}

