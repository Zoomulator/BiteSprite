#include "imagedata.hpp"





namespace Bite
	{

	ImageData::ImageData( std::string path ) :
		pixels( 0 ),
			width( 0 ),
			height( 0 ),
			bitpp( 0 ),
			bytepp( 0 ),
			pixelDataSize( 0 )
		{
		Load( path );
		}


	ImageData::~ImageData()
		{
		ClearData();
		}


	void
	ImageData::Load( std::string path )
		{
		// TODO: extract filetype and load accordingly
		LoadBMP( path );
		}


	void
	ImageData::LoadBMP( std::string path )
		{
		void ClearData();

		std::fstream 
			file( path.c_str(), std::ios_base::binary | std::ios_base::in );
		
		if( !file.good() )
			{
			std::cout << "Could not open file: " << path.c_str() << std::endl;
			return;
			}
		// Lets read all the meta data about the bmp image.

		// Set stream get-pointer to pixel data offset and read it.
		Uint32 pixDataOffset = 0;
		file.seekg( BMP::PixDataOffset );
		file.read( (Uint8*)&pixDataOffset, 4 ); // Read 4 bytes

		file.seekg( BMP::PixWidth );
		file.read( (Uint8*)&width, 4 );

		file.seekg( BMP::PixHeight );
		file.read( (Uint8*)&height, 4 );

		file.seekg( BMP::BPP );
		file.read( (Uint8*)&bitpp, 4 );
		bytepp = bitpp / 8;

		file.seekg( BMP::BitmaskR );
		file.read( (Uint8*)&mask, 16 ); // Read all masks in one swoop.

		Uint32 bmpRowWidth = ( bitpp * width / 32 ) * 4; // Row bytes wide in file with padding
		pixelDataSize = width*height*bytepp; // 8bits per byte
		
		// Now we know everything but the pixel data itself.
		// Lets create an array that will fit it.
		pixels = (void*)new Uint8[ pixelDataSize ]; // Allocate bytes
		
		// Read the pixel data!
		//for( Uint32 y = height-1; y == 0; --y ) // Run bottoms up.
		for( Uint32 y = 0; y < height; ++y )
			{
			for( Uint32 x = 0; x < width; ++x )
				{
				Uint32 fOffset = pixDataOffset + bmpRowWidth * y + x*bytepp; // 8bits/byte
				file.seekg( fOffset );
				// Read the pixel from the file and place it at the same place in the pixel array.
				Uint32 pOffset = x*bytepp + (height-y)*(width-1)*bytepp;
				B_ASSERT( pOffset <= pixelDataSize );
				file.read( ((Uint8*) pixels) + pOffset, bytepp );
				}
			}
		}


	void
	ImageData::PixAt( Uint32 x, Uint32 y, void* ret )
		{
		memcpy( 
			(Uint8*)ret,
			((Uint8*)pixels) + x*bytepp + y*width*bytepp,
			bytepp );
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