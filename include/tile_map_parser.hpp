#ifndef __PROJECTS_TGG_TILE_MAP_PARSER_HPP__
#define __PROJECTS_TGG_TILE_MAP_PARSER_HPP__


#include "tile.hpp"
#include "utilities.hpp"
#include "object.hpp"
#include "component_sprite.hpp"
#include "type_identifier.hpp"

#include "../3rdparty/rapidxml-1.13/rapidxml.hpp"
#include "../3rdparty/rapidxml-1.13/rapidxml.hpp"
#include "../3rdparty/rapidxml-1.13/rapidxml_utils.hpp"
#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <sstream>

struct TileSheetData
{
    int          texture_id;  
    sf::Vector2u image_size; // The size of the texture.
    int          columns;    // How many columns in the tile sheet.
    int          rows;       // How many rows in the tile sheet.
    sf::Vector2u tile_size;  // The size of an individual tile.
};


class TileMapParser
{
private:
    TextureHolder& texture_holder_;

private:
    // reads the XML file and loads in the tileset used
    std::shared_ptr<TileSheets>           BuildTileSheetData (rapidxml::xml_node<>* root_node);
    // returns the data for each tile in each layer
    std::shared_ptr<TileMap>              BuildTileMap       (rapidxml::xml_node<>* root_node);
    // creates and returns the data for one layer within the tile map
    std::pair<std::string,
	      std::shared_ptr<TileLayer>> BuildTileLayer     (rapidxml::xml_node<>* layer_node,
							      std::shared_ptr<TileSheets> tile_sheets);
public:
                                          TileMapParser      (TextureHolder& texture_holder);
    std::vector<std::shared_ptr<Object>>  ParseXML           (const std::string& file, sf::Vector2i offset);
    
};


#endif
