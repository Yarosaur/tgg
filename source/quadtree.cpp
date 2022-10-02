#include "../include/quadtree.hpp"
#include "../include/component_instance_id.hpp"


Quadtree::Quadtree()
    : Quadtree(5, 5, 0,
	       {0.f, 0.f, 1920, 1080}, 
	       nullptr)
{}

Quadtree::Quadtree(std::size_t max_objects,  std::size_t max_depth, std::size_t depth,
		   sf::FloatRect bounds, Quadtree* parent)
    : max_objects_ {max_objects}
    , max_depth_   {max_depth}
    , depth_       {depth}
    , bounds_      {bounds}
    , parent_      {parent}     
{}


void Quadtree::Insert(std::shared_ptr<CBoxCollider> object)
{
    if (children_[0] != nullptr) 
    {
	NodeIndex index_for_object { GetChildIndex(object->GetCollidable()) };
	if(index_for_object != kThisTree)
	{
	    children_[index_for_object]->Insert(object);
	    return;
	}
    }
    
    objects_.emplace_back(object);
    if(objects_.size() > max_objects_ &&  depth_ < max_depth_ && children_[0] == nullptr)
    {
	Split();
	auto obj_iter { objects_.begin() };
	while (obj_iter != objects_.end())
	{
	    auto obj { *obj_iter};
	    NodeIndex index_for_object { GetChildIndex(obj->GetCollidable()) };
	    if (index_for_object != kThisTree)
	    {
		children_[index_for_object]->Insert(obj);
		obj_iter = objects_.erase(obj_iter);
	    }
	    else
	    {
		++obj_iter;
	    }
	}
    }
}


void Quadtree::Remove(std::shared_ptr<CBoxCollider> object)
{
    NodeIndex index { GetChildIndex(object->GetCollidable()) };
    if(index == kThisTree || children_[index] == nullptr)
    {
	for(std::size_t i {0}; i < objects_.size(); i++)
	{
	    if(objects_[i]->GetOwner()->GetComponent<CInstanceID>()->GetID() 
	       == object->GetOwner()->GetComponent<CInstanceID>()->GetID() )
	    {
		objects_.erase(objects_.begin() + i);
		break;
	    }
	}
    }
    else
    {
	return children_[index]->Remove(object);
    }
}



void Quadtree::Clear()
{
    objects_.clear();
    for(std::size_t i {0}; i < kMaxChild; i++)
    {
	if(children_[i] != nullptr)
	{
	    children_[i]->Clear();
	    children_[i] = nullptr;
	}
    }
}

