#include "imagedata.hpp"





namespace Bite
	{

	ImageData::ImageData() :
		pixels( 0 ),
			width( 0 ),
			height( 0 )
		{}


	ImageData::~ImageData()
		{
		ClearData();
		}


	Uint32*
	ImageData::DropPixels()
		{
		Uint32* ret = pixels;
		pixels = 0;
		return ret;
		}


	Uint32
	ImageData::PixAt( Uint32 x, Uint32 y )
		{
		return pixels[ x + y*width ];
		}


	void
	ImageData::ClearData()
		{
		delete[] pixels;
		pixels = 0;
		width = 0;
		height = 0;
		}


	Uint32
	ImageData::Size() const
		{
		return width * height * 4; // 4bytes per pix
		}

	} // namespace Bite