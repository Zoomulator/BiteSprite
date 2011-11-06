#ifndef BITE_SHADERHANDLE_HPP
#define BITE_SHADERHANDLE_HPP

#include "GL/glew.h"


namespace Bite
	{

	//! OpenGL shader management class.
	/*! This class holds a shader id and disposes of it when it
	 *	goes out of scope. Assignment and copy will transfer 
	 *	ownership and make the old handle invalid.	*/
	class ShaderHandle
		{
		public:
			ShaderHandle( GLuint shaderName );
			ShaderHandle( const ShaderHandle& );
			ShaderHandle& operator = ( const ShaderHandle& );
			ShaderHandle& operator = ( GLuint shaderName );

			operator GLuint () const 
				{ return shader; }

			~ShaderHandle();
			void Unload();

			bool IsValid() const
				{ return valid; }

		private:
			void Assign( GLuint );
			GLuint shader;
			mutable bool valid;
		};


	} // namespace Bite



#endif // BITE_SHADERHANDLE_HPP