#ifndef __PROJECTS_TGG_COMPONENT_CAMERA_HPP__
#define __PROJECTS_TGG_COMPONENT_CAMERA_HPP__


#include "component.hpp"


class CCamera : public Component
{
private:
    Window* window_;
    
public:
         CCamera    (Object* owner);
    void LateUpdate (float delta_time) override;
    void SetWindow  (Window* game_window);
};
#endif 
