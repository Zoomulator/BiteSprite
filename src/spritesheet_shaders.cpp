#include "BiteSprite/spritesheet_shaders.hpp"



namespace Bite
	{
namespace Shader
	{
	#define NULL 0

	GLint _glsProgSprite = 0;
	GLint _unilocProjection = 0;
	GLint _unilocView = 0;
	GLint _unilocSpriteSheet = 0;
	GLint _unilocSpriteFrame = 0;

	const GLuint attriblocVertex = 0;
	const GLuint attriblocTemplateID = 1;
	const GLuint attriblocFlags = 2;

	const GLint& glsProgSprite = _glsProgSprite;
	const GLint& unilocProjection = _unilocProjection;
	const GLint& unilocView = _unilocView;
	const GLint& unilocSpriteSheet = _unilocSpriteSheet;
	const GLint& unilocSpriteFrame = _unilocSpriteFrame;


namespace Source
	{

	const char * vertexPassthrough =
		"#version 330\n"
		"\n"
		"in vec4 vertex;"
		"\n"
		"void main(void)\n"
		"	{\n"
		"	gl_Position = vertex;\n"
		"	}"
		; // vertexPassthrough

	const char * geometryPassthrough =
		"#version 330\n"
		"\n"
		"layout (points) in;\n"
		"layout (triangle_strip) out;\n"
		"layout (max_vertices = 4) out;"
		"\n"
		"void main(void)\n"
		"	{\n"
		"	gl_Position.xy = gl_in[0].gl_Position.xy + vec2( -0.1, -0.1 );\n"
		"	EmitVertex();\n"
		"	gl_Position.xy = gl_in[0].gl_Position.xy + vec2( 0.1, -0.1 );\n"
		"	EmitVertex();\n"
		"	gl_Position.xy = gl_in[0].gl_Position.xy + vec2( 0.1, 0.1 );\n"
		"	EmitVertex();\n"
		"	gl_Position.xy = gl_in[0].gl_Position.xy + vec2( -0.1, 0.1 );\n"
		"	EmitVertex();\n"
		"	EndPrimitive();\n"
		"	}"
		; // geometryPassthrough


	const char* fragmentPassthrough =
		"#version 330\n"
		"\n"
		"out vec4 fragColor;\n"
		"\n"
		"void main(void)\n"
		"	{\n"
		"	fragColor = vec4(0.8, 0.1, 0.1, 1.0);\n"
		"	}"
		; // fragmentPassthrough

	const char * vertex =
		"#version 330\n"
		"\n"
		"uniform sampler2D spriteSheet;\n"
		"uniform usamplerBuffer spriteFrame;\n"
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
		"	gID = templateID;\n"
		"	gFlags = flags;\n"
		"	gl_Position = ivec4(vertex);//projection * view * vertex;\n"
		"	gl_Position.w = 1;\n"
		"	}\n"
		; // vertex end


	const char* geometry =
		"#version 330\n"
		"\n"
		"layout (points) in;\n"
		"layout (triangle_strip) out;\n"
		"layout (max_vertices = 4) out;"
		"\n"
		"in uint gID[];\n"
		"in uint gFlags[];\n"
		"flat out uint fID;\n"
		"flat out uint fFlags;\n"
		"smooth out vec2 texCoord;\n"
		"\n"
		"uniform usamplerBuffer spriteFrame;\n"
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		"\n"
		"void main(void)\n"
		"	{\n"
		"	fID = gID[0];\n"
		"	fFlags = gFlags[0];\n"
		"	if( (gFlags[0] & 1u) == 1u ) // is visibility bit set?\n"
		"		{\n"
		"		vec4 frame = texelFetch( spriteFrame, int(gID[0]) );\n"
		"		vec2 size = frame.zw;\n"

		"		gl_Position = gl_in[0].gl_Position;"
		"		gl_Position.xy += ceil( vec2(-size.x / 2, size.y / 2) );\n"
		"		gl_Position = projection * gl_Position;\n"
		"		texCoord = vec2( 0, 0 );\n"
		"		EmitVertex();\n"
				
		"		gl_Position = gl_in[0].gl_Position;"
		"		gl_Position.xy += ceil(-size/2);\n"
		"		gl_Position = projection * gl_Position;\n"
		"		texCoord = vec2( 0, 1 );\n"
		"		EmitVertex();\n"

		"		gl_Position = gl_in[0].gl_Position;\n"
		"		gl_Position.xy += ceil(size/2);"
		"		gl_Position = projection * gl_Position;\n"
		"		texCoord = vec2( 1, 0 );\n"
		"		EmitVertex();\n"

		"		gl_Position = gl_in[0].gl_Position;"
		"		gl_Position.xy += ceil( vec2( size.x/2, -size.y/2) );\n"
		"		gl_Position = projection * gl_Position;\n"
		"		texCoord = vec2( 1, 1 );\n"
		"		EmitVertex();\n"

		"		EndPrimitive();\n"
		"		}\n"
		"	}"
		; // geometry end


	const char* fragment =
		"#version 330\n"
		"uniform sampler2D spriteSheet;\n"
		"uniform usamplerBuffer spriteFrame;\n"
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		"\n"
		"flat in uint fID;\n"
		"flat in uint fFlags;\n"
		"in vec2 texCoord;\n"
		"out vec4 fragColor;\n"
		"\n"
		"void main(void)\n"
		"	{\n"
		"	vec2 sheetSize = textureSize( spriteSheet, 0 );\n"
		"	vec4 frame = texelFetch( spriteFrame, int(fID) );\n"
		"	vec2 spriteCoord = (frame.xy + texCoord * frame.zw) / sheetSize;\n"
		"	fragColor = texture( spriteSheet, spriteCoord );\n"
		"	\n"
		"	}"
		; // fragment end

	} // namespace Source
	

	void
	CheckShader( GLuint shader )
		{
		GLint shaderInfo = 0;
		glGetShaderiv( shader, GL_COMPILE_STATUS, &shaderInfo );

		if( shaderInfo == GL_FALSE )
			{
			char infoLog[1024];
			glGetShaderInfoLog( shader, 1024, NULL, infoLog );
			throw ShaderCompileError( infoLog );
			}
		}


	void
	CheckLink( GLuint program )
		{
		GLint programInfo = 0;
		glGetProgramiv( program, GL_LINK_STATUS, &programInfo );

		if( programInfo == GL_FALSE )
			{
			char infoLog[1024];
			glGetProgramInfoLog( program, 1024, NULL, infoLog );
			throw ShaderLinkError( infoLog );
			}
		}


	void
	Init()
		{
		GLuint glsVertex = glCreateShader( GL_VERTEX_SHADER );
		GLuint glsGeometry = glCreateShader( GL_GEOMETRY_SHADER );
		GLuint glsFragment = glCreateShader( GL_FRAGMENT_SHADER );
		_glsProgSprite = glCreateProgram();

		glShaderSource( glsVertex, 1, &Source::vertex, NULL );
		glShaderSource( glsGeometry, 1, &Source::geometry, NULL );
		glShaderSource( glsFragment, 1, &Source::fragment, NULL );
	
		try
			{
			glCompileShader( glsVertex );
			CheckShader( glsVertex );
			glCompileShader( glsGeometry );
			CheckShader( glsGeometry );
			glCompileShader( glsFragment );
			CheckShader( glsFragment );

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

			glLinkProgram( glsProgSprite );

			CheckLink( glsProgSprite );
			}
		catch( ShaderError& error )
			{
			glDeleteShader( glsVertex );
			glDeleteShader( glsGeometry );
			glDeleteShader( glsFragment );
			glDeleteProgram( glsProgSprite );
			throw;
			}
	
		// Find locations of uniforms:
		_unilocProjection = glGetUniformLocation( glsProgSprite, "projection" );
		_unilocView = glGetUniformLocation( glsProgSprite, "view" );
		_unilocSpriteSheet = glGetUniformLocation( glsProgSprite, "spriteSheet" );
		_unilocSpriteFrame = glGetUniformLocation( glsProgSprite, "spriteFrame" );

		// Cleanup shader sources
		glDeleteShader( glsVertex );
		glDeleteShader( glsGeometry );
		glDeleteShader( glsFragment );
		}


	void
	Quit()
		{
		glDeleteProgram( glsProgSprite );
		}


	} // namespace Shader
	} // namespace Bite