#include "BiteSprite/vertexbuffer.hpp"



namespace Bite
	{


	template<class T>
	VertexBuffer<T>::VertexBuffer( 
		GLuint vertexArrayBuffer, 
		GLuint index,
		GLenum glType,
		GLuint bufW,
		GLuint size ) :

		VAO( vertexArrayBuffer ),
		locIndex( index ),
		bufferID( 0 ),
		type( glType ),
		normalize( false ),
		typeSize( 0 ),
		bufferWidth( bufW ),
		elementSize( size ),
		hasChanged( true ),
		overflowOption( OverflowReallocate )
		{
		CalculateTypeSize();
		SetupGLBuffers();		
		}


	template<class T>
	VertexBuffer<T>::VertexBuffer() :
		VAO( 0 ),
		locIndex( 0 ),
		bufferID( 0 ),
		type( 0 ),
		normalize( false ),
		typeSize( 0 ),
		bufferWidth( 0 ),
		elementSize( 0 ),
		overflowOption( OverflowReallocate )
		{}


	template<class T>
	VertexBuffer<T>::~VertexBuffer()
		{
		DeleteGLBuffers();
		}


	template<class T>
	void
	VertexBuffer<T>::SynchRange( ID first, Uint32 size )
		{
		if( useBufferMapping )
			{
			memcpy( 
				&((char*)bufferMap)[ typeSize * first * elementSize],
				&data[ first * elementSize],
				size * typeSize * elementSize );
			}
		else
			{
			glBufferSubData(
				GL_ARRAY_BUFFER, 
				first * typeSize * elementSize, 
				size * typeSize * elementSize, 
				&data[first * elementSize] );
			CHECK_GL_ERRORS("Synch range");
			}
		}


	template<class T>
	void
	VertexBuffer<T>::Synch()
		{
		if( !hasChanged ) return;
		hasChanged = false;
					
		glBindBuffer( GL_ARRAY_BUFFER, bufferID );

		useBufferMapping = true;
		if( useBufferMapping )
			{
			bufferMap = glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );
			}
			
		SynchRange( 0, Size() );

		if( useBufferMapping )
			{
			glUnmapBuffer( GL_ARRAY_BUFFER );
			}

		glBindBuffer( GL_ARRAY_BUFFER, GL_NONE );
		}


	template<class T>
	void
	VertexBuffer<T>::Grow( Uint32 addSize )
		{
		Uint32 elementCount = data.size();
		
		// Increase size if buffer has room.
		if( (elementCount + addSize) < bufferWidth )
			{
			data.resize( data.size() + addSize * elementSize );
			}
		else // Buffer overflow!
			{
			switch( overflowOption )
				{
				case OverflowException:
					throw BufferOverflow( bufferWidth );
					break;
				case OverflowReallocate:
					DeleteGLBuffers();
					bufferWidth *= 2;
					SetupGLBuffers();
					Grow(addSize);
					break;
				}
			}
		}


	template<class T>
	T&
	VertexBuffer<T>::Element( ID id, Uint8 component=0 )
		{
		hasChanged = true;
		return data[ id*elementSize + component ];
		}


	template<class T>
	const T&
	VertexBuffer<T>::Element( ID id, Uint8 component=0 ) const
		{
		return data[ id*elementSize + component ];
		}



	template<class T>
	void
	VertexBuffer<T>::SetupGLBuffers()
		{
		glBindVertexArray( VAO );
		glGenBuffers( 1, &bufferID );
		glEnableVertexAttribArray( locIndex );
		glBindBuffer( GL_ARRAY_BUFFER, bufferID );
		glBufferData(
			GL_ARRAY_BUFFER,
			typeSize * elementSize * bufferWidth,
			NULL,
			GL_DYNAMIC_COPY );
		
		if( type == GL_FLOAT || type == GL_DOUBLE || type == GL_HALF_FLOAT )
			{
			glVertexAttribPointer( locIndex, elementSize, type, normalize, 0, 0 );
			}
		else
			{
			glVertexAttribIPointer( locIndex, elementSize, type, 0, 0 );
			}
		
		glBindBuffer( GL_ARRAY_BUFFER, GL_NONE );
		glBindVertexArray( GL_NONE );
		}


	template<class T>
	void
	VertexBuffer<T>::DeleteGLBuffers()
		{
		glDeleteBuffers( 1, &bufferID );
		}


	template<class T>
	void
	VertexBuffer<T>::CalculateTypeSize()
		{
		switch( type )
			{
			case GL_HALF_FLOAT:
				typeSize = sizeof( GLfloat ) / 2; break;
			case GL_FLOAT:
				typeSize = sizeof( GLfloat ); break;
			case GL_DOUBLE:
				typeSize = sizeof( GLdouble ); break;
			case GL_BYTE:
				typeSize = sizeof( GLbyte ); break;
			case GL_UNSIGNED_BYTE:
				typeSize = sizeof( GLubyte ); break;
			case GL_SHORT:
				typeSize = sizeof( GLshort ); break;
			case GL_UNSIGNED_SHORT:
				typeSize = sizeof( GLushort ); break;
			case GL_INT:
				typeSize = sizeof( GLint ); break;
			case GL_UNSIGNED_INT:
				typeSize = sizeof( GLuint ); break;
			default:
				throw UnknownGLType();
			}
		}


	template<class T>
	void
	VertexBuffer<T>::OverflowHandling( OverflowOptions option )
		{
		overflowOption = option;
		}


	
	} // namespace Bite