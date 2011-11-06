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

	const GLuint attriblocVertex = 0;
	const GLuint attriblocTemplateID = 1;
	const GLuint attriblocFlags = 2;
	const GLuint attriblocRotScale = 3;

	const ProgramHandle& glsProgSprite = _glsProgSprite;
	const GLint& unilocProjection = _unilocProjection;
	const GLint& unilocView = _unilocView;
	const GLint& unilocSpriteSheet = _unilocSpriteSheet;
	const GLint& unilocSpriteFrame = _unilocSpriteFrame;
	const GLint& unilocColorKey = _unilocColorKey;

//
//namespace Source
//	{
//
//	const char * vertexPassthrough =
//		"#version 330\n"
//		"\n"
//		"in vec4 vertex;"
//		"\n"
//		"void main(void)\n"
//		"	{\n"
//		"	gl_Position = vertex;\n"
//		"	}"
//		; // vertexPassthrough
//
//	const char * geometryPassthrough =
//		"#version 330\n"
//		"\n"
//		"layout (points) in;\n"
//		"layout (triangle_strip) out;\n"
//		"layout (max_vertices = 4) out;"
//		"\n"
//		"void main(void)\n"
//		"	{\n"
//		"	gl_Position.xy = gl_in[0].gl_Position.xy + vec2( -0.1, -0.1 );\n"
//		"	EmitVertex();\n"
//		"	gl_Position.xy = gl_in[0].gl_Position.xy + vec2( 0.1, -0.1 );\n"
//		"	EmitVertex();\n"
//		"	gl_Position.xy = gl_in[0].gl_Position.xy + vec2( 0.1, 0.1 );\n"
//		"	EmitVertex();\n"
//		"	gl_Position.xy = gl_in[0].gl_Position.xy + vec2( -0.1, 0.1 );\n"
//		"	EmitVertex();\n"
//		"	EndPrimitive();\n"
//		"	}"
//		; // geometryPassthrough
//
//
//	const char* fragmentPassthrough =
//		"#version 330\n"
//		"\n"
//		"out vec4 fragColor;\n"
//		"\n"
//		"void main(void)\n"
//		"	{\n"
//		"	fragColor = vec4(0.8, 0.1, 0.1, 1.0);\n"
//		"	}"
//		; // fragmentPassthrough
//
//	} // namespace Source
//	

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

		glLinkProgram( glsProgSprite );
		Shader::CheckLink( glsProgSprite );
	
		// Find locations of uniforms:
		_unilocProjection = glGetUniformLocation( glsProgSprite, "projection" );
		_unilocView = glGetUniformLocation( glsProgSprite, "view" );
		_unilocSpriteSheet = glGetUniformLocation( glsProgSprite, "spriteSheet" );
		_unilocSpriteFrame = glGetUniformLocation( glsProgSprite, "spriteFrame" );
		_unilocColorKey = glGetUniformLocation( glsProgSprite, "colorKey" );
		}


	void
	Quit()
		{
		_glsProgSprite.Unload();
		}


	} // namespace Shader
	} // namespace Bite