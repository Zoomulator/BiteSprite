#include "BiteSprite/animation.hpp"

#include "BiteSprite/animationsheet.hpp"

namespace Bite
	{

	AnimationData::AnimationData() :
		isPlaying(false),
		frameTime(0),
		frameSpeed(1.0f),
		frameIndex(0),
		animationTemplateID(0)
		{
		}



	Animation::Animation( ID id, ID sid, const std::string& animName, AnimationSheet* animSheet) :
		Sprite( sid, "", animSheet ),
		sheet(animSheet),
		animationID(id)
		{
		UseTemplate( animName );
		}


	void
	Animation::Drop()
		{
		sheet->idGenAnimation.RecycleID( animationID );
		Sprite::Drop();
		}


	void
	Animation::Progress( float seconds )
		{
		AnimationData& data = sheet->animations[animationID];

		data.frameTime += seconds * data.frameSpeed;
		// Look up the animation template
		AnimationTemplate& aniTemplate =
			sheet->animationTemplates[ data.animationTemplateID ];

		// If past duration change to next sprite frame.
		float frameDuration = aniTemplate.frames[data.frameIndex].duration;
		if( data.frameTime >= frameDuration )
			{
			data.frameTime -= frameDuration; // Leave any leftover frame time.

			data.frameIndex = (++data.frameIndex) % aniTemplate.frames.size();

			Frame( aniTemplate.frames[data.frameIndex].name );
			}
		}


	void
	Animation::Play()
		{
		AnimationData& data = sheet->animations[animationID];
		data.isPlaying = true;
		}


	void
	Animation::Pause()
		{
		AnimationData& data = sheet->animations[animationID];
		data.isPlaying = false;
		}


	void
	Animation::Stop()
		{
		AnimationData& data = sheet->animations[animationID];
		data.isPlaying = false;
		data.frameIndex = 0;
		data.frameTime = 0;
		}


	void
	Animation::Speed( float multiplier )
		{
		AnimationData& data = sheet->animations[animationID];
		data.frameSpeed = multiplier;
		}


	void
	Animation::UseTemplate( const std::string& name )
		{
		AnimationData& data = sheet->animations[animationID];

		StringID::iterator it = sheet->nameToAnimTemplateID.find( name );

		if( it == sheet->nameToAnimTemplateID.end() ) throw BadAnimationTemplateName(name);

		data.animationTemplateID = it->second;
		AnimationTemplate& aniTemplate =
			sheet->animationTemplates[ data.animationTemplateID ];
		Frame( aniTemplate.frames[data.frameIndex].name );
		}

	} // namespace Bite