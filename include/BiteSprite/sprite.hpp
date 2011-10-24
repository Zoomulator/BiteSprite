#ifndef BITE_SPRITE_HPP
#define BITE_SPRITE_HPP



#include "BiteSprite/types.hpp"
#include "BiteSprite/idgenerator.hpp"

#include <cmath>


namespace Bite
	{
	class SpriteSheet;
	enum Anchor { Center=1, TopLeft=2 };

	class Sprite
		{
		friend SpriteSheet;
		public:

		void Visible( bool );
		void UseColorKey( bool );
		void Position( float x, float y, Anchor anchor=Center );
		void ZIndex( float z );

		private:
		Sprite( ID id, ID templateID, SpriteSheet* sheet );

		ID id;
		SpriteSheet* sheet;
	
		};


	} // namespace Bite



#endif // BITE_SPRITE_HPP