#ifndef __PROJECTS_TGG_ANIMATION_HPP__
#define __PROJECTS_TGG_ANIMATION_HPP__


#include "type_identifier.hpp"

#include <vector>
#include <map>
#include <functional>
#include <bitset>


struct FrameData
{
    int   texture_id;           // Texture id (retrieved from our texture holder).
    int   x;                    // x position of sprite in the texture.
    int   y;                    // y position of sprite in the texture.
    int   width;                // Width of sprite.
    int   height;               // Height of sprite.
    float display_time_seconds; // How long to display the frame.
};



class Animation
{
private:
    std::vector<FrameData>                      frames_; 
    int                                         current_frame_index_; 
    float                                       current_frame_time_;
    std::map<int, std::vector<AnimationAction>> actions_;
    std::bitset<64>                             frames_with_action_;

private:
    void              IncrementFrame           ();
    void              RunActionForCurrentFrame ();

public:
                      Animation                ();
    void              AddFrame                 (const FrameData& frame);
    const FrameData*  GetCurrentFrame          () const;
    bool              UpdateFrame              (float delta_time);
    void              Reset                    ();
    void              AddFrameAction           (uint frame, AnimationAction action);

   
};


#endif
