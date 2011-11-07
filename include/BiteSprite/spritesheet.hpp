#ifndef BITE_SPRITESHEET_HPP
#define BITE_SPRITESHEET_HPP


#include <vector>
#include <set>
#include <map>
#include <sstream>

#include <GL/glew.h>

#include "BiteSprite\bexception.hpp"
#include "BiteSprite\bassert.hpp"
#include "BiteSprite\types.hpp"
#include "BiteSprite\imageloader.hpp"
#include "BiteSprite\biteimage.hpp"
#include "BiteSprite\batch.hpp"
#include "BiteSprite\spritetemplate.hpp"
#include "BiteSprite\sprite.hpp"
#include "BiteSprite\spritesheet_shaders.hpp"
#include "BiteSprite\projection.hpp"
#include "BiteSprite\framebuffer.hpp"
#include "BiteSprite\view.hpp"
#include "BiteSprite\idgenerator.hpp"
#include "BiteSprite\checkglerror.hpp"

namespace Bite
	{


	class SpriteSheet : public Batch
		{
		friend Sprite;

		public:
		SpriteSheet( const std::string imageName, Uint32 bufferSize=1024 );
		~SpriteSheet();

		//! Draws all sprites currently in GL buffers.
		/*! Synch will have to be called separately.
		 *	Draws to BiteSprite's own framebuffer. Use
		 *	Bite::Framebuffer::Flip() to display in window.
		 */
		void
		Render() const;

		void
		SynchRange( ID first, Uint32 size );

		//! Upload any changed Sprites in the buffer to GL
		void
		Synch();

		//! Upload full buffer to GL
		void
		SynchAll();
		
		//! Puts the Sprite in the update queue to be uploaded in the next synch call.
		void
		UpdateSprite( ID id );
		
		void
		CreateTemplate( const std::string& name, Rect frame );

		void
		DropTemplate( const std::string& name );

		Sprite
		CreateSprite( const std::string& templateName );
		
		//! Set a color to be used as transparent with normalized float range (0.0->1.0).
		/*! Sprites should have UseColorKey enabled. The range argument
		 *	gives a sensitivity threshold, in case the color is "dirty".
		 */
		void
		ColorKeyNorm( float r, float g, float b, float range=0.1f );

		//! Set a color to be used as transparent with 8bit ranges.
		/*! Sprites should have UseColorKey enabled. The range argument
		 *	gives a sensitivity threshold, in case the color is "dirty".
		 */
		void
		ColorKey( Uint8 r, Uint8 g, Uint8 b, Uint8 range=25 );

		enum OverflowOptions {
			OverflowReallocate, OverflowException };

		//! Let's you chose how overflows are handled.
		/*! It should be preferred to set an appropriate buffer size
		 *  when the SpriteSheet is initialized and have overflow handling
		 *  set to throw exceptions. Reallocation is quite a heavy procedure.
		 *	On reallocation, the buffer is doubled in size.
		 *  The Bite::BufferOverflow exception is used when throwing.
		 */
		void OverflowHandling( OverflowOptions );

		private:
		typedef std::vector<SpriteTemplate> Templates;
		typedef std::map<std::string, ID> StringID;
		typedef std::vector<GLuint> BufferUint;
		typedef std::vector<GLfloat> BufferFloat;

		void
		GLBufferSetup();

		void
		GrowBuffers();

		void
		GLDestroyBuffers();

		void
		IncrementBuffers();

		Image sheet;

		// GL data
		GLuint VAO; // Vertex array object.
		Uint32 bufferSize; // Amount of units allocated for.

		// GL buffer (gluffer) names
		GLuint glufferVertex; // x,y,z
		GLuint glufferTemplateID;
		GLuint glufferFlag;
		GLuint glufferRotScale; // rotation and scale floats
		GLuint glufferFrameTBO; // Stores all the template's frames in ID order
		
		// GL textures
		GLuint texFrameTBO; // Texture for glufferFrameTBO to bind to
		
		//GL uniforms
		GLfloat colorKey[4];
		// SpriteTemplate IDs are the same as the index in this vector.
		Templates templates;
		IDGenerator idGenTemplate;
		BufferUint frames;
		StringID nameToTemplateID;

		IDGenerator idGenSprite;
		IDSet changeSet; // ID of sprites that needs to synch.
		Uint32 spriteCount; // Number of sprites fed to the buffer.
		
		BufferUint spriteFlag;
		BufferFloat spritePosition;
		BufferUint	spriteTemplateID;
		BufferFloat spriteRotScale;

		OverflowOptions overflowOption;
		};


	class BadTemplateName : public Exception
		{
		public:
		BadTemplateName( const std::string& name )
			{
			errstr =
				"Bad template name: " + name;
			}

		protected:
		BadTemplateName() {}
		};


	class TemplateNameAlreadyInUse : public BadTemplateName
		{
		public:
		TemplateNameAlreadyInUse( const std::string& name )
			{
			errstr =
				"Template name already in use: " + name;
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


#endif // BITE_SPRITESHEET_HPP