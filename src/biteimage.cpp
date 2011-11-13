#include "BiteSprite/biteimage.hpp"



namespace Bite
	{

	Image::Image( const std::string& n ) :
		textureID(0),
		name(n),
		width(0),
		height(0),
		pixels(0),
		format(none)
		{
		glGenTextures( 1, &textureID );
		}


	Image::~Image()
		{
		delete[] pixels;
		glDeleteTextures( 1, &textureID );
		}



	const Uint32*
	Image::Pixels() const
		{
		return pixels;
		}


	void
	Image::CopyPixels( Uint32* newPix, Uint32 newWidth, Uint32 newHeight, Palette* pal )
		{
		// Note: Not exception safe.
		width = newWidth;
		height = newHeight;
		Uint32 size = width * height;

		delete[] pixels;
		pixels = new Uint32[ size ];

		memcpy( pixels, newPix, size );	
		
		if( pal != NULL )
			{
			format = pal8bit;	
			palette = *pal;
			}
		else
			format = true32bit;
		}


	void
	Image::AdoptPixels( Uint32* newPix, Uint32 newWidth, Uint32 newHeight, Palette* pal )
		{
		delete[] pixels;

		width = newWidth;
		height = newHeight;
		pixels = newPix;

		if( pal != NULL )
			{
			format = pal8bit;	
			palette = *pal;
			}
		else
			format = true32bit;
		}


	void
	Image::UpdateTexture()
		{
		glBindTexture( GL_TEXTURE_2D, textureID );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		if( format == pal8bit )
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RED, width, height, 0,
				GL_RGBA, GL_UNSIGNED_BYTE, pixels );
		else
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
				GL_RGBA, GL_UNSIGNED_BYTE, pixels );
		}


	} // namespace Bite