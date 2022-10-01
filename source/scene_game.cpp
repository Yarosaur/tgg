#include "../include/scene_game.hpp"

SceneGame::SceneGame(WorkingDirectory& working_dir, TextureHolder& texture_holder)
    : working_dir_     {working_dir}
    , texture_holder_  {texture_holder}
    , tile_map_parser_ (texture_holder)
{
}


void SceneGame::Create()
{
    auto player    { std::make_shared<Object>() };
    
    auto sprite    { player -> AddComponent<CSprite>() };
    sprite -> SetTextureHolder(&texture_holder_);

    auto movement  { player -> AddComponent<CKeyboardMovement>() };
    movement -> SetInput(&input_);

    auto animation { player -> AddComponent<CAnimation >() };
    
    auto idle_animation { std::make_shared<Animation>(FacingDirection::kRight) };

    FrameData temp_frame {};
    temp_frame.texture_id           = texture_holder_.Add(working_dir_.Get() +
							  "media/textures/viking.png");
    temp_frame.x                    = 600;
    temp_frame.y                    = 0;
    temp_frame.width                = 200;
    temp_frame.height               = 145;
    temp_frame.display_time_seconds = 0.2f;
    idle_animation -> AddFrame(temp_frame);

    temp_frame.x = 800;
    temp_frame.y = 0;
    idle_animation -> AddFrame(temp_frame);

    temp_frame.x = 0;
    temp_frame.y = 145;
    idle_animation -> AddFrame(temp_frame);

    temp_frame.x = 200;
    temp_frame.y = 145;
    idle_animation -> AddFrame(temp_frame);
    
    animation->AddAnimation(AnimationState::kIdle, idle_animation);

    auto walk_animation { std::make_shared<Animation>(FacingDirection::kRight) };
    
    temp_frame.x                    = 600;
    temp_frame.y                    = 290;
    temp_frame.display_time_seconds = 0.15f;
    walk_animation -> AddFrame(temp_frame);

    
    temp_frame.x = 800;
    temp_frame.y = 290;
    walk_animation -> AddFrame(temp_frame);
    
    temp_frame.x = 0;
    temp_frame.y = 435;
    walk_animation -> AddFrame(temp_frame);
    
    temp_frame.x = 200;
    temp_frame.y = 435;
    walk_animation -> AddFrame(temp_frame);
    
    temp_frame.x = 400;
    temp_frame.y = 435;
    walk_animation -> AddFrame(temp_frame);
    
    temp_frame.x = 600;
    temp_frame.y = 435;
    walk_animation -> AddFrame(temp_frame);

    animation->AddAnimation(AnimationState::kWalk, walk_animation);
    
    objects_.Add(player);

    sf::Vector2i tile_map_offset(0, 32);
    std::vector<std::shared_ptr<Object>> level_tiles 
	= tile_map_parser_.ParseXML(working_dir_.Get() + "media/tilemaps/test.xml", tile_map_offset);
    for (std::size_t i {0}; i < level_tiles.size(); ++i)
    {
	objects_.Add(level_tiles[i]);
    }
}


void SceneGame::Destroy()
{
}


void SceneGame::ProcessInput()
{
    input_.Update();
}


void SceneGame::Update(float delta_time)
{
    objects_.ProcessNewObjects();
    objects_.Update(delta_time);
}


void SceneGame::LateUpdate(float delta_time)
{
    objects_.LateUpdate(delta_time);
}


void SceneGame::Draw(Window& window)
{
    objects_.Draw(window);
}
