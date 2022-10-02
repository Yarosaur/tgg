#ifndef __PROJECTS_TGG_COMPONENT_INSTANCE_ID_HPP__
#define __PROJECTS_TGG_COMPONENT_INSTANCE_ID_HPP__

#include "component.hpp"


class CInstanceID : public Component
{
private:
    static std::size_t count_;
    std::size_t        id_;
    
public:
                CInstanceID  (Object* owner);
                ~CInstanceID ();
    std::size_t GetID        () const;
};


#endif
