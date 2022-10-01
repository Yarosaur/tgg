#ifndef __PROJECTS_TGG_TILE_HPP__
#define __PROJECTS_TGG_TILE_HPP__

#include "resource_holder.hpp"

#include <SFML/Graphics/Rect.hpp>

struct TileInfo
{
    int         texture_id;
    int         tile_id;
    sf::IntRect texture_rect;

    
    TileInfo()
	: tile_id {-1}
    {}

    
    TileInfo(int set_texture_id, uint set_tile_id, sf::IntRect set_texture_rect)
	: texture_id   {set_texture_id}
	, tile_id      {set_tile_id}
	, texture_rect {set_texture_rect}
    {}
};


struct Tile
{
    std::shared_ptr<TileInfo> properties;
    int                       tile_grid_x;
    int                       tile_grid_y;
};

#endif

