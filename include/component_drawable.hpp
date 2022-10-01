#ifndef __PROJECTS_TGG_COMPONENT_DRAWABLE_HPP__
#define __PROJECTS_TGG_COMPONENT_DRAWABLE_HPP__


#include "window.hpp"

#include <SFML/Graphics.hpp>


class CDrawable
{
protected:
    int sort_order_;

public:
                 CDrawable    ();
    virtual      ~CDrawable   ();
    
    virtual void Draw         (Window& window) = 0;
    void         SetSortOrder (int order);
    int          GetSortOrder () const;
};

#endif
