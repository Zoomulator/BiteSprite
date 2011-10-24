#include "BiteSprite/spritesheet.hpp"


namespace Bite
	{
	const int VertexUnitSize = 3;
	

	SpriteSheet::SpriteSheet( const std::string imageName, Uint32 bufferSize_ ) :
		VAO(0),
		bufferSize( bufferSize_ ),
		glufferVertex(0),
		glufferTemplateID(0),
		glufferFlag(0),
		glufferFrameTBO(0),
		texFrameTBO(0),
		spriteCount(0)
		{
		GLBufferSetup();

		sheet = Load::Image( imageName );
		}


	SpriteSheet::~SpriteSheet()
		{
		GLDestroyBuffers();
		}


	void
	SpriteSheet::Render() const
		{
		// Bindings:
		glUseProgram( Shader::glsProgSprite );
		CHECK_GL_ERRORS( "Program binding, SpriteSheet::Render" )
		glBindVertexArray( VAO );
		CHECK_GL_ERRORS( "Vertex Array binding, SpriteSheet::Render" )
			
		// Uniforms:
		glActiveTexture( GL_TEXTURE0 ); // For sprite sheet
		glBindTexture( GL_TEXTURE_2D, sheet.textureID );
		glUniform1i( Shader::unilocSpriteSheet, 0 );
		CHECK_GL_ERRORS( "Bind sprite sheet texture, SpriteSheet::Render" )

		glActiveTexture( GL_TEXTURE1 ); // For template frame TBO
		glBindTexture( GL_TEXTURE_BUFFER, texFrameTBO );
		glTexBuffer( GL_TEXTURE_BUFFER, GL_RGBA32UI, glufferFrameTBO );
		glUniform1i( Shader::unilocSpriteFrame, 1 );
		CHECK_GL_ERRORS( "Bind frameTBO, SpriteSheet::Render" )

		glUniformMatrix4fv( Shader::unilocProjection, 1, GL_FALSE, Projection::matrix );
		glUniformMatrix4fv( Shader::unilocView, 1, GL_TRUE, View::matrix );
		CHECK_GL_ERRORS( "Set uniform matrices, SpriteSheet::Render" );

		glDrawArrays( GL_POINTS, 0, spriteCount );
		CHECK_GL_ERRORS( "Draw arrays, SpriteSheet::Render" );

		// Unbind:
		glActiveTexture( GL_TEXTURE2 );
		glBindTexture( GL_TEXTURE_2D, GL_NONE );

		glActiveTexture( GL_TEXTURE0 );
		glBindTexture( GL_TEXTURE_2D, GL_NONE );

		glBindVertexArray( GL_NONE );
		glUseProgram( GL_NONE );

		CHECK_GL_ERRORS( "SpriteSheet::Render" );

		
		}


	void
	SpriteSheet::SynchRange( ID first, Uint32 size )
		{
		glBindVertexArray( VAO );

		// Update vertex arrays:
		glBindBuffer( GL_ARRAY_BUFFER, glufferVertex );
		glBufferSubData( GL_ARRAY_BUFFER, first, sizeof(GLfloat)* VertexUnitSize * size, &spritePosition[first*VertexUnitSize] );

		glBindBuffer( GL_ARRAY_BUFFER, glufferTemplateID );
		glBufferSubData( GL_ARRAY_BUFFER, first, sizeof(GLuint) * size, &spriteTemplateID[first] );

		glBindBuffer( GL_ARRAY_BUFFER, glufferFlag );
		glBufferSubData( GL_ARRAY_BUFFER, first, sizeof(GLuint) * size, &spriteFlag[first] );

		// Update uniform array texture buffer thingies:
		glBindBuffer( GL_TEXTURE_BUFFER, glufferFrameTBO );
		glBufferSubData( GL_TEXTURE_BUFFER, first, sizeof(GLuint) * frames.size(), &frames.front() );
				
		CHECK_GL_ERRORS( "SpriteSheet::Synch" );

		glBindBuffer( GL_TEXTURE_BUFFER, 0 );
		glBindVertexArray( GL_NONE );
		}


	void
	SpriteSheet::Synch()
		{
		// Sort the changed IDs into ranges and synch only those, instead of the whole buffer.		
		while( !changeSet.empty() )
			{
			IDSet::iterator first = changeSet.begin();
			IDSet::iterator last = first;
			IDSet::iterator it = first;
			// Find range that is without jumps between IDs.
			for( ;it != changeSet.end() && *it <= *last+1; ++it )
				{
				last = it;
				}
			SynchRange( *first, *last-*first+1 );
			changeSet.erase( first, ++last ); // Last needs to point beyond end here.
			}
		}


	void
	SpriteSheet::SynchAll()
		{
		SynchRange( 0, spriteCount );
		}


	void
	SpriteSheet::UpdateSprite( ID id )
		{
		changeSet.insert( id );
		}


	void
	SpriteSheet::CreateTemplate( const std::string& name, Rect frame )
		{
		StringID::const_iterator it = nameToTemplateID.find( name );

		if( it == nameToTemplateID.end() ) // If name's not taken
			{
			ID id = idGenTemplate.NewID();

			SpriteTemplate spriteTemplate;
			spriteTemplate.id = id;
			spriteTemplate.name = name;
			spriteTemplate.frame = frame;
			
			BASSERT( id <= templates.size() );
			// Create new place in vector only if ID equal to length
			if( id == templates.size() )
				{
				templates.push_back( spriteTemplate );
				frames.resize( frames.size() + 4 );
				}
			else
				{
				templates[id] = spriteTemplate;
				}			

			frames[ id*4 ] = frame.x;
			frames[ id*4 + 1 ] = frame.y;
			frames[ id*4 + 2 ] = frame.w;
			frames[ id*4 + 3 ] = frame.h;
			nameToTemplateID[name] = id; 
			}
		else // name is taken
			{
			throw TemplateNameAlreadyInUse( name );
			}
		}


	Sprite
	SpriteSheet::CreateSprite( const std::string& templateName )
		{
		Uint32 tid = nameToTemplateID[ templateName ];
		ID sid = idGenSprite.NewID();

		// Note: think of a better way to lay this out. Offsets and structures
		// in a single vector perhaps. Or a reusable buffer object, or something.
		BASSERT( sid <= spriteFlag.size() );
		BASSERT( sid <= spritePosition.size() );
		BASSERT( sid <= spriteTemplateID.size() );

		if( sid == spriteFlag.size() )
			{
			// Expand vectors and fill with 0
			spriteFlag.resize( spriteFlag.size() + 1, 0 );
			spritePosition.resize( spritePosition.size() + 3, 0 );
			spriteTemplateID.resize( spriteTemplateID.size() + 1, 0 );
			++spriteCount;
			}

		UpdateSprite( sid );

		return Sprite( sid, tid, this );
		}

	
	void
	SpriteSheet::GLBufferSetup()
		{
		BASSERT( VAO == 0 );
		BASSERT( glufferVertex == 0 );
		BASSERT( glufferTemplateID == 0 );
		BASSERT( glufferFlag == 0 );
		BASSERT( glufferFrameTBO == 0 );
		BASSERT( texFrameTBO == 0 );
				
		glGenVertexArrays( 1, &VAO );
		glClearColor( 0.2f, 0.8f, 0.2f, 1.0f );
				
		glGenBuffers( 1, &glufferVertex );
		glGenBuffers( 1, &glufferTemplateID );
		glGenBuffers( 1, &glufferFlag );
		glGenBuffers( 1, &glufferFrameTBO );
		glGenTextures( 1, &texFrameTBO );
		
		glBindVertexArray( VAO );

		glEnableVertexAttribArray( Shader::attriblocVertex );
		glEnableVertexAttribArray( Shader::attriblocTemplateID );
		glEnableVertexAttribArray( Shader::attriblocFlags );

		// Create buffer objects for the different vertex attributes.
		// 1. Bind the buffer object that will hold attribute data.
		// 2. Allocate the buffer memory, but no data uploaded (NULL passed).
		// 3. Create a pointer for the VAO so that you can access it in shader.
		// Repeat per buffer...
		glBindBuffer( GL_ARRAY_BUFFER, glufferVertex );
		glBufferData( GL_ARRAY_BUFFER, sizeof(GLfloat) * VertexUnitSize * bufferSize, NULL, GL_DYNAMIC_COPY );
		glVertexAttribPointer( Shader::attriblocVertex, VertexUnitSize, GL_FLOAT, GL_FALSE, 0, 0 );

		glBindBuffer( GL_ARRAY_BUFFER, glufferTemplateID );
		glBufferData( GL_ARRAY_BUFFER, sizeof(GLuint)*bufferSize, NULL, GL_DYNAMIC_COPY );
		glVertexAttribIPointer( Shader::attriblocTemplateID, 1, GL_UNSIGNED_INT, 0,0);

		glBindBuffer( GL_ARRAY_BUFFER, glufferFlag );
		glBufferData( GL_ARRAY_BUFFER, sizeof(GLuint)*bufferSize, NULL, GL_DYNAMIC_COPY );
		glVertexAttribIPointer( Shader::attriblocFlags, 1, GL_UNSIGNED_INT, 0, 0 );

		glBindBuffer( GL_TEXTURE_BUFFER, glufferFrameTBO );
		glBufferData( GL_TEXTURE_BUFFER, sizeof(GLuint)*4*bufferSize, NULL, GL_DYNAMIC_COPY );
		
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