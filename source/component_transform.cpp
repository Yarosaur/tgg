#include "../include/component_transform.hpp"

CTransform::CTransform(Object* owner)
    : Component  (owner)
    , position_  (0.f, 0.f)
    , movable_   {true}
{}


void CTransform::SetPosition(float x, float y)
{
    position_.x = x;
    position_.y = y;
}


void CTransform::SetPosition(sf::Vector2f pos)
{
    position_ = pos;
}


void CTransform::AddPosition(float x, float y)
{
    position_.x += x;
    position_.y += y;
}


void CTransform::AddPosition(sf::Vector2f pos)
{
    position_ += pos;
}


void CTransform::SetX(float x)
{
    position_.x = x;
}


void CTransform::SetY(float y)
{
    position_.y = y;
}


sf::Vector2f CTransform::GetPosition() const
{
    return position_;
}


bool CTransform::IsMovable() const
{
    return movable_;
}


void CTransform::SetMovable(bool movable)
{
    movable_ = movable;
}


