#ifndef __PROJECTS_TGG_SCENE_HPP__
#define __PROJECTS_TGG_SCENE_HPP__

#include "window.hpp"

class Scene
{
public:
    // Called when scene initially created. Called once.
    virtual void Create       () = 0; 

    // Called when scene destroyed. Called at most once (if a scene 
    // is not removed from the game, this will never be called).
    virtual void Destroy      () = 0;
    
    // Called whenever a scene is transitioned into. Can be 
    // called many times in a typical game cycle.
    virtual void Activate     () {}; 

    // Called whenever a transition out of a scene occurs. 
    // Can be called many times in a typical game cycle.
    virtual void Deactivate () {};
    
    // The below functions can be overridden as necessary in our scenes.
    virtual void ProcessInput () {};
    virtual void Update       (float delta_time) {};
    virtual void LateUpdate   (float delta_time) {};
    virtual void Draw         (Window& window) {};
};

#endif
