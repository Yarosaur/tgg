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


std::vector<std::shared_ptr<CBoxCollider>> Quadtree::Search(const sf::FloatRect& area)
{
    std::vector<std::shared_ptr<CBoxCollider>> possible_overlaps;
    Search(area, possible_overlaps);
    std::vector<std::shared_ptr<CBoxCollider>> return_list;
    for (auto collider : possible_overlaps)
    {
	if (area.intersects(collider->GetCollidable()))
	{
	    return_list.emplace_back(collider);
	}
    }
    return return_list;
}


void Quadtree::Search(const sf::FloatRect& area,              
		      std::vector<std::shared_ptr<CBoxCollider>>& overlapping_objects)
{
    overlapping_objects.insert(overlapping_objects.end(), objects_.begin(), objects_.end()); // 1
    if(children_[0] != nullptr)
    {
	int index { GetChildIndex(area) };
	if(index == kThisTree)
	{
	    for(int i {kChildNE}; i < kMaxChild; i++)
	    {
		if(children_[i]->GetBounds().intersects(area))
		{
		    children_[i]->Search(area, overlapping_objects);
		}
	    }
	}
	else
	{
	    children_[index]->Search(area, overlapping_objects);
	}
    }
}



const sf::FloatRect& Quadtree::GetBounds() const
{
    return bounds_;
}



Quadtree::NodeIndex Quadtree::GetChildIndex(const sf::FloatRect& object_bounds)
{
    NodeIndex index {kThisTree};
    double vertical_dividing_line   { bounds_.left + bounds_.width * 0.5f};
    double horizontal_dividing_line { bounds_.top + bounds_.height * 0.5f };
    
    bool north { object_bounds.top < horizontal_dividing_line 
	&& (object_bounds.height + object_bounds.top < horizontal_dividing_line) };
    bool south { object_bounds.top > horizontal_dividing_line };
    bool west  { object_bounds.left < vertical_dividing_line 
	&& (object_bounds.left + object_bounds.width < vertical_dividing_line) };
    bool east  { object_bounds.left > vertical_dividing_line };
    if(east)
    {
	if(north)
	{
	    index = kChildNE;
	}
	else if(south)
	{
	    index = kChildSE;
	}
    }
    else if(west)
    {
	if(north)
	{
	    index = kChildNW;
	}
	else if(south)
	{
	    index = kChildSW;
	}
    }
    return index;
}


void Quadtree::Split()
{
    const int child_width  { bounds_.width / 2 };
    const int child_height { bounds_.height / 2 };
    children_[kChildNE] = std::make_shared<Quadtree>(max_objects_, max_depth_, depth_ + 1, 
						   sf::FloatRect(bounds_.left + child_width,
								 bounds_.top,
								 child_width, child_height), 
						     this);
    
    children_[kChildNW] = std::make_shared<Quadtree>(max_objects_, max_depth_, depth_ + 1, 
						   sf::FloatRect(bounds_.left, bounds_.top,
								 child_width, child_height), 
						   this);
    
    children_[kChildSW] = std::make_shared<Quadtree>(max_objects_, max_depth_, depth_ + 1, 
						   sf::FloatRect(bounds_.left,
								 bounds_.top + child_height,
								 child_width, child_height), 
						   this);
    
    children_[kChildSE] = std::make_shared<Quadtree>(max_objects_, max_depth_, depth_ + 1, 
						   sf::FloatRect(bounds_.left + child_width,
								 bounds_.top + child_height,
								 child_width, child_height), 
						   this);
}
