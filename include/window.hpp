#ifndef __PROJECTS_TGG_WINDOW_HPP__
#define __PROJECTS_TGG_WINDOW_HPP__

#include <SFML/Graphics.hpp>

#include <string>

class Window
{
public:
                 Window    (const std::string& window_name);
    void         Update    ();
    void         BeginDraw ();
    void         Draw      (const sf::Drawable& drawable);
    void         EndDraw   ();
    bool         IsOpen    () const;
    sf::Vector2u GetCentre () const;

private:
    sf::RenderWindow window_;
};

#endif
