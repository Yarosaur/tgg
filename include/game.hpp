#ifndef __PROJECTS_TGG_GAME_HPP__
#define __PROJECTS_TGG_GAME_HPP__

#include "window.hpp"
#include "working_directory.hpp"
#include "input.hpp"
#include "scene_state_machine.hpp"
#include "scene_splash_screen.hpp"
#include "scene_game.hpp"
#include "resource_holder.hpp"
#include "type_identifier.hpp"

class Game
{
public:
         Game               ();
    void Update             ();
    void LateUpdate         ();
    void Draw               ();
    bool IsRunning          () const;
    void CalculateDeltaTime ();
    void ProcessInput       ();

private:
    Window            window_;
    WorkingDirectory  working_dir_;
    sf::Clock         clock_;
    float             delta_time_;
    SceneStateMachine scene_state_machine_;
    TextureHolder     texture_holder_;
};

#endif
