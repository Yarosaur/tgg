#include "../include/component_drawable.hpp"

CDrawable::CDrawable(Object* owner)
    : Component   (owner)
    , sort_order_ {0}
{}

CDrawable::~CDrawable() {}


void CDrawable::SetSortOrder(std::size_t order)
{
    sort_order_ = order;
}


std::size_t CDrawable::GetSortOrder() const
{
    return sort_order_;
}
