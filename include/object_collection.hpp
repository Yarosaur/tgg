#ifndef __PROJECTS_TGG_OBJECT_COLLECTION_HPP__
#define __PROJECTS_TGG_OBJECT_COLLECTION_HPP__

#include "object.hpp"
#include "system_drawable.hpp"
#include "system_collidable.hpp"

#include <vector>
#include <memory>


class ObjectCollection
{
private:
    std::vector<std::shared_ptr<Object>> objects_;
    std::vector<std::shared_ptr<Object>> fresh_objects_;
    SDrawable                            drawables_;
    SCollidable                          collidables_;
    
public:
    void Add               (std::shared_ptr<Object> object);
    void Update            (float delta_time);
    void LateUpdate        (float delta_time);
    void Draw              (Window& window);
    void ProcessNewObjects ();
    void ProcessRemovals   ();
};


#endif
