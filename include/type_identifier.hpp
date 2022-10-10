#ifndef __PROJECTS_TGG_TYPE_IDENTIFIER_HPP__
#define __PROJECTS_TGG_TYPE_IDENTIFIER_HPP__

#include "resource_holder.hpp"
#include "tile.hpp"

#include <SFML/Graphics.hpp>

#include <vector>
#include <map>
#include <unordered_map>
#include <memory>

struct     TileSheetData;
struct     TileLayer;
enum class FacingDirection;
class      Animation;

// ResourceHolders
using TextureHolder   = ResourceHolder<sf::Texture>;
using FontHolder      = ResourceHolder<sf::Font>;

// Tiles
using TileMap         = std::vector<std::pair<std::string, std::shared_ptr<TileLayer>>>;
using TileSet         = std::unordered_map<unsigned int, std::shared_ptr<TileInfo>>;
using TileSheets      = std::map<int, std::shared_ptr<TileSheetData>>;

// Animation
using AnimationList   = std::map<FacingDirection, std::shared_ptr<Animation>>;
using AnimationAction = std::function<void(void)>;

#endif
