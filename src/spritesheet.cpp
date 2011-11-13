#include "BiteSprite/spritesheet.hpp"


namespace Bite
	{
	const int VertexUnitSize = 3;
	

	SpriteSheet::SpriteSheet( const std::string imageName, Uint32 bufferSize_ ) :
		sheet(0),
		VAO(0),
		bufferSize( bufferSize_ ),
		glufferFrameTBO(0),
		texFrameTBO(0),
		spriteCount(0)
		{
		ColorKeyNorm( 1.0, 1.0, 1.0 );
		GLBufferSetup();

		sheet = Load::Image( imageName );
		paletteBuffer.Add( *sheet );
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
		glBindTexture( GL_TEXTURE_2D, *sheet );
		glUniform1i( Shader::unilocSpriteSheet, 0 );
		CHECK_GL_ERRORS( "Bind sprite sheet texture, SpriteSheet::Render" )

		glActiveTexture( GL_TEXTURE1 ); // For template frame TBO
		glBindTexture( GL_TEXTURE_BUFFER, texFrameTBO );
		glTexBuffer( GL_TEXTURE_BUFFER, GL_RGBA32UI, glufferFrameTBO );
		glUniform1i( Shader::unilocSpriteFrame, 1 );
		CHECK_GL_ERRORS( "Bind frameTBO, SpriteSheet::Render" )

		glActiveTexture( GL_TEXTURE2 );
		glBindTexture( GL_TEXTURE_BUFFER, texPaletteTBO );
		glTexBuffer( GL_TEXTURE_BUFFER, GL_RGBA8UI, paletteBuffer );
		glUniform1i( Shader::unilocPalette, 2 );
		CHECK_GL_ERRORS( "Bind paletteTBO, SpriteSheet::Render" );

		glUniformMatrix4fv( Shader::unilocProjection, 1, GL_FALSE, Projection::matrix );
		glUniformMatrix4fv( Shader::unilocView, 1, GL_TRUE, View::matrix );
		glUniform1ui( Shader::unilocUsePalette, sheet->UsesPalette() );
		CHECK_GL_ERRORS( "Set uniform matrices, SpriteSheet::Render" );

		glUniform4fv( Shader::unilocColorKey, 1, colorKey );

		Framebuffer::SetForDraw();

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
	SpriteSheet::Synch()
		{
		spriteFlag->Synch();
		spritePosition->Synch();
		spriteTemplateID->Synch();
		spriteRotScale->Synch();
		spritePalette->Synch();

		// Update uniform array texture buffer thingies:
		glBindBuffer( GL_TEXTURE_BUFFER, glufferFrameTBO );
		CHECK_GL_ERRORS( "SpriteSheet::Synch, Bind Buffer" );
		glBufferSubData( GL_TEXTURE_BUFFER, 0, sizeof(GLuint) * frames.size(), &frames.front() );
		CHECK_GL_ERRORS( "SpriteSheet::Synch" );
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
			spriteTemplate.active = true;
			
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


	void
	SpriteSheet::DropTemplate( const std::string& templateName )
		{
		// Check name validity.
		StringID::const_iterator templateIt = nameToTemplateID.find( templateName );
		if( templateIt == nameToTemplateID.end() ) throw BadTemplateName( templateName );

		ID id = nameToTemplateID[ templateName ];
		templates[id].active = false;
		idGenTemplate.RecycleID( id );
		}


	Sprite
	SpriteSheet::CreateSprite( const std::string& templateName )
		{
		// Check name validity.
		StringID::const_iterator templateIt = nameToTemplateID.find( templateName );
		if( templateIt == nameToTemplateID.end() ) throw BadTemplateName( templateName );

		Uint32 tid = templateIt->second; 
		ID sid = idGenSprite.NewID();

		// Note: think of a better way to lay this out. Offsets and structures
		// in a single vector perhaps. Or a reusable buffer object, or something.
		BASSERT( sid <= spriteFlag->Size() );
		BASSERT( sid <= spritePosition->Size() );
		BASSERT( sid <= spriteTemplateID->Size() );
		BASSERT( sid <= spriteRotScale->Size() );
		BASSERT( sid <= spritePalette->Size() );

		IncrementBuffers();

		return Sprite( sid, tid, this );
		}


	void
	SpriteSheet::IncrementBuffers()
		{
		// Expand vectors and fill with 0
		spriteFlag->Grow( 1 );
		spritePosition->Grow( 1 );
		spriteTemplateID->Grow( 1 );
		spriteRotScale->Grow( 1 );
		spritePalette->Grow( 1 );
		++spriteCount;	
		}


	void
	SpriteSheet::ColorKeyNorm( float r, float g, float b, float range )
		{
		colorKey[0] = r;
		colorKey[1] = b;
		colorKey[2] = g;
		colorKey[3] = range;
		}


	void
	SpriteSheet::ColorKey( Uint8 r, Uint8 g, Uint8 b, Uint8 range )
		{
		ColorKeyNorm( r/255.0f, g/255.0f, b/255.0f, range/255.0f );
		}


	void
	SpriteSheet::AddPalette( const Palette& pal )
		{
		paletteBuffer.Add( pal );
		}

	
	void
	SpriteSheet::GLBufferSetup()
		{
		BASSERT( VAO == 0 );
		BASSERT( glufferFrameTBO == 0 );
		BASSERT( texFrameTBO == 0 );
				
		glGenVertexArrays( 1, &VAO );
		glClearColor( 0.2f, 0.8f, 0.2f, 1.0f );
				
		glGenBuffers( 1, &glufferFrameTBO );
		glGenTextures( 1, &texFrameTBO );
		glGenTextures( 1, &texPaletteTBO );
		
		glBindVertexArray( VAO );

		// Create buffer objects for the different vertex attributes.
		// 1. Bind the buffer object that will hold attribute data.
		// 2. Allocate the buffer memory, but no data uploaded (NULL passed).
		// 3. Create a pointer for the VAO so that you can access it in shader.
		// Repeat per buffer...
		spritePosition.reset( new VertexBuffer<GLfloat>( 
			VAO, Shader::attriblocVertex, GL_FLOAT, bufferSize, VertexUnitSize ) );
		spriteTemplateID.reset( new VertexBuffer<GLuint>(
			VAO, Shader::attriblocTemplateID, GL_UNSIGNED_INT, bufferSize ) );
		spriteFlag.reset( new VertexBuffer<GLuint>(
			VAO, Shader::attriblocFlags, GL_UNSIGNED_INT, bufferSize ) );
		spriteRotScale.reset( new VertexBuffer<GLfloat>(
			VAO, Shader::attriblocRotScale, GL_FLOAT, bufferSize, 2 ) );
		spritePalette.reset( new VertexBuffer<GLuint>(
			VAO, Shader::attriblocPaletteID, GL_UNSIGNED_INT, bufferSize ) );

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

		glDeleteTextures( 1, &texFrameTBO );
		texFrameTBO = 0;

		glDeleteTextures( 1, &texPaletteTBO );
		texPaletteTBO = 0;
		}


	} // namespace Bite