#ifndef __PROJECTS_TGG_QUADTREE_HPP__
#define __PROJECTS_TGG_QUADTREE_HPP__


#include "object.hpp"
#include "component_box_collider.hpp"

#include <memory>
#include <vector>


class Quadtree
{
private:
    enum NodeIndex
    {
	kThisTree = -1,
	kChildNE  = 0,
	kChildNW  = 1,
	kChildSW  = 2,
	kChildSE  = 3,
	kMaxChild,
    };

private:
    
    std::size_t                                max_objects_;
    std::size_t                                max_depth_;
    Quadtree*                                  parent_;     // nulptr for the base node.
    std::array<std::shared_ptr<Quadtree>, 4>   children_;
    std::vector<std::shared_ptr<CBoxCollider>> objects_;    // Stores objects in this node.
    std::size_t                                depth_;      // Depth of this node in the tree
    sf::FloatRect                              bounds_;     // The bounds of this node.
    
private:
    void                 Search       (const sf::FloatRect& area,
				       std::vector<std::shared_ptr<CBoxCollider>>& overlapping_objects);
    
    // Returns the index for the node that will contain 		
    // the object. -1 is returned if it is this node.
    NodeIndex            GetChildIndex(const sf::FloatRect& object_bounds);

    // Creates the child nodes.
    void                 Split        ();

public:
                         Quadtree     ();
                         Quadtree     (std::size_t   max_objects,
				       std::size_t   max_depth,
				       std::size_t   depth, 
				       sf::FloatRect bounds,
				       Quadtree*     parent);
    
    void                 Insert       (std::shared_ptr<CBoxCollider> object);
    void                 Remove       (std::shared_ptr<CBoxCollider> object);
    void                 Clear        ();
    
    std::vector<std::shared_ptr<CBoxCollider>>
                         Search       (const sf::FloatRect& area);
    const sf::FloatRect& GetBounds    () const;
    
};


#endif 
