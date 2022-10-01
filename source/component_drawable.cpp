#include "../include/component_drawable.hpp"

CDrawable::CDrawable() : sort_order_ {0} {}

CDrawable::~CDrawable() {}


void CDrawable::SetSortOrder(int order)
{
    sort_order_ = order;
}


int CDrawable::GetSortOrder() const
{
    return sort_order_;
}
