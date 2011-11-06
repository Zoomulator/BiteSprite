#include "BiteSprite/shaderloader.hpp"



namespace Bite
	{

	namespace Shader
		{

		void Source( std::istream& stream, GLuint shaderName )
			{
			std::stringstream ss;
			ss << stream.rdbuf();
			const std::string& shaderString = ss.str();

			const char* shaderCStr = shaderString.c_str();
			int shaderLen = shaderString.size();
			glShaderSource( shaderName, 1, (const GLchar**)&shaderCStr, (GLint*)&shaderLen );
			}


		GLuint LoadFromFile( const std::string& path, GLenum shaderType )
			{
			std::ifstream file( path );
			if( !file.good() ) throw FileError(path);

			GLuint shader = glCreateShader( shaderType );
			Source( file, shader );
			return shader;
			}


		void
		CheckCompile( GLuint shader )
			{
			GLint shaderInfo = 0;
			glGetShaderiv( shader, GL_COMPILE_STATUS, &shaderInfo );

			if( shaderInfo == GL_FALSE )
				{
				char infoLog[1024];
				glGetShaderInfoLog( shader, 1024, NULL, infoLog );
				throw CompileError( infoLog );
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
				throw LinkError( infoLog );
				}
			}
		} // namespace Shader
	} // namespace Bite