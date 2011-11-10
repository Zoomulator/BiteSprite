#include "BiteSprite/palettebuffer.hpp"


namespace Bite
	{


	PaletteBuffer::PaletteBuffer() :
		glufferID( 0 ),
		elementWidth( 256 ),
		elementCount( 0 )
		{
		elementSize = sizeof( GLuint ) * elementWidth;
		CreateBuffer();
		}


	PaletteBuffer::~PaletteBuffer()
		{
		DestroyBuffer();
		}


	ID
	PaletteBuffer::Add( Palette pal )
		{
		palettes.push_back( pal );
		UpdateBuffer();
		return palettes.size() - 1;
		}


	void
	PaletteBuffer::CreateBuffer()
		{
		glGenBuffers( 1, &glufferID );
		ResizeBuffer();
		}


	void
	PaletteBuffer::DestroyBuffer()
		{
		glDeleteBuffers( 1, &glufferID );
		glufferID = 0;
		}


	void
	PaletteBuffer::UpdateBuffer()
		{
		CHECK_GL_ERRORS( __FUNCTION__ );

		if( elementCount < palettes.size() ) // GL buffer too small!
			{
			elementCount = palettes.size();
			ResizeBuffer();
			}

		for( size_t i = 0; i < palettes.size(); ++i )
			{
			glBindBuffer( GL_TEXTURE_BUFFER, glufferID );
			CHECK_GL_ERRORS( __FUNCTION__ );
			glBufferSubData(
				GL_TEXTURE_BUFFER,
				i * elementSize,
				elementSize,
				&(palettes[i][0]) );
			CHECK_GL_ERRORS( __FUNCTION__ );
			glBindBuffer( GL_TEXTURE_BUFFER, GL_NONE );
			}

		CHECK_GL_ERRORS( __FUNCTION__ );
		}


	void
	PaletteBuffer::ResizeBuffer()
		{
		CHECK_GL_ERRORS( __FUNCTION__ );

		glBindBuffer( GL_TEXTURE_BUFFER, glufferID );
		glBufferData( 
			GL_TEXTURE_BUFFER, 
			elementSize * elementCount, 
			NULL, 
			GL_DYNAMIC_COPY );		
		glBindBuffer( GL_TEXTURE_BUFFER, GL_NONE );

		CHECK_GL_ERRORS( __FUNCTION__ );
		}


	} // namespace Bite