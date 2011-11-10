#include "BiteSprite/palette.hpp"
#include "BiteSprite/biteimage.hpp"


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


	Palette
	Palette::FromTrueColor( const Image* img )
		{
		Palette pal;
		const Uint32* pixels = img->Pixels();

		for( size_t i = 0;
			i < pal.colormap.size();
			++i )
			{
			pal.colormap[i] = pixels[i];
			}

		return pal;
		}

	} // namespace Bite