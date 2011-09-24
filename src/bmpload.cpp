#include "bmpload.hpp"


namespace Bite
	{

	void
	BMP::operator () ( std::istream& stream, ImageData& data ) const
		{
		// Exception safety: This function serves the basic guarantee.
		Uint8* pixAllocation = 0;
		
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

			stream.seekg( BMP::BPP );
			stream.read( (Uint8*)&data.bitpp, 4 );
			data.bytepp = data.bitpp / 8; // 8 bits per byte.

			stream.seekg( BMP::BitmaskR );
			stream.read( (Uint8*)&data.mask, 16 ); // Read all masks in one swoop (4bytes*4).

			Uint32 bmpRowWidth = ( data.bitpp * data.width / 32 ) * 4; // Row bytes wide in stream with possible padding
			data.pixelDataSize = data.width * data.height * data.bytepp;
		
			pixAllocation = new Uint8[ data.pixelDataSize ];

			// Now we know everything but the pixel data itself.
			// Lets create an array that will fit it.
		
			// Read the pixel data from the stream!
			for( Uint32 y = 0; y < data.height; ++y )
				{
				for( Uint32 x = 0; x < data.width; ++x )
					{
					Uint32 fOffset = 
						pixDataOffset + 
						bmpRowWidth * y + 
						data.bytepp * x;
					stream.seekg( fOffset );
					// Read each pixel from the stream and place it at the inverted
					// row place in the data class. X position remains the same.
					Uint32 pOffset = 
						x * data.bytepp + 
						(data.height - y) * (data.width - 1) * data.bytepp;
					B_ASSERT( pOffset <= data.pixelDataSize );
					stream.read( pixAllocation + pOffset, data.bytepp );
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