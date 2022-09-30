#ifndef __PROJECTS_TGG_COMPONENT_KEYBOARD_MOVEMENT_HPP__
#define __PROJECTS_TGG_COMPONENT_KEYBOARD_MOVEMENT_HPP__

#include "component.hpp"
#include "input.hpp"
#include "component_animation.hpp"


class CKeyboardMovement : public Component
{
private:
    int                         move_speed_; 
    Input*                      input_;
    std::shared_ptr<CAnimation> animation_;

public:
         CKeyboardMovement (Object * owner);
    void Awake             ()                 override;
    void SetInput          (Input* input);
    void SetMovementSpeed  (int speed);
    void Update            (float delta_time) override;
    
};
    
#endif
