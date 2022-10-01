#include "../include/component_keyboard_movement.hpp"
#include "../include/object.hpp"
#include "../include/component_transform.hpp"

CKeyboardMovement::CKeyboardMovement(Object* owner)
    : Component   (owner)
    , move_speed_ {100}
    , input_      {nullptr}
{}


void CKeyboardMovement::Awake()
{
    animation_ = owner_->GetComponent<CAnimation>();
}

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
	animation_->SetAnimationDirection(FacingDirection::kLeft);
    }
    if(input_->IsKeyPressed(Input::Key::Right))
    {
	xmove += move_speed_ * delta_time;
	animation_->SetAnimationDirection(FacingDirection::kRight);
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

    if(xmove == 0 && ymove == 0)
    {
	animation_->SetAnimationState(AnimationState::kIdle);
    }
    else
    {
	animation_->SetAnimationState(AnimationState::kWalk);
    }
    
    owner_ -> GetComponent<CTransform>() -> AddPosition(xmove, ymove);
}
