#ifndef __PROJECTS_TGG_OBJECT_HPP__
#define __PROJECTS_TGG_OBJECT_HPP__

#include "window.hpp"
#include "component.hpp"
#include "component_drawable.hpp"

#include <vector>
#include <memory>
#include <type_traits>

class Object
{
private:
    std::vector<std::shared_ptr<Component>> components_;
    bool                                    queued_for_removal_;
    
public:
         Object             ();
    void Awake              ();  
    void Start              ();  
    void Update             (float delta_time);
    void LateUpdate         (float delta_time);
    void Draw               (Window& window);
    bool IsQueuedForRemoval ();
    void QueueForRemoval    ();

    template <typename T>
    std::shared_ptr<T> AddComponent();

    template <typename T>
    std::shared_ptr<T> GetComponent();
};


#include "object.inl"

#endif
