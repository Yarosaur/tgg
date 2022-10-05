#ifndef __PROJECTS_TGG_COMPONENT_BOX_COLLIDER_HPP__
#define __PROJECTS_TGG_COMPONENT_BOX_COLLIDER_HPP__

#include "component_collider.hpp"

class CBoxCollider : public CCollider
{
private:
    sf::FloatRect aabb_;
    sf::Vector2f  offset_;

private:
    void SetPosition();

public:
                         CBoxCollider   (Object* owner);
    Manifold             Intersects     (std::shared_ptr<CCollider> other) override;
    void                 ResolveOverlap (const Manifold& m)                override;
    void                 SetCollidable  (const sf::FloatRect& rect);
    const sf::FloatRect& GetCollidable  ();
    
    void                 SetOffset      (const sf::Vector2f& offset);
    void                 SetOffset      (float x, float y);
    void                 SetSize        (const sf::Vector2f& size);
    void                 SetSize        (float width, float height);
};


#endif
