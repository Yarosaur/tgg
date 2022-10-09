#include "../include/input.hpp"

void Input::Update()
{
    // record previous keys input
    prev_frame_keys_.reset();
    prev_frame_keys_ |= curr_frame_keys_;

    // record current keys input
    curr_frame_keys_.set(static_cast<std::size_t>(Key::kLeft),
			 sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
			 sf::Keyboard::isKeyPressed(sf::Keyboard::A));

    curr_frame_keys_.set(static_cast<std::size_t>(Key::kRight),
			 sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
			 sf::Keyboard::isKeyPressed(sf::Keyboard::D));

    curr_frame_keys_.set(static_cast<std::size_t>(Key::kUp),
			 sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
			 sf::Keyboard::isKeyPressed(sf::Keyboard::W));

    curr_frame_keys_.set(static_cast<std::size_t>(Key::kDown),
			 sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
			 sf::Keyboard::isKeyPressed(sf::Keyboard::S));

    curr_frame_keys_.set(static_cast<std::size_t>(Key::kEsc),
			 sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));

    curr_frame_keys_.set(static_cast<std::size_t>(Key::kLBracket), 
			 sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket));
    
    curr_frame_keys_.set(static_cast<std::size_t>(Key::kRBracket), 
			 sf::Keyboard::isKeyPressed(sf::Keyboard::RBracket));
}


bool Input::IsKeyPressed(Key keycode)
{
    return curr_frame_keys_.test(static_cast<std::size_t>(keycode));
}


bool Input::IsKeyDown(Key keycode)
{
    bool prev_frame {prev_frame_keys_.test(static_cast<std::size_t>(keycode))};
    bool curr_frame {curr_frame_keys_.test(static_cast<std::size_t>(keycode))};

    return curr_frame && !prev_frame;
}


bool Input::IsKeyUp(Key keycode)
{
    bool prev_frame {prev_frame_keys_.test(static_cast<std::size_t>(keycode))};
    bool curr_frame {curr_frame_keys_.test(static_cast<std::size_t>(keycode))};

    return !curr_frame && prev_frame;
}
