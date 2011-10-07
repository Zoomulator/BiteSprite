#include "spritesheet.hpp"


namespace Bite
	{
	

	SpriteSheet::SpriteSheet( const std::string imageName, Uint32 bufferSize_ ) :
		VAO(0),
		bufferSize( bufferSize_ ),
		glufferVertex(0),
		glufferTemplateID(0),
		glufferFrameTBO(0),
		texFrameTBO(0)
		{
		GLLoadShaders();
		GLBufferSetup();

		image = Load::Image( imageName );
		}


	SpriteSheet::~SpriteSheet()
		{
		GLDestroyBuffers();
		GLUnloadShaders();
		}


	void
	SpriteSheet::Render() const
		{
		// Bindings:
		glUseProgram( Shader::glsProgSprite );
		glBindVertexArray( VAO );

		// Uniforms:
		glActiveTexture( GL_TEXTURE0 ); // For sprite sheet
		glBindTexture( GL_TEXTURE_2D, sheet.textureID );
		glUniform1i( Shader::unilocSpriteSheet, 0 );

		glActiveTexture( GL_TEXTURE1 ); // For template frame TBO
		glBindTexture( GL_TEXTURE_BUFFER, texFrameTBO );
		glTexBuffer( GL_TEXTURE_BUFFER, GL_RGBA32F, glufferFrameTBO );
		glUniform1i( Shader::unilocSpriteFrame, 1 );

		glUniformMatrix4fv( Shader::unilocProjection, 1, GL_TRUE, Projection::matrix );
		glUniformMatrix4fv( Shader::unilocView, 1, GL_TRUE, View::matrix );

		glDrawArrays( GL_POINTS, 0, spriteCount );

		// Unbind:
		glActiveTexture( GL_TEXTURE2 );
		glBindTexture( GL_TEXTURE_2D, GL_NONE );

		glActiveTexture( GL_TEXTURE0 );
		glBindTexture( GL_TEXTURE_2D, GL_NONE );

		glBindVertexArray( GL_NONE );
		glUseProgram( GL_NONE );
		}


	void
	SpriteSheet::CreateTemplate( const std::string& name, Rect frame )
		{
		StringID::const_iterator it = nameToTemplateID.find( name );

		if( it != nameToTemplateID.end() ) // If name's not taken
			{
			ID id = idGenTemplate.NewID();

			SpriteTemplate& spriteTemplate = templates[id];
			spriteTemplate.id = id;
			spriteTemplate.name = name;
			spriteTemplate.frame = frame;

			// if( nameToTemplateID.size() > id ) // replace
			nameToTemplateID[name] = id; // Note: Not sure if this creates a new object if out of bounds.
			// else push to template
			}
		else // name is taken
			{
			// TODO: Throw exception
			}
		}


	Sprite
	SpriteSheet::CreateSprite( const std::string& templateName )
		{
		Uint32 tid = nameToTemplateID[ templateName ];
		ID sid = idGenSprite.NewID();
		Sprite( sid, tid, this );
		}

	
	void
	SpriteSheet::GLBufferSetup()
		{
		BASSERT( VAO == 0 );
		BASSERT( glufferVertex == 0 );
		BASSERT( glufferTemplateID == 0 );
		
		glGenVertexArrays( 1, &VAO );
				
		glGenBuffers( 1, &glufferVertex );
		glGenBuffers( 1, &glufferTemplateID );
		glGenBuffers( 1, &glufferFrameTBO );
		glGenTextures( 1, &texFrameTBO );
		
		glBindVertexArray( VAO );

		// Create buffer objects for the different vertex attributes.
		// 1. Bind the buffer object that will hold attribute data.
		// 2. Allocate the buffer memory, but no data uploaded (NULL passed).
		// 3. Create a pointer for the VAO so that you can access it in shader.
		// Repeat per buffer...
		glBindBuffer( GL_ARRAY_BUFFER, glufferVertex );
		glBufferData( GL_ARRAY_BUFFER, sizeof(GLfloat)*3*bufferSize, NULL, GL_DYNAMIC_COPY );
		glVertexAttribPointer( Shader::attriblocVertex, 3, GL_FLOAT, GL_FALSE, 0, 0 );

		glBindBuffer( GL_ARRAY_BUFFER, glufferTemplateID );
		glBufferData( GL_ARRAY_BUFFER, sizeof(GLuint)*bufferSize, NULL, GL_DYNAMIC_COPY );
		glVertexAttribPointer( Shader::attriblocTemplateID, 1, GL_UNSIGNED_INT, GL_FALSE, 0,0);

		glBindBuffer( GL_TEXTURE_BUFFER, glufferFrameTBO );
		glBufferData( GL_TEXTURE_BUFFER, sizeof(GLfloat)*4*bufferSize, NULL, GL_DYNAMIC_COPY );

		// Unbind any used GL objects to not corrupt state outside function.
		glBindVertexArray( GL_NONE );
		glBindBuffer( GL_ARRAY_BUFFER, GL_NONE );
		}

	
	void
	SpriteSheet::GLDestroyBuffers()
		{
		glDeleteVertexArrays( 1, &VAO );
		VAO = 0;

		glDeleteBuffers( 1, &glufferVertex );
		glufferVertex = 0;

		glDeleteBuffers( 1, &glufferTemplateID );
		glufferVertex = 0;

		glDeleteBuffers( 1, &glufferFrameTBO );
		glufferFrameTBO = 0;

		glDeleteTextures( 1, &texFrameTBO );
		texFrameTBO = 0;
		}


	} // namespace Bite