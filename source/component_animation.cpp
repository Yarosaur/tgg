#include "../include/component_animation.hpp"
#include "../include/object.hpp"

CAnimation::CAnimation(Object* owner)
    : Component          (owner)
    , current_animation_ (AnimationState::kNone, nullptr)
    , current_direction_ {FacingDirection::kDown}
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


void CAnimation::SetAnimationState(AnimationState state)
{
    if (current_animation_.first == state)
    {
	return;
    }

    auto animation_map_iter {animations_.find(state)};
    if (animation_map_iter != animations_.end())
    {
	auto animation { animation_map_iter->second.find(current_direction_) };
	if (animation != animation_map_iter->second.end())
	{
	    current_animation_.first  = animation_map_iter -> first;
	    current_animation_.second = animation -> second;
	    current_animation_.second -> Reset();
	}
    }
}


AnimationState CAnimation::GetAnimationState() const
{
    return current_animation_.first;
}


void CAnimation::SetAnimationDirection(FacingDirection dir)
{
    if (dir != current_direction_)
    {
	current_direction_ = dir;
	auto animation_map_iter { animations_.find(current_animation_.first) };
	if (animation_map_iter != animations_.end())
	{
	    auto animation { animation_map_iter->second.find(current_direction_) };
	    if(animation != animation_map_iter->second.end())
	    {
		current_animation_.second = animation->second;
		current_animation_.second->Reset();
	    }
	}
    }
}


void CAnimation::AddAnimation(AnimationState state, AnimationList& animationList)
{
    animations_.insert(std::make_pair(state, animationList));
    if (current_animation_.first == AnimationState::kNone)
    {
	SetAnimationState(state);
    }
}
