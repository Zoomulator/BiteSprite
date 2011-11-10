#include "BiteSprite/spritesheet_shaders.hpp"



namespace Bite
	{
namespace Shader
	{
	#define NULL 0

	ProgramHandle _glsProgSprite = 0;
	GLint _unilocProjection = 0;
	GLint _unilocView = 0;
	GLint _unilocSpriteSheet = 0;
	GLint _unilocSpriteFrame = 0;
	GLint _unilocColorKey = 0;
	GLint _unilocPalette = 0;
	GLint _unilocUsePalette = 0;

	const GLuint attriblocVertex = 0;
	const GLuint attriblocTemplateID = 1;
	const GLuint attriblocFlags = 2;
	const GLuint attriblocRotScale = 3;
	const GLuint attriblocPaletteID = 4;

	const ProgramHandle& glsProgSprite = _glsProgSprite;
	const GLint& unilocProjection = _unilocProjection;
	const GLint& unilocView = _unilocView;
	const GLint& unilocSpriteSheet = _unilocSpriteSheet;
	const GLint& unilocSpriteFrame = _unilocSpriteFrame;
	const GLint& unilocColorKey = _unilocColorKey;
	const GLint& unilocPalette = _unilocPalette;
	const GLint& unilocUsePalette = _unilocUsePalette;


	void
	Init()
		{
		// Load shader sources and create program.
		ShaderHandle glsVertex = 
			Shader::LoadFromFile( "spritesheet.vsh", GL_VERTEX_SHADER );
		ShaderHandle glsGeometry =
			Shader::LoadFromFile( "spritesheet.gsh", GL_GEOMETRY_SHADER );
		ShaderHandle glsFragment = 
			Shader::LoadFromFile( "spritesheet.fsh", GL_FRAGMENT_SHADER );

		_glsProgSprite = glCreateProgram();
			
		// Compile, attach attributes and link.
		glCompileShader( glsVertex );
		Shader::CheckCompile( glsVertex );

		glCompileShader( glsGeometry );
		Shader::CheckCompile( glsGeometry );

		glCompileShader( glsFragment );
		Shader::CheckCompile( glsFragment );

		glAttachShader( glsProgSprite, glsVertex );
		glAttachShader( glsProgSprite, glsGeometry );
		glAttachShader( glsProgSprite, glsFragment );
		CHECK_GL_ERRORS( "Shader attachment." )

		glBindAttribLocation( glsProgSprite, attriblocVertex, "vertex" );
		CHECK_GL_ERRORS( "Attribute binding." )
		glBindAttribLocation( glsProgSprite, attriblocTemplateID, "templateID" );
		CHECK_GL_ERRORS( "Attribute binding." )
		glBindAttribLocation( glsProgSprite, attriblocFlags, "flags" );
		CHECK_GL_ERRORS( "Attribute binding." )
		glBindAttribLocation( glsProgSprite, attriblocRotScale, "rotscale" );
		CHECK_GL_ERRORS( "Attribute binding." )
		glBindAttribLocation( glsProgSprite, attriblocPaletteID, "paletteID" );

		glLinkProgram( glsProgSprite );
		Shader::CheckLink( glsProgSprite );
	
		// Find locations of uniforms:
		_unilocProjection = glGetUniformLocation( glsProgSprite, "projection" );
		_unilocView = glGetUniformLocation( glsProgSprite, "view" );
		_unilocSpriteSheet = glGetUniformLocation( glsProgSprite, "spriteSheet" );
		_unilocSpriteFrame = glGetUniformLocation( glsProgSprite, "spriteFrame" );
		_unilocColorKey = glGetUniformLocation( glsProgSprite, "colorKey" );
		_unilocPalette = glGetUniformLocation( glsProgSprite, "palette" );
		_unilocUsePalette = glGetUniformLocation( glsProgSprite, "usePalette" );
		}


	void
	Quit()
		{
		_glsProgSprite.Unload();
		}


	} // namespace Shader
	} // namespace Bite