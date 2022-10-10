#ifndef __PROJECTS_TGG_COMPONENT_ANIMATION_HPP__
#define __PROJECTS_TGG_COMPONENT_ANIMATION_HPP__

#include "type_identifier.hpp"
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


enum class FacingDirection
{
    kNone,
    kLeft,
    kRight,
    kUp,
    kDown,
};



class CAnimation : public Component
{
private:
    std::shared_ptr<CSprite>                              sprite_;
    std::map<AnimationState, AnimationList>               animations_;
    std::pair<AnimationState, std::shared_ptr<Animation>> current_animation_;
    FacingDirection                                       current_direction_;

public:
                   CAnimation            (Object* qwner);
    void           Awake                 ()                      override;
    void           Update                (float delta_time)      override;
    void           SetAnimationState     (AnimationState state);
    AnimationState GetAnimationState     ()                      const;
    void           SetAnimationDirection (FacingDirection dir);
    void           AddAnimation          (AnimationState state,
					  AnimationList& list);
};

#endif
