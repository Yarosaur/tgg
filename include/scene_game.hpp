#ifndef __PROJECTS_TGG_SCENE_GAME_HPP__
#define __PROJECTS_TGG_SCENE_GAME_HPP__

#include "scene.hpp"
#include "input.hpp"
#include "working_directory.hpp"
#include "object.hpp"
#include "component_sprite.hpp"
#include "component_keyboard_movement.hpp"
#include "resource_holder.hpp"
#include "type_identifier.hpp"

class SceneGame : public Scene
{
  private:
    std::shared_ptr<Object> player_;
    WorkingDirectory&       working_dir_;
    Input                   input_;
    TextureHolder&          texture_holder_;
  
public:
         SceneGame    (WorkingDirectory& workingDir,
		       TextureHolder& texture_holder);
  
    void Create       ()                 override;
    void Destroy      ()                 override;
    void ProcessInput ()                 override;
    void Update       (float delta_time) override;
    void LateUpdate   (float delta_time) override;
    void Draw         (Window& window)   override;
};

#endif // __PROJECTS_TGG_SCENE_GAME_HPP__
