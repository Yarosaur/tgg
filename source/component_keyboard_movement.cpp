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
    if(input_->IsKeyPressed(Input::Key::kLeft))
    {
	xmove -= move_speed_ * delta_time;
    }
    if(input_->IsKeyPressed(Input::Key::kRight))
    {
	xmove += move_speed_ * delta_time;
    }
    
    float ymove {0};
    if(input_->IsKeyPressed(Input::Key::kUp))
    {
	ymove -= move_speed_ * delta_time;
    }
    if(input_->IsKeyPressed(Input::Key::kDown))
    {
	ymove += move_speed_ * delta_time;
    }

    owner_ -> GetComponent<CTransform>() -> AddPosition(xmove, ymove);
    
    if(xmove == 0 && ymove == 0)
    {
	animation_->SetAnimationState(AnimationState::kIdle);
    }
    else
    {
	animation_->SetAnimationState(AnimationState::kWalk);
    }
    
    owner_ -> GetComponent<CTransform>() -> AddPosition(xmove, ymove);

    if(xmove == 0 && ymove == 0)
    {
	animation_->SetAnimationState(AnimationState::kIdle);
    }
    else
    {
	animation_->SetAnimationState(AnimationState::kWalk);
	if(abs(xmove) > abs(ymove))
	{
	    if(xmove < 0)
	    {
		animation_->SetAnimationDirection(FacingDirection::kLeft);
	    }
	    else
	    {
		animation_->SetAnimationDirection(FacingDirection::kRight);
	    }
	}
	else
	{
	    if(ymove < 0)
	    {
		animation_->SetAnimationDirection(FacingDirection::kUp);
	    }
	    else
	    {
		animation_->SetAnimationDirection(FacingDirection::kDown);
	    }
	}
    }
}
