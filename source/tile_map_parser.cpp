#include "../include/tile_map_parser.hpp"
#include "../include/component_transform.hpp"
#include "../include/component_box_collider.hpp"

#include <cstring>

TileMapParser::TileMapParser(TextureHolder& texture_holder)
    : texture_holder_ {texture_holder}
{}


std::vector<std::shared_ptr<Object>>  TileMapParser::ParseXML(const std::string& file,
							      sf::Vector2i offset)
{
    char* file_loc = new char[file.size() + 1];

    //TODO: make multi format version of string copy
#ifdef MACOS
    strlcpy(file_loc, file.c_str(), file.size() + 1); 
#else
    strcpy(file_loc, file.c_str());
#endif
    
    //TODO: error checking - check file exists before attempting open.
    rapidxml::file<>         xml_file  (file_loc);
    rapidxml::xml_document<> doc;
    doc.parse<0>(xml_file.data());
    rapidxml::xml_node<>*    root_node { doc.first_node("map") };

    // Loads tile layers from XML.
    std::shared_ptr<TileMap> tile_map { BuildTileMap(root_node) };
    
    // We need these to calculate the tiles position in world space
    int tile_size_x { std::atoi(root_node->first_attribute("tilewidth")->value()) };
    int tile_size_y { std::atoi(root_node->first_attribute("tileheight")->value()) };
    int map_size_x  { std::atoi(root_node->first_attribute("width")->value()) };
    int map_size_y  { std::atoi(root_node->first_attribute("height")->value()) };
    
    // This will contain all of our tiles as objects.
    std::vector<std::shared_ptr<Object>> tile_objects;

    // We iterate through each layer in the tile map
    std::size_t layer_count { tile_map->size() - 1 };
    for (const auto& layer : *tile_map)
     {
        // And each tile in the layer
	 for (const auto& tile : layer.second->tiles)
	{
	    std::shared_ptr<TileInfo> tile_info   { tile->properties };
	    std::shared_ptr<Object>   tile_object { std::make_shared<Object>() };
            //TODO: tile scale should be set at the data level.
	    const unsigned int        tile_scale  { 3 };

            // Allocate sprite for visible layer.
	    if (layer.second->is_visible)
	    {
		auto sprite { tile_object->AddComponent<CSprite>() };
		sprite->SetTextureHolder(&texture_holder_);
		sprite->Load(tile_info->texture_id);
		sprite->SetTextureRect(tile_info->texture_rect);
		sprite->SetScale(tile_scale, tile_scale);
		sprite->SetSortOrder(layer_count);
		sprite->SetDrawLayer(DrawLayer::kBackground);
	    }
	    
            // Calculate world position.
	    float x { tile->tile_grid_x * tile_size_x * tile_scale + offset.x };
	    float y { tile->tile_grid_y * tile_size_y * tile_scale + offset.y };
	    tile_object->GetComponent<CTransform>()->SetPosition(x, y);

            // Add new tile Object to the collection.
	    if (layer.first == "Collision")
	    {
		auto  collider { tile_object->AddComponent<CBoxCollider>() };
		float left     { x - (tile_size_x * tile_scale) * 0.5f };
		float top      { y - (tile_size_y * tile_scale) * 0.5f };
		float width    { tile_size_x * tile_scale };
		float height   { tile_size_y * tile_scale };
		collider->SetCollidable(sf::FloatRect(left, top, width, height));
		collider->SetLayer(CollisionLayer::kTile);
	    }
	    tile_objects.emplace_back(tile_object);
	}
	layer_count--;
    }

    delete[] file_loc;
    
    return tile_objects;
}


std::shared_ptr<TileSheets> TileMapParser::BuildTileSheetData(rapidxml::xml_node<> *root_node)
{
    TileSheets tile_sheets;
    // Traverse to the tile set node.
    
    for (rapidxml::xml_node<>* tile_sheet_node { root_node->first_node("tileset") }; 
	 tile_sheet_node; tile_sheet_node = tile_sheet_node -> next_sibling("tileset"))
    {
	TileSheetData tile_sheet_data;

	//TODO: add error checking to ensure these values actually exist.
        //TODO: add support for multiple tile sets.

	int first_id { std::atoi(tile_sheet_node->first_attribute("firstgid")->value()) };

	// Build the tile set data.
	tile_sheet_data.tile_size.x = std::atoi(tile_sheet_node->first_attribute("tilewidth")->value());
	tile_sheet_data.tile_size.y = std::atoi(tile_sheet_node->first_attribute("tileheight")->value());

	int tile_count { std::atoi(tile_sheet_node->first_attribute("tilecount")->value()) };
	tile_sheet_data.columns = std::atoi(tile_sheet_node->first_attribute("columns")->value());
	tile_sheet_data.rows    = tile_count / tile_sheet_data.columns;
	
	rapidxml::xml_node<>* image_node { tile_sheet_node->first_node("image") };
	tile_sheet_data.texture_id =
	    texture_holder_.Add(std::string(image_node->first_attribute("source")->value()) );

	//TODO: add error checking - we want to output a message if the texture is not found.

	tile_sheet_data.image_size.x = std::atoi(image_node->first_attribute("width")->value());
	tile_sheet_data.image_size.y = std::atoi(image_node->first_attribute("height")->value());

	// We store the tile sheets firstid.
	tile_sheets.insert( std::make_pair(first_id, std::make_shared<TileSheetData>(tile_sheet_data)) );
	
    }
    
    return std::make_shared<TileSheets>(tile_sheets);
}



std::shared_ptr<TileMap> TileMapParser::BuildTileMap(rapidxml::xml_node<>* root_node)
{
    std::shared_ptr<TileSheets>  tile_sheets  { BuildTileSheetData(root_node) };
    std::shared_ptr<TileMap>     tile_map     { std::make_shared<TileMap>() };

    // We loop through each layer in the XML document.
    for (rapidxml::xml_node<> * node { root_node->first_node("layer") }; node;
	 node = node->next_sibling())
    {
	std::pair<std::string, std::shared_ptr<TileLayer>> tile_map_layer { BuildTileLayer(node, tile_sheets) };
	tile_map->emplace(tile_map_layer);
    }
    return tile_map;
}



std::pair<std::string, std::shared_ptr<TileLayer>> 
TileMapParser::BuildTileLayer(rapidxml::xml_node<>* layer_node, 
			      std::shared_ptr<TileSheets> tile_sheets)
{
    TileSet tile_set;
    auto layer  { std::make_shared<TileLayer>() };
    int  width  { std::atoi(layer_node->first_attribute("width")->value()) };
    int  height { std::atoi(layer_node->first_attribute("height")->value()) };
    
    rapidxml::xml_node<>* data_node   { layer_node->first_node("data") };
    char*                 map_indices { data_node->value() };
    std::stringstream     data_stream ( map_indices );
    
    int         count {0};
    std::string line  {};
    while (data_stream.good())
    {
	std::string substr {};
	std::getline(data_stream, substr, ',');
	if (!utilities::IsInteger(substr)) 
	{
            // We remove special characters from the int before parsing
	    substr.erase(std::remove(substr.begin(), substr.end(), '\r'), substr.end()); 
	    substr.erase(std::remove(substr.begin(), substr.end(), '\n'), substr.end());

            //TODO: add additional check to 
            //confirm that the character removals have worked:
	}
	
	int tile_id { std::stoi(substr) };
	if (tile_id != 0) 
	{
	    auto itr { tile_set.find(tile_id) };
	    if (itr == tile_set.end()) 
	    {
		std::shared_ptr<TileSheetData> tile_sheet_data;
		for (auto iter { tile_sheets->rbegin() }; iter != tile_sheets->rend(); ++iter)
		{
		    if(tile_id >= iter->first)
		    {
                        // We know the tile belongs to this tileset.
			tile_sheet_data = iter->second;
			break;
		    }
		}
		
		if(!tile_sheet_data)
		{
                    //TODO: output error message.
		    continue;
		}
	    
		int  texture_x { tile_id % tile_sheet_data->columns - 1 };
		int  texture_y { tile_id / tile_sheet_data->columns };
		auto tile_info { std::make_shared<TileInfo>(tile_sheet_data->texture_id, tile_id, 
							    sf::IntRect(texture_x * tile_sheet_data->tile_size.x, 
									texture_y * tile_sheet_data->tile_size.y, 
									tile_sheet_data->tile_size.x, 
									tile_sheet_data->tile_size.y)) };
		
		itr = tile_set.insert(std::make_pair(tile_id, tile_info)).first;
	    }
	    
	    auto tile { std::make_shared<Tile>() };
	    // Bind properties of a tile from a set.
	    tile->properties  = itr->second;
	    tile->tile_grid_x = count % width - 1;
	    tile->tile_grid_y = count / width;
	    layer->tiles.emplace_back(tile); 
	}
	count++;
    }
    
    const std::string layer_name { layer_node->first_attribute("name")->value() };

    // Check layer visibility
    bool layer_visible { true };
    rapidxml::xml_attribute<>* visible_attribute { layer_node->first_attribute("visible") };
    if(visible_attribute)
    {
	layer_visible = std::stoi(visible_attribute->value());
    }
    layer->is_visible = layer_visible;
    
    return std::make_pair(layer_name, layer);
}


