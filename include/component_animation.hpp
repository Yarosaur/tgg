#ifndef __PROJECTS_TGG_COMPONENT_ANIMATION_HPP__
#define __PROJECTS_TGG_COMPONENT_ANIMATION_HPP__

#include "component.hpp"
#include "animation.hpp"
#include "component_sprite.hpp"

#include <map>

enum class AnimationState
{
    kNone,
    kAttack,
    kIdle,
    kJump,
    kWalk,
    kDie,
};


class CAnimation : public Component
{
private:
    std::shared_ptr<CSprite>              sprite_;
    
    std::map<AnimationState,
	     std::shared_ptr<Animation>>  animations_;
    
    std::pair<AnimationState, 
	      std::shared_ptr<Animation>> current_animation_;

public:
                   CAnimation            (Object* qwner);
    void           Awake                 ()                                     override;
    void           Update                (float delta_time)                     override;
    void           AddAnimation          (AnimationState state,
					  std::shared_ptr<Animation> animation);
    void           SetAnimationState     (AnimationState state);
    AnimationState GetAnimationState     ()                                     const;
    void           SetAnimationDirection (FacingDirection dir);
};

#endif
