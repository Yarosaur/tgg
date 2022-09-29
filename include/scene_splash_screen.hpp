#ifndef __PROJECTS_TGG_SCENE_SPLASH_SCREEN_HPP__
#define __PROJECTS_TGG_SCENE_SPLASH_SCREEN_HPP__

#include "window.hpp"
#include "scene_state_machine.hpp"
#include "working_directory.hpp"
#include "resource_holder.hpp"
#include "type_identifier.hpp"

#include <SFML/Graphics.hpp>

class SceneSplashScreen : public Scene
{
  private:
    WorkingDirectory&  working_dir_;
    SceneStateMachine& scene_state_machine_;
    Window&            window_;
    // The state we want to transition to when this scenes time expires.
    uint               switch_to_scene_;
    // We want to show this scene for a set amount of time
    float              show_for_seconds_;
    // How long the scene has currently been visible.
    float              current_seconds_;
    TextureHolder&     texture_holder_;
    sf::Sprite         splash_sprite_;
public:
         SceneSplashScreen(WorkingDirectory&  working_dir,
			   SceneStateMachine& scene_state_machine,
			   Window&            window,
			   TextureHolder&     texture_holder);

    void Create           ()                 override;
    void Destroy          ()                 override;
    void Activate         ()                 override;
    void SetSwitchToScene (uint id);
    void Update           (float delta_time) override;
    void Draw             (Window& window)   override;
};

#endif
