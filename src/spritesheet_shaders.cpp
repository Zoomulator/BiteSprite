#include "spritesheet_shaders.hpp"



namespace Bite
	{
namespace Shader
	{
	#define NULL 0

	GLuint _glsProgSprite = 0;
	GLuint _unilocProjection = 0;
	GLuint _unilocView = 0;
	GLuint _unilocSpriteSheet = 0;
	GLuint _unilocSpriteFrame = 0;

	const GLuint attriblocVertex = 0;
	const GLuint attriblocTemplateID = 1;
	const GLuint attriblocFlags = 2;

	const GLuint& glsProgSprite = _glsProgSprite;
	const GLuint& unilocProjection = _unilocProjection;
	const GLuint& unilocView = _unilocView;
	const GLuint& unilocSpriteSheet = _unilocSpriteSheet;
	const GLuint& unilocSpriteFrame = _unilocSpriteFrame;


namespace Source
	{

	const char * vertex =
		"#version 330\n"
		"\n"
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		"\n"
		"in vec4 vertex;\n"
		"in uint templateID;\n"
		"in uint flags;\n"
		"\n"
		"out uint gID;\n"
		"out uint gFlags;\n"
		"\n"
		"void main(void)\n"
		"	{\n"
		"	gID = ID;\n"
		"	gFlags = flags;\n"
		"	gl_Position = projection * view * vertex;\n"
		"	}\n"
		; // vertex end


	const char* geometry =
		"#version 330\n"
		"\n"
		"layout (point) in;\n"
		"layout (triangle_strip) out;\n"
		"layout (max_vertices = 4) out;"
		"\n"
		"in uint gID;\n"
		"in uint gFlags;\n"
		"out uint fID;\n"
		"out uint fFlags;\n"
		"smooth out vec2 texCoord;\n"
		"\n"
		"uniform samplerBuffer spriteFrame;\n"
		"\n"
		"void main(void)\n"
		"	{\n"
		"	fID = gID;\n"
		"	fFlags = gFlags;\n"
		"	if( glFlags & 1 ) // is visibility bit set?\n"
		"		{\n"
		"		Vec4 frame = texelFetch( spriteFrame, ID );\n"
		"		Vec2 size = frame.wz;\n"

		"		gl_Position.xy = gl_in[0].xy - (size.xy / 2.0 );\n"
		"		texCoord = vec2( 0, 0 );\n"
		"		EmitVertex();\n"

		"		gl_Position.x = gl_in[0].x + size.x / 2.0;\n"
		"		gl_Position.y = gl_in[0].y - size.y / 2.0;\n"
		"		texCoord = vec2( 1, 0 );\n"
		"		EmitVertex();\n"

		"		gl_Position.xy = gl_in[0].xy + (size.xy / 2.0f);\n"
		"		texCoord = vec2( 1, 1 );\n"
		"		EmitVertex();\n"

		"		gl_Position.x = gl_in[0].x - size.x/2.0f;\n"
		"		gl_Position.y = gl_in[0].y + size.y/2.0f;\n"
		"		texCoord = vec2( 0, 1 );\n"
		"		EmitVertex();\n"

		"		EndPrimitive();\n"
		"		}\n"
		"	}"
		; // geometry end


	const char* fragment =
		"#version 330\n"
		"uniform sampler2D spriteSheet;\n"
		"uniform samplerBuffer spriteFrame;\n"
		"\n"
		"in uint fID;\n"
		"in uint fFlags;\n"
		"in vec2 texCoord;\n"
		"out vec4 fragColor;\n"
		"\n"
		"void main(void)\n"
		"	{\n"
		"	Vec2 sheetSize = textureSize( spriteSheet, 0 );\n"
		"	Vec4 frame = texelFetch( spriteFrame, fID );\n"
		"	Vec2 spriteCoord = (frame.xy + texCoord * frame.zw) / sheetSize;\n"
		"	fragColor = texture( spriteSheet, spriteCoord );\n"
		"	\n"
		"	}"
		; // fragment end

	} // namespace Source


	void
	Init()
		{
		// TODO: Error checking
		GLuint glsVertex = glCreateShader( GL_VERTEX_SHADER );
		GLuint glsGeometry = glCreateShader( GL_GEOMETRY_SHADER );
		GLuint glsFragment = glCreateShader( GL_FRAGMENT_SHADER );
		_glsProgSprite = glCreateProgram();

		glShaderSource( glsVertex, 1, &Source::vertex, NULL );
		glShaderSource( glsGeometry, 1, &Source::geometry, NULL );
		glShaderSource( glsFragment, 1, &Source::fragment, NULL );

		glCompileShader( glsVertex );
		glCompileShader( glsGeometry );
		glCompileShader( glsFragment );

		glAttachShader( glsProgSprite, glsVertex );
		glAttachShader( glsProgSprite, glsGeometry );
		glAttachShader( glsProgSprite, glsFragment );

		glBindAttribLocation( glsProgSprite, attriblocVertex, "vertex" );
		glBindAttribLocation( glsProgSprite, attriblocTemplateID, "templateID" );
		glBindAttribLocation( glsProgSprite, attriblocFlags, "flags" );

		glLinkProgram( glsProgSprite );

		// Cleanup shader sources
		glDeleteShader( glsVertex );
		glDeleteShader( glsGeometry );

		glDeleteShader( glsFragment );

		// Find locations of uniforms:
		_unilocProjection = glGetUniformLocation( glsProgSprite, "projection" );
		_unilocView = glGetUniformLocation( glsProgSprite, "view" );
		_unilocSpriteSheet = glGetUniformLocation( glsProgSprite, "spriteSheet" );
		_unilocSpriteFrame = glGetUniformLocation( glsProgSprite, "spriteFrame" );
		}


	void
	Quit()
		{
		glDeleteProgram( glsProgSprite );
		}


	} // namespace Shader
	} // namespace Bite