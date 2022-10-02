#include "../include/component_instance_id.hpp"

std::size_t CInstanceID::count_ {0};

CInstanceID::CInstanceID(Object* owner)
    : Component (owner)
    , id_       {count_++}
{}


CInstanceID::~CInstanceID() {}


std::size_t CInstanceID::GetID() const
{
    return id_;
}
