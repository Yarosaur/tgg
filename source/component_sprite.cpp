#include "../include/component_sprite.hpp"


CSprite::CSprite(Object* owner)
    : Component(owner)
{}


void CSprite::Load(const std::string& filepath)
{
  if (texture_holder_)
    {
      int texture_id { texture_holder_->Add(filepath) };
      if (texture_id >= 0)
	{
	  std::shared_ptr<sf::Texture> texture { texture_holder_->Get(texture_id) };
	  sprite_.setTexture(*texture);
	}
    }
}


void CSprite::Load(int id)
{
  if(id >= 0)
    {
      std::shared_ptr<sf::Texture> texture { texture_holder_->Get(id) };
      sprite_.setTexture(*texture);
    }
}


void CSprite::LateUpdate(float delta_time)
{
    sprite_.setPosition(owner_ -> GetComponent<CTransform>() -> GetPosition());
}


void CSprite::Draw(Window& window)
{
    window.Draw(sprite_);
}


void CSprite::SetTextureHolder(TextureHolder* holder)
{
  texture_holder_ = holder;
}

