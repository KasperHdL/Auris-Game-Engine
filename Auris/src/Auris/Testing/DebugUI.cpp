#ifdef DEBUG
#include "Auris/Testing/DebugUI.hpp"
#include "Auris/Engine.hpp"

using namespace Auris;
void DebugUI::startup(Engine* engine){
    this->e = engine;
  
    e->world->SetDebugDraw(&debugDraw);
    debugDraw.SetFlags(b2Draw::e_shapeBit);

}

void DebugUI::shutdown(){

}

void DebugUI::update(float dt){
    runOneStep = false;

    if(Input::keyDown(Auris::Action::stepOne) || Input::keyHeld(Auris::Action::playOnHold)){
        runOneStep = true;
        pause = true;
    }

    if(Input::keyDown(Auris::Action::drawDebug))
        drawDebug = !drawDebug;
    

    if(Input::keyDown(Auris::Action::drawColliders))
        drawColliders = !drawColliders;

    if(Input::keyDown(Auris::Action::debug_menu))
        debug_menu = !debug_menu;
    
    if(Input::keyDown(Auris::Action::pause))
        pause = !pause;
   
    if(Input::keyDown(Auris::Action::toggleProfiler))
        profiling = !profiling;

    if(Input::keyDown(Auris::Action::toggleHierarchy))
        toggle_hierarchy = !toggle_hierarchy;

    if(Input::keyDown(Auris::Action::toggleInspector))
        toggle_inspector = !toggle_inspector;


    if(debug_menu){
        
        ImGui::Begin("Debug Menu");
        {
            ImGui::Checkbox("Debug(F2)[this]", &debug_menu);
            ImGui::Checkbox("Toggle Hierarchy(F3)", &toggle_hierarchy);
            ImGui::Checkbox("Toggle Inspector(F4)", &toggle_inspector);
            ImGui::Checkbox("Toggle Profiling inspector(F5)", &profiling);
            ImGui::Separator();

            ImGui::Checkbox("Debug Colliders(F7)", &drawColliders);
            ImGui::Checkbox("Call DrawDebug on Entities(F8)", &drawDebug);

            ImGui::Separator();
            ImGui::Checkbox("Pause(F10)", &pause);
            if(ImGui::Button("Step One Frame(F11)")){
                runOneStep = true;
                pause = true;
            }
            ImGui::SameLine();
            ImGui::Text("Play on Hold(F12)");
    //          ImGui::Checkbox("Toggle Camera Controls(Arrow Keys)",&toggle_cameraControls);

        }
        ImGui::End();
    }

    if(profiling){
        ImGui::Begin("Profiling:");
        {

            if(dt > max_deltaTime)
                max_deltaTime = dt;

            if(e->renderSystem.spritePool.count > max_renderSprites)
                max_renderSprites = e->renderSystem.spritePool.count;

            sum_dt              -= arr_deltaTime           [ arrIndex];
            sum_input           -= arr_profInput           [ arrIndex];
            sum_entUpdate       -= arr_profEntityUpdate    [ arrIndex];
            sum_gEarlyUpdate    -= arr_profGEarlyUpdate    [ arrIndex];
            sum_gUpdate         -= arr_profGUpdate         [ arrIndex];
            sum_gLateUpdate     -= arr_profGLateUpdate     [ arrIndex];
            sum_physics         -= arr_profPhysics         [ arrIndex];
            sum_updateTransform -= arr_profUpdateTransform [ arrIndex];
            sum_render          -= arr_profRender          [ arrIndex];
            sum_swap            -= arr_profSwap            [ arrIndex];

            arr_deltaTime           [ arrIndex] = dt;
            arr_physMem             [ arrIndex] = memLeakDet.getPhysMemUsedByMe();
            arr_virtMem             [ arrIndex] = memLeakDet.getVirtMemUsedByMe();
            arr_profInput           [ arrIndex] = e->profile_InputTimer.length;
            arr_profEntityUpdate    [ arrIndex] = e->profile_Entity_UpdateTimer.length;
            arr_profGEarlyUpdate    [ arrIndex] = e->profile_Game_EarlyUpdateTimer.length;
            arr_profGUpdate         [ arrIndex] = e->profile_Game_UpdateTimer.length;
            arr_profGLateUpdate     [ arrIndex] = e->profile_Game_LateUpdateTimer.length;
            arr_profPhysics         [ arrIndex] = e->profile_PhysicsTimer.length;
            arr_profUpdateTransform [ arrIndex] = e->profile_UpdatePhysicsEntityTransformTimer.length;
            arr_profRender          [ arrIndex] = e->profile_RenderTimer.length;
            arr_profSwap            [ arrIndex] = e->profile_SwapTimer.length;


            sum_dt              += arr_deltaTime           [ arrIndex];
            sum_input           += arr_profInput           [ arrIndex];
            sum_entUpdate       += arr_profEntityUpdate    [ arrIndex];
            sum_gEarlyUpdate    += arr_profGEarlyUpdate    [ arrIndex];
            sum_gUpdate         += arr_profGUpdate         [ arrIndex];
            sum_gLateUpdate     += arr_profGLateUpdate     [ arrIndex];
            sum_physics         += arr_profPhysics         [ arrIndex];
            sum_updateTransform += arr_profUpdateTransform [ arrIndex];
            sum_render          += arr_profRender          [ arrIndex];
            sum_swap            += arr_profSwap            [ arrIndex];


            ImGui::Text("Physical Memory in MB");
            ImGui::PlotLines("", arr_physMem, arrSize);
            ImGui::Text("%f \n/ \n%f", arr_physMem[arrIndex], memLeakDet.getTotalPhysMem());
            ImGui::Separator();
            ImGui::Text("Virtual Memory in MB");
            ImGui::PlotLines("", arr_virtMem, arrSize);
            ImGui::Text("%f \n/ \n%f", arr_virtMem[arrIndex], memLeakDet.getTotalVirtMem());
 


            ImGui::Text("Num Entities %zu", e->game->entities.size());
            ImGui::Text("Num of Sprites Allocated %d - Max %d", e->renderSystem.spritePool.count, max_renderSprites);

            ImGui::Separator();
            ImGui::Separator();
            ImGui::Text("Delta time in ms");
            ImGui::PlotLines("", arr_deltaTime, arrSize);
            ImGui::Text("%f \t- Avg: %f",1000 * dt, (1000 * sum_dt) / (double)arrSize);

            ImGui::Separator();
            ImGui::Text("Input Update in ms");
            ImGui::PlotLines("", arr_profInput, arrSize);
            ImGui::Text("%f \t- Avg: %f", 1000 * e->profile_InputTimer.length, (1000 * sum_input) / (double)arrSize);

            ImGui::Separator();
            ImGui::Text("Entity Update in ms");
            ImGui::PlotLines("", arr_profEntityUpdate, arrSize);
            ImGui::Text("%f \t- Avg: %f", 1000 * e->profile_Entity_UpdateTimer.length, (1000 * sum_entUpdate) / (double)arrSize);

            ImGui::Separator();
            ImGui::Text("Game Early Update in ms");
            ImGui::PlotLines("", arr_profGEarlyUpdate, arrSize);
            ImGui::Text("%f \t- Avg: %f", 1000 * e->profile_Game_EarlyUpdateTimer.length, (1000 * sum_gEarlyUpdate) / (double)arrSize);
            ImGui::Separator();
            ImGui::Text("Game Update in ms");
            ImGui::PlotLines("", arr_profGUpdate, arrSize);
            ImGui::Text("%f \t- Avg: %f", 1000 * e->profile_Game_UpdateTimer.length, (1000 * sum_gUpdate) / (double)arrSize);
            ImGui::Separator();
            ImGui::Text("Game Late Update in ms");
            ImGui::PlotLines("", arr_profGLateUpdate, arrSize);
            ImGui::Text("%f \t- Avg: %f", 1000 * e->profile_Game_LateUpdateTimer.length, (1000 * sum_gLateUpdate) / (double)arrSize);

            ImGui::Separator();
            ImGui::Text("Physics Step in ms");
            ImGui::PlotLines("", arr_profPhysics, arrSize);
            ImGui::Text("%f \t- Avg: %f", 1000 * e->profile_PhysicsTimer.length, (1000 * sum_physics) / (double)arrSize);

            ImGui::Separator();
            ImGui::Text("PhysicsEntity Update Transform in ms");
            ImGui::PlotLines("", arr_profUpdateTransform, arrSize);
            ImGui::Text("%f \t- Avg: %f", 1000 * e->profile_UpdatePhysicsEntityTransformTimer.length, (1000 * sum_updateTransform) / (double)arrSize);

            ImGui::Separator();
            ImGui::Text("Render time in ms");
            ImGui::PlotLines("", arr_profRender, arrSize);
            ImGui::Text("%f \t- Avg: %f", 1000 * e->profile_RenderTimer.length, (1000 * sum_render) / (double)arrSize);

            ImGui::Separator();
            ImGui::Text("SwapWindow time in ms");
            ImGui::PlotLines("", arr_profSwap, arrSize);
            ImGui::Text("%f \t- Avg: %f", 1000 * e->profile_SwapTimer.length, (1000 * sum_swap) / (double)arrSize);




        }
        ImGui::End();
    }


    int countOpen = 0;
    if(toggle_hierarchy){
        ImGui::Begin("Hierarchy");
        {

            int i = 0;
            int numWithNoName = 0;
            for(auto& ent: e->game->entities){
                if(i >= entityInspectorOpenSize)
                    continue;

                string name = ent->name;
                if(name == ""){
                    numWithNoName++;
                    i++;
                    continue;
                }


                if(ent->parent == nullptr){
                    ImGui::PushID(&entityInspectorOpen[i]);
                    if(ent->children.size() > 0){
                        ImGui::Checkbox("",&entityInspectorOpen[i]);
                        ImGui::SameLine();
                        if(ImGui::TreeNode(name.c_str())){
                            for(int j = 0; j < ent->children.size(); j++){

                                int k = 0;
                                for(auto& q: e->game->entities){
                                    if(ent->children[j] == q.get()) break;
                                    k++;
                                }

                                ImGui::Checkbox(ent->children[j]->name.c_str(),&entityInspectorOpen[k]);


                            }
                            ImGui::TreePop();

                        }
                    }else{
                        ImGui::Checkbox(ent->name.c_str(),&entityInspectorOpen[i]);
                    }
                    ImGui::PopID();
                }

                if(toggle_inspector){
                    if(entityInspectorOpen[i]){
                        ImGui::Begin("Inspector");
                        {
                            if(countOpen > 0){
                                ImGui::Separator();
                                ImGui::Separator();
                            }

                            if(ImGui::TreeNode(name.c_str())){
                                /* Child Toggle Parent in Inspector
                                if(ent->parent != nullptr){

                                    int k = 0;
                                    for(auto& q: e->game->entities){
                                        if(ent->parent == q.get()) break;
                                        k++;
                                    }

                                    ImGui::Checkbox(("Parent: " + ent->parent->name).c_str(),&entityInspectorOpen[k]);
                                }
                                */

                                ent->inspectorImGui();
                                ImGui::TreePop();
                            }
                            countOpen++;
                        }
                        ImGui::End();
                    }
                }
                i++;


            }
            ImGui::Text("Num Entities with no name: %d", numWithNoName);
        }
        ImGui::End();
    }


    if(toggle_inspector && countOpen == 0){
        ImGui::Begin("Inspector");
        ImGui::Text("Select Entities in the Hierarchy");
        ImGui::End();
    }


    arrIndex++;
    if(arrIndex >= arrSize)
        arrIndex = 0;

    e->game->drawDebugImGui();


}

void DebugUI::draw(){
    if(drawDebug){
        for(auto& ent: e->game->entities){
            ent->debugDraw();
        }
    }

    if(drawColliders){
        e->world->DrawDebugData();
    }


}
#endif
