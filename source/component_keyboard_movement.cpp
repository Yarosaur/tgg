#include "../include/component_keyboard_movement.hpp"
#include "../include/object.hpp"

CKeyboardMovement::CKeyboardMovement(Object* owner)
    : Component   (owner)
    , move_speed_ {100}
    , input_      {nullptr}
{}


void CKeyboardMovement::SetInput(Input* input)
{
    input_ = input;
}


void CKeyboardMovement::SetMovementSpeed(int speed)
{
    move_speed_ = speed;
}


void CKeyboardMovement::Update(float delta_time)
{
    if(input_ == nullptr)
    {
	return;
    }
    
    float xmove {0};
    if(input_->IsKeyPressed(Input::Key::Left))
    {
	xmove -= move_speed_ * delta_time;
    }
    if(input_->IsKeyPressed(Input::Key::Right))
    {
	xmove += move_speed_ * delta_time;
    }
    
    float ymove {0};
    if(input_->IsKeyPressed(Input::Key::Up))
    {
	ymove -= move_speed_ * delta_time;
    }
    if(input_->IsKeyPressed(Input::Key::Down))
    {
	ymove += move_speed_ * delta_time;
    }
    
    owner_ -> GetComponent<CTransform>() -> AddPosition(xmove, ymove);
}
