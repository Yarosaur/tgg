#ifndef __PROJECTS_TGG_COMPONENT_KEYBOARD_MOVEMENT_HPP__
#define __PROJECTS_TGG_COMPONENT_KEYBOARD_MOVEMENT_HPP__

#include "component.hpp"
#include "input.hpp"


class CKeyboardMovement : public Component
{
private:
    int    move_speed_; 
    Input* input_;

public:
         CKeyboardMovement (Object * owner);
    void SetInput          (Input* input);
    void SetMovementSpeed  (int speed);
    void Update            (float delta_time) override;
};
    
#endif
