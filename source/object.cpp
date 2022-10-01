#include "../include/object.hpp"
#include "../include/component_transform.hpp"


Object::Object()
    : queued_for_removal_ {false}
{
    AddComponent<CTransform>();
}


void Object::Awake()
{
    for (std::size_t i {0}; i < components_.size(); i++)
    {
	components_[i] -> Awake();
    }
}


void Object::Start()
{
    for (std::size_t i {0}; i < components_.size(); i++)
    {
	components_[i] -> Start();
    }    
}


void Object::Update(float delta_time)
{
    for (std::size_t i {0}; i < components_.size(); i++)
    {
	components_[i] -> Update(delta_time);
    }
}


void Object::LateUpdate(float delta_time)
{
    for (std::size_t i {0}; i < components_.size(); i++)
    {
	components_[i] -> LateUpdate(delta_time);
    }
}


void Object::Draw(Window& window)
{
    drawable_ -> Draw(window);
}


void Object::QueueForRemoval()
{
    queued_for_removal_ = true;
}


bool Object::IsQueuedForRemoval()
{
    return  queued_for_removal_;
}



std::shared_ptr<CDrawable> Object::GetDrawable()
{
    return drawable_;
}
