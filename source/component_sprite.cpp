#include "../include/component_sprite.hpp"
#include "../include/object.hpp"
#include "../include/component_transform.hpp"


CSprite::CSprite(Object* owner)
    : CDrawable           (owner)
    , current_texture_id_ {-1}
{}


void CSprite::Load(const std::string& filepath)
{
    if (texture_holder_)
    {
	int texture_id { texture_holder_->Add(filepath) };
	if (texture_id >= 0 && texture_id != current_texture_id_)
	{
	    current_texture_id_ = texture_id;
	    std::shared_ptr<sf::Texture> texture { texture_holder_->Get(texture_id) };
	    sprite_.setTexture(*texture);
	}
    }
}


void CSprite::Load(int id)
{
    if(id >= 0 && id != current_texture_id_)
    {
	current_texture_id_ = id;
	std::shared_ptr<sf::Texture> texture { texture_holder_->Get(id) };
	sprite_.setTexture(*texture);
    }
}


void CSprite::LateUpdate(float delta_time)
{
    sf::Vector2f        pos          { owner_ -> GetComponent<CTransform>() -> GetPosition() };
    const sf::IntRect&  spriteBounds { sprite_.getTextureRect() };
    const sf::Vector2f& spriteScale  { sprite_.getScale() };
    
    sprite_.setPosition( pos.x - ((abs(spriteBounds.width) * 0.5f) * spriteScale.x), 
			 pos.y - ((abs(spriteBounds.height) * 0.5f) * spriteScale.y) );
}


void CSprite::Draw(Window& window)
{
    window.Draw(sprite_);
}


void CSprite::SetTextureHolder(TextureHolder* holder)
{
    texture_holder_ = holder;
}



void CSprite::SetTextureRect(int x, int y, int width, int height)
{
    sprite_.setTextureRect(sf::IntRect(x, y, width, height));
}


void CSprite::SetTextureRect(const sf::IntRect& rect)
{
    sprite_.setTextureRect(rect);
}


void CSprite::SetScale(uint factor_x, uint factor_y)
{
    sprite_.setScale(factor_x, factor_y);
}
