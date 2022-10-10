#include "../include/animation.hpp"


Animation::Animation()
    : frames_              {}
    , current_frame_index_ {0}
    , current_frame_time_  {0.f}
{}


void Animation::IncrementFrame()
{
    current_frame_index_ = (current_frame_index_ + 1) % frames_.size();
}


void Animation::RunActionForCurrentFrame()
{
    if (actions_.size() > 0)
    {
	if ( frames_with_action_[current_frame_index_] )
	{
	    auto actions_to_run { actions_.at(current_frame_index_) };

	    for (auto fun : actions_to_run)
	    {
		fun();
	    }
	
	}
    }
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
	    RunActionForCurrentFrame();

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


void Animation::AddFrameAction(unsigned int frame, AnimationAction action)
{
    // If the frame is larger than the number of animation frames 
    // then this request is ignored.
    if (frame < frames_.size())
    {
	auto action_key { actions_.find(frame) };
	if (action_key == actions_.end())
	{
            // If there is not an existing entry for this frame 
            // we create one.
	    frames_with_action_.set(frame);
	    actions_.insert(std::make_pair(frame, 
					   std::vector<AnimationAction>{action}) );
	}
	else
	{
            // An existing entry was found so we 
            // add the action to the vector
	    action_key->second.emplace_back(action);
	}
    }
}
