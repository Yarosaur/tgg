#ifndef __PROJECTS_TGG_DEBUG_HPP__
#define __PROJECTS_TGG_DEBUG_HPP__


#include "window.hpp"

#include <SFML/Graphics.hpp>

#include <array>
#include <vector>
#include <iostream>
#include <functional>


class Debug
{
private:
    static std::vector<std::array<sf::Vertex, 2>> lines_;
    static std::vector<sf::RectangleShape>        rects_;
    
public:
    static void Draw       (Window& window);
    static void DrawRect   (const sf::FloatRect& rect, 
			    sf::Color colour = sf::Color::White);
    static void DrawLine   (const sf::Vector2f& from, 
			    const sf::Vector2f& to, 
			    sf::Color colour = sf::Color::White);
    static void Log        (const std::string& msg);
    static void LogWarning (const std::string& msg);
    static void LogError   (const std::string& msg);

};
#endif 
