#ifndef __PROJECTS_TGG_COMPONENT_COLLIDER_HPP__
#define __PROJECTS_TGG_COMPONENT_COLLIDER_HPP__


#include "component.hpp"

#include <SFML/Graphics.hpp>

#include <memory>


enum class CollisionLayer
{
    kDefault,
    kPlayer,
    kTile,
    kMaxLayers
};


struct Manifold
{
    bool                 colliding { false };
    const sf::FloatRect* other     { nullptr };
};


class CCollider : public Component
{
private:
    CollisionLayer layer_;

public:
                     CCollider      (Object* owner);
                     ~CCollider     ();

    virtual Manifold Intersects     (std::shared_ptr<CCollider> other) = 0;
    virtual void     ResolveOverlap (const Manifold& m)                = 0;
    CollisionLayer   GetLayer       ()                                 const;
    void             SetLayer       (CollisionLayer layer);
};


#endif
