#ifndef BITE_IMAGEDATA_HPP
#define BITE_IMAGEDATA_HPP


#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

#include "types.hpp"
#include "bassert.hpp"

namespace Bite
	{

	class ImageData
		{
		public:
		ImageData();
		~ImageData();

		template<class T>
		void PixAt( Uint32 x, Uint32 y, T& ret );
		void ClearData() throw();

		// Drops ownership of the pixel map without deleting it.
		// Returns a pointer to it's heap location.
		void* DropPixels() throw();

		void* pixels; // Yay, pixels!

		// Metadata:
		Uint32 width;
		Uint32 height;
		Uint32 bitpp; // bit per pixel
		Uint32 bytepp;
		Uint32 pixelDataSize; // In bytes

		struct Mask
			{
			Mask() : r(0), g(0), b(0), a(0) {}
			Uint32 r;
			Uint32 g;
			Uint32 b;
			Uint32 a;
			} mask;

		};
	


	// This template allows the return value to be any size the user needs.
	// Should work just as well with 32bit as 64bit colors.
	// However, it does not guarantee that the 64bit value is valid if used
	// on a 32bit image. It's up to the user to use the appropriate return type.
	template<class T> void
	ImageData::PixAt( Uint32 x, Uint32 y, T& ret )
		{
		memcpy( 
			(Uint8*)&ret,
			((Uint8*)pixels) + x * bytepp + y * width * bytepp, // Fetch the right pixel
			sizeof(T) ); // Makes sure it doesn't outbound
		}

	}

#endif // BITE_IMAGEDATA_HPP