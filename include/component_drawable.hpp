#ifndef __PROJECTS_TGG_COMPONENT_DRAWABLE_HPP__
#define __PROJECTS_TGG_COMPONENT_DRAWABLE_HPP__


#include "window.hpp"
#include "component.hpp"

#include <SFML/Graphics.hpp>


class CDrawable : public Component
{
protected:
    std::size_t sort_order_;

public:
                 CDrawable    (Object* owner);
    virtual      ~CDrawable   ();
    
    virtual void Draw         (Window& window) = 0;
    void         SetSortOrder (std::size_t order);
    std::size_t  GetSortOrder () const;
};

#endif
