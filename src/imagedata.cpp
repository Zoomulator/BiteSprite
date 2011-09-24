#include "imagedata.hpp"





namespace Bite
	{

	ImageData::ImageData() :
		pixels( 0 ),
			width( 0 ),
			height( 0 ),
			bitpp( 0 ),
			bytepp( 0 ),
			pixelDataSize( 0 )
		{}


	ImageData::~ImageData()
		{
		ClearData();
		}


	void*
	ImageData::DropPixels()
		{
		void* ret = pixels;
		pixels = 0;
		return ret;
		}


	void
	ImageData::ClearData()
		{
		delete[] pixels;
		pixels = 0;
		width = 0;
		height = 0;
		bitpp = 0;
		bytepp = 0;
		pixelDataSize = 0;
		mask.r = 0;
		mask.g = 0;
		mask.b = 0;
		mask.a = 0;
		}

	} // namespace Bite