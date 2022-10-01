#ifndef __PROJECTS_TGG_SYSTEM_DRAWABLE_HPP__
#define __PROJECTS_TGG_SYSTEM_DRAWABLE_HPP__

#include "component_drawable.hpp"
#include "object.hpp"

#include <map>


class SDrawable
{
private:
    std::vector<std::shared_ptr<Object>> drawables_;
    
private:
    void Add             (std::shared_ptr<Object> object);
    void Sort            ();
    
public:
    void Add             (std::vector<std::shared_ptr<Object>>& object);
    void ProcessRemovals ();
    void Draw            (Window& window);
    
};


#endif
