#include "../include/component_drawable.hpp"
#include "../include/object.hpp"

CDrawable::CDrawable(Object* owner)
    : Component   (owner)
    , layer_      {DrawLayer::kDefault}
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


void CDrawable::SetDrawLayer(DrawLayer layer)
{
    layer_ = layer;
}


DrawLayer CDrawable::GetDrawLayer() const
{
    return layer_;
}

