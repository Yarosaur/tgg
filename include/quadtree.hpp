#ifndef __PROJECTS_TGG_QUADTREE_HPP__
#define __PROJECTS_TGG_QUADTREE_HPP__


#include "object.hpp"
#include "component_box_collider.hpp"
#include "debug.hpp"

#include <memory>
#include <vector>


class Quadtree
{
private:
    enum NodeIndex
    {
	kThisTree = -1,
	kChildNW  = 0,
	kChildNE  = 1,
	kChildSE  = 2,
	kChildSW  = 3,
	kMaxChild,
    };

    enum Quadrant
    {
		
	kNE = 5,  // 0b0101
	kSE = 7,  // 0b0110
	kNW = 9,  // 0b1001	
	kSW = 10, // 0b1010
    };

private:
    std::size_t                                max_objects_;// maximum of objects for one node
    std::size_t                                max_depth_;    
    std::size_t                                depth_;      // Depth of this node in the tree
    sf::FloatRect                              bounds_;     // The bounds of this node.
    Quadtree*                                  parent_;     // nulptr for the base node.
    std::array<std::shared_ptr<Quadtree>, 4>   children_;
    std::vector<std::shared_ptr<CBoxCollider>> objects_;    // Stores objects in this node.
    
public:
                         Quadtree     ();
                         Quadtree     (std::size_t   max_objects,
				       std::size_t   max_depth,
				       std::size_t   depth, 
				       sf::FloatRect bounds,
				       Quadtree*     parent);
    
    void                 Insert       (std::shared_ptr<CBoxCollider> collider);
    void                 Remove       (std::shared_ptr<CBoxCollider> collider);
    void                 Clear        ();
    
    std::vector<std::shared_ptr<CBoxCollider>>
                         Search       (const sf::FloatRect& area);
    const sf::FloatRect& GetBounds    () const;
    void                 DrawDebug    () const;

private:
    void                 Search       (const sf::FloatRect& area,
				       std::vector<std::shared_ptr<CBoxCollider>>& overlapping_colliders);
    
    // Returns the index for the node that will contain 		
    // the object. -1 is returned if it is this node.
    NodeIndex            GetChildIndex(const sf::FloatRect& object_bounds);
    // Creates the child nodes.
    void                 Split        ();
    // Rearrange objects among tree nodes
    void                 Rearrange    ();

    
};


#endif 
