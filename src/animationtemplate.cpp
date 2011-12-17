#include "BiteSprite\animationtemplate.hpp"



namespace Bite
	{

	
	AnimationTemplate::AnimationTemplate() :
		totalDuration(0)
		{
		}


	void
	AnimationTemplate::AddFrame( const AnimationFrame& frame )
		{
		frames.push_back( frame );
		totalDuration += frame.duration;
		}


	} // namespace Bite