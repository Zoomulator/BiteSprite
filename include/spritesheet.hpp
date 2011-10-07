#ifndef BITE_SPRITESHEET_HPP
#define BITE_SPRITESHEET_HPP


#include <vector>
#include <set>
#include <map>

#include <GL/glew.h>

#include "bassert.hpp"
#include "types.hpp"
#include "imageloader.hpp"
#include "biteimage.hpp"
#include "batch.hpp"
#include "spritetemplate.hpp"
#include "sprite.hpp"
#include "spritesheet_shaders.hpp"
#include "projection.hpp"
#include "view.hpp"
#include "idgenerator.hpp"

namespace Bite
	{


	class SpriteSheet : public Batch
		{
		friend Sprite;

		public:
		SpriteSheet( const std::string imageName, Uint32 bufferSize=1024 );
		~SpriteSheet();

		void
		Render() const;

		void
		Synch(); // Upload changed areas of the buffer to GL

		void
		CreateTemplate( const std::string& name, Rect frame );

		Sprite
		CreateSprite( const std::string& templateName );

		// TODO: OverflowMethod with options: Reallocate, Exception, Silent...

		private:
		typedef std::vector<SpriteTemplate> Templates;
		typedef std::map<std::string, ID> StringID;
		typedef std::vector<Sprite> Sprites; // Unused?
		typedef std::vector<GLuint> BufferUint;
		typedef std::vector<GLfloat> BufferFloat;
	
		void
		GLLoadShaders();

		void
		GLUnloadShaders();

		void
		GLBufferSetup();

		void
		GLDestroyBuffers();

		Image sheet;

		// GL data
		GLuint VAO; // Vertex array object.
		Uint32 bufferSize; // Amount of units allocated for.

		// GL buffer (gluffer) names
		GLuint glufferVertex; // x,y,z
		GLuint glufferTemplateID;
		GLuint glufferFrameTBO; // Stores all the template's frames in ID order
		
		// GL textures
		GLuint texFrameTBO; // Texture for glufferFrameTBO to bind to
		
		// Matrices
		GLfloat projection[16];
		GLfloat view[16];

		// SpriteTemplate IDs are the same as the index in this vector.
		Templates templates;
		IDGenerator idGenTemplate;
		StringID nameToTemplateID;

		IDGenerator idGenSprite;
		IDSet changeSet; // ID of sprites that needs to synch.
		Uint32 spriteCount; // Number of sprites fed to the buffer.
		
		BufferUint spriteFlag;
		BufferFloat spritePosition;
		BufferUint	spriteTemplateID;
		};


	} // namespace Bite


#endif // BITE_SPRITESHEET_HPP