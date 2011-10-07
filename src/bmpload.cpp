#include "bmpload.hpp"


namespace Bite
	{


	void
	BMP::operator () ( std::istream& stream, ImageData& data ) const
		{
		// Exception safety: This function serves the basic guarantee.
		Uint32* pixAllocation = 0;
		
		try
			{
			data.ClearData();

			// Now lets read all the meta data about the bmp image.

			// Set stream get-pointer to pixel data offset and read each header.
			// Sizes depends on the BMP specs and are the given magical numbers below.
			Uint32 pixDataOffset = 0;
			stream.seekg( BMP::PixDataOffset );
			stream.read( (Uint8*)&pixDataOffset, 4 ); // Read 4 bytes

			stream.seekg( BMP::PixWidth );
			stream.read( (Uint8*)&data.width, 4 );

			stream.seekg( BMP::PixHeight );
			stream.read( (Uint8*)&data.height, 4 );

			Uint32 bitpp;
			Uint32 bytepp;
			stream.seekg( BMP::BPP );
			stream.read( (Uint8*)&bitpp, 4 );
			bytepp = bitpp / 8; // 8 bits per byte.

			ColorMask BMPmask;
			BMPmask.r = 0x00FF0000;
			BMPmask.g = 0x0000FF00;
			BMPmask.b = 0x000000FF;
			BMPmask.a = 0xFF000000;

			Uint32 bmpRowWidth = ( bitpp * data.width / 32 ) * 4; // Row bytes wide in stream with possible padding
					
			pixAllocation = new Uint32[ data.width * data.height ]; // 4 bytes per Uint32

			// Now we know everything but the pixel data itself.
			// Lets create an array that will fit it.
		
			// Read the pixel data from the stream!
			for( Uint32 y = 0; y < data.height; ++y )
				{
				for( Uint32 x = 0; x < data.width; ++x )
					{
					// Read the pixel from the stream.
					Uint32 fOffset = 
						pixDataOffset + 
						bmpRowWidth * y + 
						bytepp * x;
					stream.seekg( fOffset );
				
					Uint32 rawPixel = 0;
					stream.read( (char*)&rawPixel, bytepp );

					// Convert it to BiteSprite's internal pixel format.
					Uint32 pixel = ConvertColor( rawPixel, BMPmask, internalMask );
					
					//Uint32 pOffset = x + (data.height - y - 1) * (data.width - 1);
					Uint32 pOffset = x + (data.width-y-1) * data.width;
					BASSERT( pOffset*4 <= data.Size() );

					pixAllocation[pOffset] = pixel;
					}
				}

			// Finally, point to the memory allocated earlier.
			data.pixels = pixAllocation; 
			}
		catch(...)
			{
			delete[] pixAllocation;
			throw;
			}
	}


	} // namespace Bite