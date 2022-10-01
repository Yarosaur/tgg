#include "../include/system_drawable.hpp"

void SDrawable::Add(std::vector<std::shared_ptr<Object>>& objects)
{
    for (auto object : objects)
    {
	Add(object);
    }
    
    Sort();
}


void SDrawable::Add(std::shared_ptr<Object> object)
{
    std::shared_ptr<CDrawable> draw { object->GetDrawable() };
    if (draw)
    {
	drawables_.emplace_back(object);
    }
}


void SDrawable::Sort()
{
    std::sort(drawables_.begin(), drawables_.end(), 
	[](std::shared_ptr<Object> a, std::shared_ptr<Object> b) -> bool
	    {
		return a->GetDrawable()->GetSortOrder() 
		    < b->GetDrawable()->GetSortOrder();
	    }
	);
}


void SDrawable::Draw(Window& window)
{
    for (auto& object : drawables_)
    {
	object->Draw(window);
    }
}


void SDrawable::ProcessRemovals()
{
    auto obj_iter { drawables_.begin() };
    while (obj_iter != drawables_.end())
    {
	auto obj = *obj_iter;
	if (obj->IsQueuedForRemoval())
	{
	    obj_iter = drawables_.erase(obj_iter);
	}
	else
	{
	    ++obj_iter;
	}
    }
}
