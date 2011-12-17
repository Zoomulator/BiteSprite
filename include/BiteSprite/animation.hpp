#ifndef BITE_ANIMATION_HPP
#define BITE_ANIMATION_HPP


#include "BiteSprite/sprite.hpp"

namespace Bite
	{

	class AnimationSheet;

	class AnimationData
		{
		public:
		AnimationData();

		bool isPlaying;
		float frameTime;
		float frameSpeed;
		Uint32 frameIndex;
		Uint32 animationTemplateID;
		};



	class Animation : public Sprite
		{
		friend AnimationSheet;

		public:
			
			virtual void Drop();
			void Progress( float seconds );
			void Play();
			void Pause();
			void Stop();
			void Speed( float multiplier = 1.0f );
			void UseTemplate( const std::string& name );

		private:
			Animation(ID id, ID spriteID, 
				const std::string& animName, AnimationSheet*);

			ID animationID;
			AnimationSheet* sheet;
		};





	} // namespace Bite
#endif // BITE_ANIMATION_HPP