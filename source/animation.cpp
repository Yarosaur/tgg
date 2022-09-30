#include "../include/animation.hpp"


Animation::Animation(FacingDirection dir)
    : frames_              {}
    , current_frame_index_ {0}
    , current_frame_time_  {0.f}
    , facing_direction_    {dir}
{}


void Animation::IncrementFrame()
{
    current_frame_index_ = (current_frame_index_ + 1) % frames_.size();
}


void Animation::AddFrame(const FrameData& frame)
{
    FrameData fresh_frame {frame};
    frames_.push_back(fresh_frame);
}


const FrameData* Animation::GetCurrentFrame() const
{
    if (frames_.size() > 0)
    {
	return &frames_[current_frame_index_];
    }

    return nullptr;
}


bool Animation::UpdateFrame(float delta_time)
{
    if (frames_.size())
    {
	current_frame_time_ += delta_time;
	if (current_frame_time_ >= frames_[current_frame_index_].display_time_seconds)
	{
	    current_frame_time_ = 0.f;
	    IncrementFrame();

	    return true;
	}
    }

    return false;
}


void Animation::Reset()
{
    current_frame_index_ = 0;
    current_frame_time_  = 0.f;
}



void Animation::SetFacingDirection(FacingDirection dir)
{
    if (facing_direction_ != dir)
    {
	facing_direction_ = dir;

	// Invert frames
	for (auto& frame: frames_)
	{
	    frame.x     += frame.width;
	    frame.width *= -1;
	}
    }
}


FacingDirection Animation::GetFacingDirection() const
{
    return facing_direction_;
}
