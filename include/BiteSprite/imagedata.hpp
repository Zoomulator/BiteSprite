#ifndef BITE_IMAGEDATA_HPP
#define BITE_IMAGEDATA_HPP


#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

#include "BiteSprite/types.hpp"
#include "BiteSprite/colormask.hpp"
#include "BiteSprite/bassert.hpp"
#include "BiteSprite/palette.hpp"

namespace Bite
	{

	class ImageData
		{
		public:
		ImageData();
		~ImageData();

		Uint32 PixAt( Uint32 x, Uint32 y );
		void ClearData() throw();
		Uint32 Size() const; // Pixelmap size in bytes

		// Drops ownership of the pixel map without deleting it.
		// Returns a pointer to it's heap location.
		Uint32* DropPixels() throw();
		void SetPixels( Uint32* p, Uint32 w, Uint32 h );
		void SetPalette( Palette* pal );

		Uint32* pixels; // Yay, pixels!
		Palette* palette;

		// Metadata:
		Uint32 width; // in pixels
		Uint32 height;
		};

	const ColorMask internalMask( 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000 );

	}

#endif // BITE_IMAGEDATA_HPP