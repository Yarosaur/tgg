#ifndef __PROJECTS_TGG_COMPONENT_SPRITE_HPP__
#define __PROJECTS_TGG_COMPONENT_SPRITE_HPP__

#include "component.hpp"
#include "object.hpp"
#include "resource_holder.hpp"
#include "type_identifier.hpp"

class CSprite : public Component
{
private:
    TextureHolder* texture_holder_;
    sf::Sprite     sprite_;

public:
         CSprite          (Object* owner);
    void Load             (const std::string& filepath);
    void Load             (int id);
    void LateUpdate       (float delta_time)            override;
    void Draw             (Window& window)              override;
    void SetTextureHolder (TextureHolder* holder);
};

#endif
