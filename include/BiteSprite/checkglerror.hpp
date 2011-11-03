#ifndef BITE_CHECKGLERROR_HPP
#define BITE_CHECKGLERROR_HPP

#include <string>
#include <iostream>
#include <GL/glew.h>


// TODO: Cleanup and throw exceptions

//! BiteSprite uses this function to check for errors.
/*!	The function is used indirectly via the CHECK_GL_ERRORS
 *	function macro, that can be enabled or disabled by defining
 *	BITE_GL_ERRORS in the preprocessor.
 */
inline
void CheckGLErrors( const std::string& note )
	{
	GLenum error = glGetError();

	switch( error )
		{
		case GL_NO_ERROR:
			return;
		case GL_INVALID_ENUM:
			std::cout << "GL error: Invalid enum." << std::endl;
			break;
		case GL_INVALID_VALUE:
			std::cout << "GL error: Invalid value." << std::endl;
			break;
		case GL_INVALID_OPERATION:
			std::cout << "GL error: Invalid operation." << std::endl;
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			std::cout << "GL error: Invalid framebuffer operation." << std::endl;
			break;
		case GL_OUT_OF_MEMORY:
			std::cout << "GL error: GL out of memory." << std::endl;
			break;
		default: return;
		}
		
	std::cout << note << std::endl;
	}


#ifdef BITE_GL_ERRORS
#define CHECK_GL_ERRORS(x) CheckGLErrors(x);
#else
#define CHECK_GL_ERRORS(x) 0;
#endif

//! /def BITE_GL_ERRORS Use this to make BiteSprite check for GL errors.

#endif // BITE_CHECKGLERROR_HPP