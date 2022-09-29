#ifndef __PROJECTS_TGG_SCENE_STATE_MACHINE_HPP__
#define __PROJECTS_TGG_SCENE_STATE_MACHINE_HPP__

#include "scene.hpp"
#include "window.hpp"

#include <memory>
#include <unordered_map>

class SceneStateMachine
{
public:
    SceneStateMachine();
    // ProcessInput, Update, LateUpdate, and Draw will simply be pass through methods.
    // They will call the correspondingly named methods of the active scene.
    void ProcessInput ();
    void Update       (float delta_time);
    void LateUpdate   (float delta_time);
    void Draw         (Window& window);

    // Adds a scene to the state machine and returns the id of that scene.
    uint Add          (std::shared_ptr<Scene> scene); 

    // Transitions to scene with specified id.
    void SwitchTo     (uint id); 

    // Removes scene from state machine.
    void Remove       (uint id);
    
private:
    // Stores all of the scenes associated with this state machine.
    std::unordered_map<uint, std::shared_ptr<Scene>> scenes_;
    
    // Stores a reference to the current scene. Used when drawing/updating.
    std::shared_ptr<Scene> curr_scene_; 

    // Stores our current scene id. This is incremented whenever a scene is added.
    uint inserted_scene_id_; 
};

#endif
