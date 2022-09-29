#include "../include/window.hpp"

Window::Window(const std::string& window_name)
    : window_ (sf::VideoMode(800, 600), window_name)
{
    window_.setVerticalSyncEnabled(true);
}


void Window::Update()
{
    sf::Event event;
    while (window_.pollEvent(event))
    {
	if (event.type == sf::Event::Closed)
	{
	    window_.close();
	}
    }
}


void Window::BeginDraw()
{
    window_.clear(sf::Color::White);
}


void Window::Draw(const sf::Drawable& drawable)
{
    window_.draw(drawable);
}


void Window::EndDraw()
{
    window_.display();
}


bool Window::IsOpen() const
{
    return window_.isOpen();
}


sf::Vector2u Window::GetCentre() const
{
    sf::Vector2u size   { window_.getSize() };
    sf::Vector2u centre (size.x / 2, size.y / 2);
    return centre;
}
