#include "../include/debug.hpp"


std::vector<sf::RectangleShape>        Debug::rects_  {};
std::vector<std::array<sf::Vertex, 2>> Debug::lines_  {};


void Debug::Draw(Window& window)
{
    for (auto& rect : rects_)
    {
	window.Draw(rect);
    }
    rects_.clear();
    
    for (auto& l : lines_)
    {
	sf::Vertex line[2] = { l.at(0), l.at(1) };
	window.Draw(line, 2, sf::Lines);
    }
    lines_.clear();
}


void Debug::DrawRect(const sf::FloatRect& rect, sf::Color colour)
{
    sf::Vector2f       size  (rect.width, rect.height);
    sf::Vector2f       pos   (rect.left, rect.top);
    sf::RectangleShape shape (size);
    
    shape.setPosition(pos);
    shape.setOutlineColor(colour);
    shape.setOutlineThickness(3.f);
    shape.setFillColor(sf::Color::Transparent);
    rects_.push_back(shape);
}


void Debug::DrawLine(const sf::Vector2f& from, 
		     const sf::Vector2f& to, sf::Color colour)
{
    lines_.push_back({ sf::Vertex(from, colour),
		       sf::Vertex(to, colour) });
}


void Debug::Log(const std::string& msg)
{
    std::cout << msg << std::endl;
}


void Debug::LogWarning(const std::string& msg)
{
    std::cout << "WARNING: " << msg << std::endl;
}


void Debug::LogError(const std::string& msg)
{
    std::cout << "ERROR: " << msg << std::endl;
}
