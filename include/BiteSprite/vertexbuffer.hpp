#ifndef BITE_VERTEXBUFFER_HPP
#define BITE_VERTEXBUFFER_HPP

#include <vector>
#include <sstream>

#include "GL/glew.h"

#include "BiteSprite/idgenerator.hpp"
#include "BiteSprite/bexception.hpp"

namespace Bite
	{
	
	template<class T>
	class VertexBuffer
		{
		public:
		enum OverflowOptions {
			OverflowReallocate, OverflowException };

		VertexBuffer( 
			GLuint VAO,
			GLuint locIndex,
			GLenum glType,
			GLuint bufferWidth, //!< Number of elements
			GLuint size=1 //!< Number of components per element
			);

		VertexBuffer();

		~VertexBuffer();

		void SynchRange( ID first, Uint32 size );
		void Synch();
		//! Grow buffer with given amount of elements.
		void Grow( Uint32 addSize );

		//! Access element with ID. Component starts at index 0
		T& Element( ID id, Uint8 component=0 );
		const T& Element( ID it, Uint8 component=0 ) const;

		Uint32 Size() const { return data.size()/elementSize; }
		Uint32 Capacity() const { return bufferWidth; }

		//! Let's you chose how overflows are handled.
		/*! It should be preferred to set an appropriate buffer size
		 *  when the SpriteSheet is initialized and have overflow handling
		 *  set to throw exceptions. Reallocation is quite a heavy procedure.
		 *	On reallocation, the buffer is doubled in size.
		 *  The Bite::BufferOverflow exception is used when throwing.
		 */
		void OverflowHandling( OverflowOptions );

		private:
		void SetupGLBuffers();
		void DeleteGLBuffers();
		void CalculateTypeSize();

		GLuint VAO;
		GLuint locIndex;
		GLuint bufferID;
		GLuint type;
		GLboolean normalize;
		GLuint typeSize;
		GLuint bufferWidth; //!< Room for #elements in buffer.
		GLuint elementSize; //!< Number of components per element
		
		typedef std::vector<T> Data;
		Data data;
		IDSet changeSet; // IDs that needs to synch.

		OverflowOptions overflowOption;
		};


	class UnknownGLType : Bite::Exception
		{
		public:
		UnknownGLType()
			{
			errstr = "Unknown GL type";
			}
		};


	class BufferOverflow : public Exception
		{
		public:
		BufferOverflow( int bufferSize )
			{
			std::stringstream sizestr;
			sizestr << bufferSize;
			errstr = "Buffer overflow. Size was: ";
			errstr += sizestr.str();
			}
		};

	} // namespace Bite



	#include "BiteSprite/vertexbuffer_impl.hpp"



#endif // BITE_VERTEXBUFFER_HPP