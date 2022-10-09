#include "../include/game.hpp"

Game::Game()
    : window_ ("Test")
{
    auto splash_screen { std::make_shared<SceneSplashScreen>(working_dir_,
							     scene_state_machine_,
							     window_,
							     texture_holder_) };

    auto scene_game    { std::make_shared<SceneGame>(working_dir_, texture_holder_, window_)};
    
    unsigned int splash_screen_id { scene_state_machine_.Add(splash_screen) }; 
    unsigned int scene_game_id    { scene_state_machine_.Add(scene_game) };
    
    splash_screen->SetSwitchToScene(scene_game_id);
    scene_state_machine_.SwitchTo(splash_screen_id);
    
    delta_time_ = clock_.restart().asSeconds();
}

void Game::Update()
{
    window_.Update();
    scene_state_machine_.Update(delta_time_);
}


void Game::LateUpdate()
{
     scene_state_machine_.LateUpdate(delta_time_);
}


void Game::Draw()
{
    window_.BeginDraw();
    scene_state_machine_.Draw(window_);
    window_.EndDraw();
}


bool Game::IsRunning() const
{
    return window_.IsOpen();
}


void Game::CalculateDeltaTime()
{
    delta_time_ = clock_.restart().asSeconds();
}


void Game::ProcessInput()
{
   scene_state_machine_.ProcessInput();
}


