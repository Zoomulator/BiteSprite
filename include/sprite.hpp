#ifndef BITE_SPRITE_HPP
#define BITE_SPRITE_HPP



#include "types.hpp"
#include "idgenerator.hpp"



namespace Bite
	{
	class SpriteSheet;

	class Sprite
		{
		friend SpriteSheet;
		public:

		void Visible( bool );
		void Position( float x, float y );
		void ZIndex( float z );

		private:
		Sprite( ID id, ID templateID, SpriteSheet* sheet );

		ID id;
		SpriteSheet* sheet;
	
		};


	} // namespace Bite



#endif // BITE_SPRITE_HPP