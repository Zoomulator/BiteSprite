#ifndef BITE_IMAGEDATA_HPP
#define BITE_IMAGEDATA_HPP


#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

#include "types.hpp"
#include "colormask.hpp"
#include "bassert.hpp"

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

		Uint32* pixels; // Yay, pixels!

		// Metadata:
		Uint32 width; // in pixels
		Uint32 height;
		};

	const ColorMask internalMask( 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000 );

	}

#endif // BITE_IMAGEDATA_HPP