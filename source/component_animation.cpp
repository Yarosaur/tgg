#include "../include/component_animation.hpp"
#include "../include/object.hpp"

CAnimation::CAnimation(Object* owner)
    : Component          (owner)
    , current_animation_ (AnimationState::kNone, nullptr)
{}


void CAnimation::Awake()
{
    sprite_ = owner_ -> GetComponent<CSprite>();
}


void CAnimation::Update(float delta_time)
{
    if (current_animation_.first != AnimationState::kNone)
    {
	bool need_update { current_animation_.second -> UpdateFrame(delta_time) };
	if (need_update)
	{
	    const FrameData* data { current_animation_.second -> GetCurrentFrame() };
	    sprite_ -> Load(data->texture_id);
	    sprite_ -> SetTextureRect(data->x, data->y, data->width, data->height);
	}
    }
}


void CAnimation::AddAnimation(AnimationState state, std::shared_ptr<Animation> animation)
{
    auto inserted { animations_.insert(std::make_pair(state, animation)) };
    if (current_animation_.first == AnimationState::kNone)
    {
	SetAnimationState(state);
    }
}


void CAnimation::SetAnimationState(AnimationState state)
{
    if (current_animation_.first == state)
    {
	return;
    }

    auto animation_iter {animations_.find(state)};
    if (animation_iter != animations_.end())
    {
	current_animation_.first  = animation_iter -> first;
	current_animation_.second = animation_iter -> second;
	current_animation_.second -> Reset();
    }
}


AnimationState CAnimation::GetAnimationState() const
{
    return current_animation_.first;
}


void CAnimation::SetAnimationDirection(FacingDirection dir)
{
    if (current_animation_.first != AnimationState::kNone)
    {
	current_animation_.second -> SetFacingDirection(dir);
    }
}
