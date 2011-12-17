#include "BiteSprite/animationsheet.hpp"


namespace Bite
	{


	AnimationSheet::AnimationSheet( const std::string& imageName ) :
		SpriteSheet( imageName )
		{}



	void
	AnimationSheet::CreateAnimationTemplate(
		const std::string& name,
		AnimationFrames frames )
		{
		AnimationTemplate aniTemplate;

		for( AnimationFrames::iterator it = frames.begin();
			it != frames.end();
			++it )
			{
			aniTemplate.AddFrame( *it );
			}

		ID id = idGenAnimationTemplate.NewID();

		if( animationTemplates.size() == id )
			{
			animationTemplates.push_back( aniTemplate );
			}
		else
			{
			animationTemplates[id] = aniTemplate;
			}

		nameToAnimTemplateID[ name ] = id;
		}


	Animation
	AnimationSheet::CreateAnimation( const std::string& templateName )
		{
		ID animID = idGenAnimation.NewID();

		if( animations.size() == animID )
			{
			animations.push_back( AnimationData() );
			}
		else
			{
			animations[animID] = AnimationData();
			}

		Sprite sprite = CreateSprite( "" );
		
		return Animation( animID, sprite.GetID(), templateName, this );
		}

	} // namespace Bite