#include "../include/scene_game.hpp"

SceneGame::SceneGame(WorkingDirectory& working_dir, TextureHolder& texture_holder)
    : working_dir_    {working_dir}
    , texture_holder_ {texture_holder}
{
}


void SceneGame::Create()
{
    player_ = std::make_shared<Object>();
    
    auto sprite   { player_ -> AddComponent<CSprite>() };
    sprite->SetTextureHolder(&texture_holder_);
    sprite -> Load(working_dir_.Get() + "media/textures/viking.png");

    auto movement { player_ -> AddComponent<CKeyboardMovement>() };
    movement -> SetInput(&input_);
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
    player_ -> Update(delta_time);
}


void SceneGame::LateUpdate(float delta_time)
{
    player_ -> LateUpdate(delta_time);
}


void SceneGame::Draw(Window& window)
{
    player_ -> Draw(window);
}
