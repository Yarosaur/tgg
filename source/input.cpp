#include "../include/input.hpp"

void Input::Update()
{
    // record previous keys input
    prev_frame_keys_.reset();
    prev_frame_keys_ |= curr_frame_keys_;

    // record current keys input
    curr_frame_keys_.set(static_cast<std::size_t>(Key::Left),
			 sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
			 sf::Keyboard::isKeyPressed(sf::Keyboard::A));

    curr_frame_keys_.set(static_cast<std::size_t>(Key::Right),
			 sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
			 sf::Keyboard::isKeyPressed(sf::Keyboard::D));

    curr_frame_keys_.set(static_cast<std::size_t>(Key::Up),
			 sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
			 sf::Keyboard::isKeyPressed(sf::Keyboard::W));

    curr_frame_keys_.set(static_cast<std::size_t>(Key::Down),
			 sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
			 sf::Keyboard::isKeyPressed(sf::Keyboard::S));

    curr_frame_keys_.set(static_cast<std::size_t>(Key::Esc),
			 sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
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
