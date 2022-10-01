#ifndef __PROJECTS_TGG_COMPONENT_SPRITE_HPP__
#define __PROJECTS_TGG_COMPONENT_SPRITE_HPP__

#include "component.hpp"
#include "component_drawable.hpp"
#include "resource_holder.hpp"
#include "type_identifier.hpp"

class CSprite : public Component, public CDrawable
{
private:
    TextureHolder* texture_holder_;
    int            current_texture_id_;
    sf::Sprite     sprite_;

public:
         CSprite          (Object* owner);
    void Load             (const std::string& filepath);
    void Load             (int id);
    void LateUpdate       (float delta_time)                   override;
    void Draw             (Window& window)                     override;
    void SetTextureHolder (TextureHolder* holder);
    void SetTextureRect   (int x, int y, int width, int height);
    void SetTextureRect   (const sf::IntRect& rect);
    void SetScale         (uint factor_x, uint factor_y);
};

#endif
