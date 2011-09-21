#ifndef BITE_IMAGEDATA_HPP
#define BITE_IMAGEDATA_HPP


#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

#include "bassert.hpp"
#include "bmpinfo.hpp"

namespace Bite
	{


	class ImageData
		{
		public:
		typedef char Uint8;
		typedef unsigned int Uint32;
		typedef int Int32;

		ImageData( std::string path );
		~ImageData();

		void Load( std::string path );
		void LoadBMP( std::string path );

		void PixAt( Uint32 x, Uint32 y, void* ret );

		void ClearData();

		void* pixels;
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
	}

#endif // BITE_IMAGEDATA_HPP