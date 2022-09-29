#ifndef __PROJECTS_TGG_OBJECT_HPP__
#define __PROJECTS_TGG_OBJECT_HPP__

#include "window.hpp"
#include "component.hpp"
#include "component_transform.hpp"

#include <vector>
#include <memory>
#include <type_traits>

class Object
{
private:
    std::vector<std::shared_ptr<Component>> components_;
    
public:
         Object     ();
    void Awake      ();  // Awake is called when object created. Use to Awake components.
    void Start      ();  // Start is called after Awake method. Use to initialise variables.
    void Update     (float delta_time);
    void LateUpdate (float delta_time);
    void Draw       (Window& window);

    template <typename T>
    std::shared_ptr<T> AddComponent();

    template <typename T>
    std::shared_ptr<T> GetComponent();
};


#include "object.inl"

#endif
