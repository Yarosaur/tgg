#include "../include/object.hpp"


Object::Object()
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
    for (std::size_t i {0}; i < components_.size(); i++)
    {
	components_[i] -> Draw(window);
    }
}
