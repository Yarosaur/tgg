#include "../include/component_camera.hpp"
#include "../include/object.hpp"
#include "../include/component_transform.hpp"

CCamera::CCamera(Object* owner) : Component(owner) {}

void CCamera::LateUpdate(float delta_time)
{
    if(window_)
    {
	sf::View view { window_->GetView() };
	const sf::Vector2f& target_pos { GetOwner()->
		GetComponent<CTransform>()->GetPosition() };
	//TODO: remove hard-coding of y value
	view.setCenter(target_pos.x, 500);
	window_->SetView(view);
    }
}


void CCamera::SetWindow(Window* game_window)
{
    window_ = game_window;
}
