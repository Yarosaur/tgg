#ifndef __PROJECTS_TGG_COMPONENT_TRANSFORM_HPP__
#define __PROJECTS_TGG_COMPONENT_TRANSFORM_HPP__

#include "component.hpp"


class CTransform : public Component
{
private:
    sf::Vector2f position_;
 
public:
                 CTransform   (Object* owner);
    void         SetPosition  (float x, float y);
    void         SetPosition  (sf::Vector2f pos);
    void         AddPosition  (float x, float y);
    void         AddPosition  (sf::Vector2f pos);
    void         SetX         (float x);
    void         SetY         (float y);
    sf::Vector2f GetPosition  () const;
};

#endif
