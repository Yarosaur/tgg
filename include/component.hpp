#ifndef __PROJECTS_TGG_COMPONENT_HPP__
#define __PROJECTS_TGG_COMPONENT_HPP__

#include "window.hpp"

class Object;

class Component
{
protected:
    Object* owner_;
public:
    Component(Object* owner) : owner_ {owner}  {}
    
    virtual void Awake      ()                 {};
    virtual void Start      ()                 {};
    virtual void Update     (float delta_time) {};
    virtual void LateUpdate (float delta_time) {};
    virtual void Draw       (Window& window)   {};
};

#endif
