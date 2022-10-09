#ifndef __PROJECTS_TGG_COMPONENT_DRAWABLE_HPP__
#define __PROJECTS_TGG_COMPONENT_DRAWABLE_HPP__


#include "window.hpp"
#include "component.hpp"

#include <SFML/Graphics.hpp>

#include <memory>


enum class DrawLayer
{
    kDefault,
    kBackground,
    kForeground,
    kEntities
};


class CDrawable : public Component
{
protected:
    DrawLayer   layer_;
    std::size_t sort_order_;

public:
                 CDrawable    (Object* owner);
    virtual      ~CDrawable   ();
    
    virtual void Draw         (Window& window) = 0;
    void         SetSortOrder (std::size_t order);
    std::size_t  GetSortOrder () const;
    void         SetDrawLayer (DrawLayer draw_layer);
    DrawLayer    GetDrawLayer () const;
};

#endif
