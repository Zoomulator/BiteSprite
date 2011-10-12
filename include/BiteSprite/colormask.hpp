#ifndef BITE_COLORMASK_HPP
#define BITE_COLORMASK_HPP



#include "BiteSprite/types.hpp"


namespace Bite
	{
	struct ColorMask
		{
		ColorMask() : r(0), g(0), b(0), a(0) {}
		ColorMask( Uint32 r_, Uint32 g_, Uint32 b_, Uint32 a_ = 0 ) :
			r(r_), g(g_), b(b_), a(a_) {}
		Uint32 r,g,b,a;
		};


	// Extracts the mask's color channel
	inline
	Uint32 MaskColor( Uint32 pixel, Uint32 mask )
		{
		switch( mask )
			{
		case 0xFF000000:
			return (pixel & mask) >> 24;
		case 0x00FF0000:
			return (pixel & mask) >> 16;
		case 0x0000FF00:
			return (pixel & mask) >> 8;
		case 0x000000FF:
			return (pixel & mask);
		default:
			return 0;
			}
		}


	// Inserts the color in the right mask channel
	inline
	Uint32 InsertColor( Uint32 color, Uint32 mask )
		{
		switch( mask )
			{
		case 0xFF000000:
			return (color & 0xFF) << 24;
		case 0x00FF0000:
			return (color & 0xFF) << 16;
		case 0x0000FF00:
			return (color & 0xFF) << 8;
		case 0x000000FF:
			return (color & 0xFF);
		default:
			return 0;
			}
		}


	inline
	Uint32 ConvertColor( Uint32 pixel,
		ColorMask source, ColorMask destination )
		{
		Uint32 destPix = 0;

		// Loop through the color masks.
		for( int c = 0; c < 4; ++c )
			{
			Uint32 src = ((Uint32*)&source)[c];
			Uint32 dst = ((Uint32*)&destination)[c];
			Uint32 val = MaskColor( pixel, src );
			destPix |= InsertColor( val, dst );
			}

		return destPix;
		}

	} // namespace Bite

#endif // BITE_COLORMASK_HPP