//#include "object.hpp"

template <typename T>
std::shared_ptr<T> Object::AddComponent()
{
    static_assert(std::is_base_of<Component, T>::value,
		  "T must derive from Component");
    
    // Check that we don't already have a component of this type.
    for (auto& component_ptr: components_)
    {
	if ( std::dynamic_pointer_cast<T>(component_ptr) )
	{
	    return std::dynamic_pointer_cast<T>(component_ptr);
	}
    }

    // Create component 'T' and add it to listT if object does not have it.
    auto fresh_component { std::make_shared<T>(this) };
    components_.push_back(fresh_component);

    return fresh_component;
}


template <typename T>
std::shared_ptr<T> Object::GetComponent()
{
    // Check that we have get a component of this type.
    for (auto& component_ptr: components_)
    {
	if ( std::dynamic_pointer_cast<T>(component_ptr) )
	{
	    return std::dynamic_pointer_cast<T>(component_ptr);
	}
    }

    return nullptr;
}

