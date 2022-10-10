#include "../include/scene_game.hpp"
#include "../include/debug.hpp"
#include "../include/component_camera.hpp"


SceneGame::SceneGame(WorkingDirectory& working_dir,
		     TextureHolder& texture_holder,
		     Window& window)
    : working_dir_     {working_dir}
    , texture_holder_  {texture_holder}
    , tile_map_parser_ (texture_holder)
    , window_          {window}
{
}


void SceneGame::Create()
{
    auto player    { std::make_shared<Object>() };
    
    auto sprite    { player -> AddComponent<CSprite>() };
    sprite -> SetTextureHolder(&texture_holder_);
    sprite -> SetDrawLayer(DrawLayer::kEntities);

    auto movement  { player -> AddComponent<CKeyboardMovement>() };
    movement -> SetInput(&input_);

    auto animation { player -> AddComponent<CAnimation >() };
    std::map<FacingDirection, std::shared_ptr<Animation>> idle_animations;

    // Some hardcoded positions on texture
    const int kUpYFramePos    {512};
    const int kLeftYFramePos  {576};
    const int kDownYFramePos  {640};
    const int kRightYFramePos {704};
    
    FrameData temp_frame {};
    temp_frame.texture_id           = texture_holder_.Add(working_dir_.Get() +
							  "media/textures/player.png");
    // Idle Up Animations
    temp_frame.x                    = 0;
    temp_frame.y                    = 0;//kUpYFramePos;
    temp_frame.width                = 64;
    temp_frame.height               = 64;
    temp_frame.display_time_seconds = 0.f;
    
    auto idle_up_animation { std::make_shared<Animation>() };
    idle_up_animation->AddFrame(temp_frame);
    idle_animations.insert(std::make_pair(FacingDirection::kUp, idle_up_animation));

    // Idle Left Animations
    temp_frame.y = kLeftYFramePos;
    
    auto idle_left_animation { std::make_shared<Animation>() };
    idle_left_animation->AddFrame(temp_frame);
    idle_animations.insert(std::make_pair(FacingDirection::kLeft, idle_left_animation));

    // Idle Down Animations
    temp_frame.y = kDownYFramePos;
    
    auto idle_down_animation { std::make_shared<Animation>() };
    idle_down_animation->AddFrame(temp_frame);
    idle_animations.insert(std::make_pair(FacingDirection::kDown, idle_down_animation));

    // Idle Right Animations
    temp_frame.y = kRightYFramePos;
    
    auto idle_right_animation { std::make_shared<Animation>() };
    idle_left_animation->AddFrame(temp_frame);
    idle_animations.insert(std::make_pair(FacingDirection::kRight, idle_right_animation));


    // Walking Up Animations
    temp_frame.display_time_seconds = 0.2f;
    std::size_t walking_frame_count {9};
    std::map<FacingDirection, std::shared_ptr<Animation>> walking_animations;
    auto walk_up_animation { std::make_shared<Animation>() };
    for (std::size_t i {0}; i < walking_frame_count; i++)
    {
	temp_frame.x = i * temp_frame.width;
	temp_frame.y = kUpYFramePos;
	walk_up_animation->AddFrame(temp_frame);
    }
    walking_animations.insert(std::make_pair(FacingDirection::kUp, walk_up_animation));

    // Walking Left Animations
    auto  walk_left_animation { std::make_shared<Animation>() };
    for (std::size_t i {0}; i < walking_frame_count; i++)
    {
	temp_frame.x = i * temp_frame.width;
	temp_frame.y = kLeftYFramePos;
	walk_left_animation->AddFrame(temp_frame);
    }
    walking_animations.insert(std::make_pair(FacingDirection::kLeft, walk_left_animation));

    // Walking Down Animations
    auto  walk_down_animation { std::make_shared<Animation>() };
    for (std::size_t i {0}; i < walking_frame_count; i++)
    {
	temp_frame.x = i * temp_frame.width;
	temp_frame.y = kDownYFramePos;
	walk_down_animation->AddFrame(temp_frame);
    }
    walking_animations.insert(std::make_pair(FacingDirection::kDown, walk_down_animation));

    // Walking Right Animations
    auto  walk_right_animation { std::make_shared<Animation>() };
    for (std::size_t i {0}; i < walking_frame_count; i++)
    {
	temp_frame.x = i * temp_frame.width;
	temp_frame.y = kRightYFramePos;
	walk_right_animation->AddFrame(temp_frame);
    }
    walking_animations.insert(std::make_pair(FacingDirection::kRight, walk_right_animation));
    
    animation->AddAnimation(AnimationState::kWalk, walking_animations);

    
    auto collider  { player->AddComponent<CBoxCollider>() };
    collider->SetCollidable(sf::FloatRect(0, 0, temp_frame.width, temp_frame.height));
    collider->SetSize(temp_frame.width * 0.4f, temp_frame.height * 0.5f);
    collider->SetOffset(0.f, 14.f);
    collider->SetLayer(CollisionLayer::kPlayer);

    auto camera { player->AddComponent<CCamera>() };
    camera->SetWindow(&window_);
    
    objects_.Add(player);

    sf::Vector2i tile_map_offset(0, 32);
    std::vector<std::shared_ptr<Object>> level_tiles 
	= tile_map_parser_.ParseXML(working_dir_.Get() + "media/tilemaps/path.tmx", tile_map_offset);
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
    objects_.ProcessRemovals();
    objects_.ProcessNewObjects();
    objects_.Update(delta_time);

    Debug::HandleCameraZoom(window_, input_);
}


void SceneGame::LateUpdate(float delta_time)
{
    objects_.LateUpdate(delta_time);
}


void SceneGame::Draw(Window& window)
{
    objects_.Draw(window);
    Debug::Draw(window);
}
