#ifndef __PROJECTS_TGG_SYSTEM_DRAWABLE_HPP__
#define __PROJECTS_TGG_SYSTEM_DRAWABLE_HPP__

#include "component_drawable.hpp"
#include "object.hpp"

#include <map>


class SDrawable
{
private:
    std::map<DrawLayer, std::vector<std::shared_ptr<CDrawable>>> drawables_;
    
private:
    void         Add              (std::shared_ptr<Object> object);
    void         Sort             ();
    static bool  LayerSort        (std::shared_ptr<CDrawable> a,
				   std::shared_ptr<CDrawable> b);
public:
    void         Add              (std::vector<std::shared_ptr<Object>>& object);
    void         ProcessRemovals  ();
    void         Draw             (Window& window);
    
};


#endif
