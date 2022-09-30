#ifndef __PROJECTS_TGG_ANIMATION_HPP__
#define __PROJECTS_TGG_ANIMATION_HPP__

#include <vector>

struct FrameData
{
    int   texture_id;           // Texture id (retrieved from our texture holder).
    int   x;                    // x position of sprite in the texture.
    int   y;                    // y position of sprite in the texture.
    int   width;                // Width of sprite.
    int   height;               // Height of sprite.
    float display_time_seconds; // How long to display the frame.
};


enum class FacingDirection
{
    kNone,
    kLeft,
    kRight,
};

class Animation
{
private:
    std::vector<FrameData> frames_; 
    int                    current_frame_index_; 
    float                  current_frame_time_;
    FacingDirection        facing_direction_;

private:
    void              IncrementFrame  ();

public:
                      Animation          (FacingDirection dir);
    void              AddFrame           (const FrameData& frame);
    const FrameData*  GetCurrentFrame    ()                       const;
    bool              UpdateFrame        (float delta_time);
    void              Reset              ();
    void              SetFacingDirection (FacingDirection dir);
    FacingDirection   GetFacingDirection ()                       const;
   
};


#endif
