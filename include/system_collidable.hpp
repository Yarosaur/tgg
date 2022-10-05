#ifndef __PROJECTS_TGG_SYSTEM_COLLIDABLE_HPP__
#define __PROJECTS_TGG_SYSTEM_COLLIDABLE_HPP__


#include "object.hpp"
#include "quadtree.hpp"
#include "component_collider.hpp"

#include <vector>
#include <memory>
#include <set>
#include <bitset>


class SCollidable
{
private:    
    // This is used to store collision layer data i.e. which layers can collide.
    std::map<CollisionLayer, std::bitset<32>>                            collision_layers_;
    // The collision system stores all collidables along with their layer.
    std::map<CollisionLayer, std::vector<std::shared_ptr<CBoxCollider>>> collidables_;
    // The quadtree stores the collidables in a spatial aware structure.
    Quadtree                                                             collision_tree_;
    
public:
         SCollidable       ();
    void Add               (std::vector<std::shared_ptr<Object>>& objects);
    void ProcessRemovals   ();
    void Update            ();
    
private:
    void Resolve           ();
    void ProcessCollisions (std::vector<std::shared_ptr<Object>>& first,
			    std::vector<std::shared_ptr<Object>>& second);
};
#endif
