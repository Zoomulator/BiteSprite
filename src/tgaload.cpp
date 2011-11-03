#include "BiteSprite/tgaload.hpp"


namespace Bite
	{


	#define READ(s, x) s.read( (char*)&x, sizeof(x) )

	void
	TGA::operator() ( std::istream& stream, ImageData& data ) const
		{
		Header header;
		Uint32* pixAllocation = 0;

		stream.seekg( 0 ); // Set cursor to beginning.

		// Read header
		READ( stream, header.idLength );
		READ( stream, header.colorMapType );
		READ( stream, header.imageType );
		READ( stream, header.colorMapSpec.firstEntryIndex );
		READ( stream, header.colorMapSpec.colorMapLength );
		READ( stream, header.colorMapSpec.colorMapEntrySize );
		READ( stream, header.imageSpec.xOrigin );
		READ( stream, header.imageSpec.yOrigin );
		READ( stream, header.imageSpec.width );
		READ( stream, header.imageSpec.height );
		READ( stream, header.imageSpec.pixelDepth );
		READ( stream, header.imageSpec.imageDescriptor );

		// Image ID
		Uint8* imageID = new Uint8[ header.idLength ];
		stream.read( imageID, header.idLength );

		// Color Map data
		Uint32 colorMapSize = header.colorMapType == 0 ? 0 :
			header.colorMapSpec.colorMapLength * header.colorMapSpec.colorMapEntrySize / 8;
		Uint8* colorMapData = new Uint8[ colorMapSize ];
		// TODO: Support for color palettes/maps!
		stream.read( colorMapData, colorMapSize );

		// Image data
		Uint32 pixCount = header.imageSpec.width * header.imageSpec.height;
		Uint8 pixDepth = header.imageSpec.pixelDepth / 8;
		Uint32 pixelMapSize =  pixCount * pixDepth;
		Uint8* pixels = new Uint8[ pixelMapSize ];
		stream.read( pixels, pixelMapSize );

		ColorMask TGAmask;
		TGAmask.r = 0x00FF0000;
		TGAmask.g = 0x0000FF00;
		TGAmask.b = 0x000000FF;
		TGAmask.a = 0xFF000000;

		pixAllocation = new Uint32[ pixCount ];
		for( Uint32 i = 0; i < pixCount; ++i )
			{
			Uint32 rawpix = 0;
			BASSERT( i*pixDepth < pixelMapSize );
			memcpy( &rawpix, &pixels[i*pixDepth], pixDepth );

			Uint32 pix = ConvertColor( rawpix, TGAmask, internalMask );
			pixAllocation[i] = pix;
			}

		data.SetPixels( pixAllocation, header.imageSpec.width, header.imageSpec.height );

		delete[] imageID;
		delete[] colorMapData;
		delete[] pixels;
		}


	} // namespace Bite