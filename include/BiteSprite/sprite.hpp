#ifndef BITE_SPRITE_HPP
#define BITE_SPRITE_HPP



#include "BiteSprite/types.hpp"
#include "BiteSprite/idgenerator.hpp"

#include <cmath>


namespace Bite
	{
	class SpriteSheet;
	enum Anchor { Center=1, TopLeft=2 };


	//! Handle interface for data in a SpriteSheet.
	/*! The methods provided by this class gives access 
		to the Sprite's related data in the SpriteSheet. It's suggested
		to not keep multiple copies of a sprite since dropping one
		instance would make the other Sprites dangling handles that
		still refer to the dropped data in the SpriteSheet.
	*/
	class Sprite
		{
		friend SpriteSheet;
		public:

		void Visible( bool );
		//! Whether or not to use the colorkey provided by the SpriteSheet.
		void UseColorKey( bool );
		void Position( float x, float y, Anchor anchor=Center );
		void ZIndex( float z );
		//! Rotates the sprite around it's center in degrees.
		void Rotation( float deg );
		void Scale( float s );
		void PaletteID( ID pal );
		//! Notifies the SpriteSheet that this Sprite is now garbage.
		void Drop();

		private:
		Sprite( ID id, ID templateID, SpriteSheet* sheet );

		ID id;
		SpriteSheet* sheet;
		bool alive;
	
		};


	} // namespace Bite



#endif // BITE_SPRITE_HPP