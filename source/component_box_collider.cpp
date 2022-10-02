#include "../include/component_box_collider.hpp"
#include "../include/object.hpp"
#include "../include/component_transform.hpp"

#include <cmath>

void CBoxCollider::SetPosition()
{
    const sf::Vector2f& pos { owner_->GetComponent<CTransform>()->GetPosition() };
    aabb_.left = pos.x - (aabb_.width / 2) + offset_.x;
    aabb_.top  = pos.y - (aabb_.height / 2) + offset_.y;
}


CBoxCollider::CBoxCollider(Object* owner)
    : CCollider (owner)
    , offset_   {sf::Vector2f(0.f, 0.f)}
{}


void CBoxCollider::SetCollidable(const sf::FloatRect& rect)
{
    aabb_ = rect;
    SetPosition();
}


const sf::FloatRect& CBoxCollider::GetCollidable()
{
    SetPosition();
    return aabb_;
}


Manifold CBoxCollider::Intersects(std::shared_ptr<CCollider> other)
{
    Manifold m;
    m.colliding = false;

    // TODO: add support to other collider shapes
    auto box_collider { std::dynamic_pointer_cast<CBoxCollider>(other) };
    if (box_collider)
    {
	const sf::FloatRect& rect1 { GetCollidable() };
	const sf::FloatRect& rect2 { box_collider->GetCollidable() };
	if (rect1.intersects(rect2)) 
	{
	    m.colliding = true; 
	    m.other = &rect2;
	}
    }
    
    return m;
}



void CBoxCollider::ResolveOverlap(const Manifold& m)
{
    auto transform { owner_->GetComponent<CTransform>() };
    if (!transform->IsMovable()) { return; }
    
    const sf::FloatRect& rect1 = GetCollidable();
    const sf::FloatRect* rect2 = m.other;
    
    float resolve  {0};
    float x_diff   { (rect1.left + (rect1.width * 0.5f)) - (rect2->left + (rect2->width * 0.5f)) };
    float y_diff   { (rect1.top + (rect1.height * 0.5f)) - (rect2->top + (rect2->height * 0.5f)) };
    // min distance to enter collision 
    float dx_entry { (rect1.width + rect2->width) * 0.5f };
    float dy_entry { (rect1.height + rect2->height) * 0.5f };
    
    if (std::fabs(x_diff)  <  dx_entry) 
    {
	if (x_diff > 0) // Colliding on the left.
	{
            // We add a positive x value to move the object to the right.
	    resolve = (rect2->left + rect2->width) - rect1.left; 
	}
	else // Colliding on the right.
	{
            // We add a negative x value to move the object to the left.
	    resolve = -((rect1.left + rect1.width) - rect2->left);
	}
	transform->AddPosition(resolve, 0); // 5
    }

    if (std::fabs(y_diff)  < dy_entry )
    {
	if (y_diff > 0) // Colliding above.
	{
            // We add a positive y value to move the object down.
	    resolve = (rect2->top + rect2->height) - rect1.top;
	}
	else // Colliding below
	{
            // We add a negative y value to move the object up.
	    resolve = -((rect1.top + rect1.height) - rect2->top);
	}
	transform->AddPosition(0, resolve); // 5
    }
}
