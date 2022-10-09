#include "../include/system_drawable.hpp"


void SDrawable::Add(std::shared_ptr<Object> object)
{
    std::shared_ptr<CDrawable> drawable { object->GetComponent<CDrawable>() };
    if (drawable)
    {
	DrawLayer layer { drawable->GetDrawLayer() };
	auto      itr   { drawables_.find(layer) };
	if (itr != drawables_.end())
	{
	    drawables_[layer].push_back(drawable);
	}
	else
	{
	    std::vector<std::shared_ptr<CDrawable>> objs;
	    objs.push_back(drawable);
	    drawables_.insert(std::make_pair(layer, objs));
	}
    }
}


void SDrawable::Sort()
{
    for (auto& layer : drawables_)
    {
	if(!std::is_sorted(layer.second.begin(), layer.second.end(), LayerSort))
	{
	    std::sort(layer.second.begin(), layer.second.end(), LayerSort);
	}
    }
}


bool SDrawable::LayerSort(std::shared_ptr<CDrawable> a,
			  std::shared_ptr<CDrawable> b)
{
    return a->GetSortOrder() < b->GetSortOrder();  
}



void SDrawable::Add(std::vector<std::shared_ptr<Object>>& objects)
{
    for (auto object : objects)
    {
	Add(object);
    }
}


void SDrawable::Draw(Window& window)
{
    Sort();
    
    for (auto& layer : drawables_)
    {
	for (auto& object : layer.second)
	{
	    object->Draw(window);
	}
    }
}


void SDrawable::ProcessRemovals()
{
    for (auto& layer : drawables_)
    {
	auto draw_iter { layer.second.begin() };
	while (draw_iter != layer.second.end())
	{
	    
	    auto drawable { *draw_iter };
	    if (drawable->GetOwner()->IsQueuedForRemoval())
	    {
		draw_iter = layer.second.erase(draw_iter);
	    }
	    else
	    {
		++draw_iter;
	    }
	}
    }
}
