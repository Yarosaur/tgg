#include "../include/scene_state_machine.hpp"

SceneStateMachine::SceneStateMachine()
    : scenes_            ()
    , curr_scene_        {nullptr}
    , inserted_scene_id_ {0}
{}


void SceneStateMachine::ProcessInput()
{
    if (curr_scene_)
    {
	curr_scene_ -> ProcessInput();
    }
}


void SceneStateMachine::Update(float delta_time)
{
    if (curr_scene_)
    {
	curr_scene_ -> Update(delta_time);
    }
}


void SceneStateMachine::LateUpdate(float delta_time)
{
    if (curr_scene_)
    {
	curr_scene_ -> LateUpdate(delta_time);
    }
}


void SceneStateMachine::Draw(Window& window)
{
    if (curr_scene_)
    {
	curr_scene_ -> Draw(window);
    }
}


uint SceneStateMachine::Add(std::shared_ptr<Scene> scene)
{
    auto inserted { scenes_.insert(std::make_pair(inserted_scene_id_, scene)) };

    inserted.first->second->Create();

    return inserted_scene_id_++;
}


void SceneStateMachine::Remove(uint id)
{
    auto it { scenes_.find(id) };
    if(it != scenes_.end())
    {
	if (curr_scene_ == it->second)
	{
	    curr_scene_ = nullptr;
	}
        // We make sure to call the OnDestroy method 
        // of the scene we are removing.
	it->second->Destroy(); 
	scenes_.erase(it);
    }
}


void SceneStateMachine::SwitchTo(uint id)
{
    auto it { scenes_.find(id) };
    if (it != scenes_.end())
    {
	if(curr_scene_)
	{
            // If we have a current scene, we call its Deactivate method.
	    curr_scene_->Deactivate(); 
	}
        // Setting the current scene ensures that it is updated and drawn.
	curr_scene_ = it->second; 
	curr_scene_->Activate();
    }
}






