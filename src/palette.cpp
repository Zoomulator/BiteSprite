#include "BiteSprite/palette.hpp"



namespace Bite
	{


	Palette::Palette() :
		colormap( 256, 0 )
		{
		
		}


	Uint32&
	Palette::operator[] ( size_t index )
		{
		return colormap.at( index );
		}

	} // namespace Bite