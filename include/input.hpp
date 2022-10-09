#ifndef __PROJECTS_TGG_INPUT_HPP__
#define __PROJECTS_TGG_INPUT_HPP__

#include <SFML/Graphics.hpp>

#include <bitset>

class Input
{
private:
    std::bitset<32> prev_frame_keys_;
    std::bitset<32> curr_frame_keys_;

public:
    enum class Key
    {
	kNone,
	kLeft,
	kRight,
	kUp,
	kDown,
	kEsc,
	kLBracket,
	kRBracket,
    };

public:
    void Update       ();
    bool IsKeyPressed (Key keycode);
    bool IsKeyDown    (Key keycode);
    bool IsKeyUp      (Key keycode);
};

#endif
