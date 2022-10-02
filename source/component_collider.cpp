#include "../include/component_collider.hpp"

CCollider::CCollider(Object* owner)
    : Component (owner)
    , layer_    {CollisionLayer::kDefault}
{}


CCollider::~CCollider() {}


CollisionLayer CCollider::GetLayer() const
{
    return layer_;
}


void CCollider::SetLayer(CollisionLayer layer)
{
    layer_ = layer;
}
