#ifndef __PROJECTS_TGG_TYPE_IDENTIFIER_HPP__
#define __PROJECTS_TGG_TYPE_IDENTIFIER_HPP__

#include "resource_holder.hpp"
#include "tile.hpp"

#include <SFML/Graphics.hpp>

#include <vector>
#include <map>
#include <memory>

struct TileSheetData;

// ResourceHolders
using TextureHolder = ResourceHolder<sf::Texture>;
using FontHolder    = ResourceHolder<sf::Font>;

// Tiles
using TileLayer     = std::vector<std::shared_ptr<Tile>>;
using TileMap       = std::map<std::string, std::shared_ptr<TileLayer>>;
using TileSet       = std::unordered_map<unsigned int, std::shared_ptr<TileInfo>>;
using TileSheets    = std::map<int, std::shared_ptr<TileSheetData>>;


#endif
