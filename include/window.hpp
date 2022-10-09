#ifndef __PROJECTS_TGG_WINDOW_HPP__
#define __PROJECTS_TGG_WINDOW_HPP__

#include <SFML/Graphics.hpp>

#include <string>

class Window
{
private:
    sf::RenderWindow window_;

public:
                    Window       (const std::string& window_name);
    void            Update       ();
    void            BeginDraw    ();
    void            Draw         (const sf::Drawable& drawable);
    void            Draw         (const sf::Vertex* vertices,
				  std::size_t       vertex_count,
				  sf::PrimitiveType type);
    void            EndDraw      ();
    bool            IsOpen       () const;
    sf::Vector2u    GetCentre    () const;
    const sf::View& GetView      () const;
    void            SetView      (const sf::View& view);
    sf::FloatRect   GetViewSpace () const;

};

#endif
