#ifndef BITE_SHADERLOADER_HPP
#define BITE_SHADERLOADER_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "GL/glew.h"

#include "BiteSprite/bexception.hpp"


namespace Bite
	{
	namespace Shader
		{
		//! Loads the shader source in the stream into the already created shaderName
		void Source( std::istream& stream, GLuint shaderName );

		//! Creates a new shader and feeds the file's content to it as source.
		/*! The filename has no affect on parsing, but the shader type must be
		 *	specified to create the correct shader. The source is not compiled
		 *	by this function. */
		GLuint LoadFromFile( const std::string& path, GLenum shaderType );
		
		//! Checks the most resent glCompileShader result and prints a log on error.
		void CheckCompile( GLuint shader );

		//! Checks the most resent glLinkProgram result and prints a log on error.
		void CheckLink( GLuint program );


	
		//! Base class for errors arising when setting up OpenGL shaders.
		class Error : public Exception
			{
			};


		class FileError : public Shader::Error
			{
			public:
			FileError( const std::string& filepath )
				{
				errstr = "Error opening file: ";
				errstr += filepath;
				}
			};


 		class CompileError : public Shader::Error
			{
			public:
			CompileError( const std::string& errorLog )
				{
				errstr = "Shader returned following compile error:\n";
				errstr += errorLog;
				}
			};

		class LinkError : public Shader::Error
			{
			public:
			LinkError( const std::string& errorLog )
				{
				errstr = "Shader returned follow linking error:\n";
				errstr += errorLog;
				}
			};
		} // namespace Shader
	} // namespace Bite


#endif // BITE_SHADERLOADER_HPP