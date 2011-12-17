#ifndef BITE_ANIMATIONTEMPLATE_HPP
#define BITe_ANIMATIONTEMPLATE_HPP


#include <string>
#include <vector>

namespace Bite
	{

	class AnimationSheet;
	class Animation;

	struct AnimationFrame
		{
		AnimationFrame( const std::string& name_, float duration_ ) : 
			name(name_), duration(duration_) {}

		std::string name;
		float duration;
		};

	
	typedef std::vector<AnimationFrame> AnimationFrames;
	

	class AnimationTemplate
		{
		friend AnimationSheet;
		friend Animation;
		public:
			void AddFrame( const AnimationFrame& frame );

		private:
			AnimationTemplate();
			AnimationFrames frames;
			
			float totalDuration;
		};

	} // namespace Bite


#endif // BITE_ANIMATIONTEMPLATE_HPP