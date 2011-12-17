#ifndef BITE_ANIMATIONSHEET_HPP
#define BITE_ANIMATIONSHEET_HPP


#include "BiteSprite/spritesheet.hpp"
#include "animationtemplate.hpp"
#include "animation.hpp"

namespace Bite
	{

	class AnimationSheet : public SpriteSheet
		{
		friend Animation;

		public:
		typedef std::vector<AnimationTemplate> AnimationTemplates;
		typedef std::vector<AnimationData> Animations;
		

		AnimationSheet( const std::string& imageName );

		void
		CreateAnimationTemplate( 
			const std::string& templateName, 
			AnimationFrames frames );


		Animation
		CreateAnimation( const std::string& templateName );

		private:
		IDGenerator idGenAnimationTemplate;
		AnimationTemplates animationTemplates;
		StringID nameToAnimTemplateID;

		IDGenerator idGenAnimation;
		Animations animations;
		};



	class BadAnimationTemplateName : public Exception
		{
		public:
		BadAnimationTemplateName( const std::string& name )
			{
			errstr =
				"Bad animation template name: " + name;
			}

		protected:
		BadAnimationTemplateName() {}
		};


	} // namespace Bite



#endif // BITE_ANIMATIONSHEET_HPP