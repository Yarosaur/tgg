#include "../include/object_collection.hpp"


void ObjectCollection::Add(std::shared_ptr<Object> object)
{
    fresh_objects_.push_back(object);
}


void ObjectCollection::Update(float delta_time)
{
    for (auto& object: objects_)
    {
	object -> Update(delta_time);
    }
}


void ObjectCollection::LateUpdate(float delta_time)
{
    for (auto& object: objects_)
    {
	object -> LateUpdate(delta_time);
    }
}


void ObjectCollection::Draw(Window& window)
{
    for (auto& object: objects_)
    {
	object->Draw(window);
    }
}


void ObjectCollection::ProcessNewObjects()
{
    if (fresh_objects_.size() > 0)
    {
	for (const auto& object: fresh_objects_)
	{
	    object -> Awake();
	}
	
	for (const auto& object: fresh_objects_)
	{
	    object -> Start();
	}

	objects_.insert(objects_.end(), fresh_objects_.begin(), fresh_objects_.end());
	fresh_objects_.clear();
    }
}


void ObjectCollection::ProcessRemovals()
{
    auto obj_iter { objects_.begin() };
    while (obj_iter != objects_.end())
    {
	auto obj { **obj_iter };
	if (obj.IsQueuedForRemoval())
	{
	    obj_iter = objects_.erase(obj_iter);
	}
	else
	{
	    ++obj_iter;
	}
    }
}
