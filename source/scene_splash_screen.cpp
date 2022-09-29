#include "../include/scene_splash_screen.hpp"
SceneSplashScreen::SceneSplashScreen(WorkingDirectory&  working_dir, 
				     SceneStateMachine& scene_state_machine,
				     Window&            window,
				     TextureHolder&     texture_holder) 
    : working_dir_         {working_dir}
    , scene_state_machine_ {scene_state_machine}
    , window_              {window}
    , switch_to_scene_     {0}
    , show_for_seconds_    {3.f} // We’ll show this splash screen for 3 seconds.
    , current_seconds_     {0.f}
    , texture_holder_      {texture_holder}
{}


void SceneSplashScreen::Create() 
{
    // We’ll initialise our splash screen image here.
    int splash_texture_id { texture_holder_.Add(working_dir_.Get() +
					        "media/textures/fennec.png") };
    if (splash_texture_id >= 0)
    {
        std::shared_ptr<sf::Texture> splash_texture {texture_holder_.Get(splash_texture_id)};
        splash_sprite_.setTexture(*splash_texture);
	
	// Set the origin of the sprite to the centre of the image:
	sf::FloatRect sprite_size { splash_sprite_.getLocalBounds() };
	splash_sprite_.setOrigin(sprite_size.width * 0.5f, sprite_size.height * 0.5f);
	splash_sprite_.setScale(0.5f, 0.5f);

	// Positions sprite in centre of screen:
	sf::Vector2u window_centre { window_.GetCentre() };
	splash_sprite_.setPosition(window_centre.x, window_centre.y);
    }
}


void SceneSplashScreen::Activate()
{
    // Resets the currentSeconds count whenever the scene is activated.
    current_seconds_ = 0.f; 
}


void SceneSplashScreen::Destroy() { }


void SceneSplashScreen::SetSwitchToScene(uint id) 
{
    // Stores the id of the scene that we will transition to.
    switch_to_scene_ = id; 
}


void SceneSplashScreen::Update(float delta_time)
{
    current_seconds_ += delta_time;
    if(current_seconds_ >= show_for_seconds_) 
    {
        // Switches states.
	scene_state_machine_.SwitchTo(switch_to_scene_); 
    }
}


void SceneSplashScreen::Draw(Window& window)
{
    window.Draw(splash_sprite_);
}
