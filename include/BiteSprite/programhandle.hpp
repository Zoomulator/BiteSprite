#ifndef BITE_PROGRAMHANDLE_HPP
#define BITE_PROGRAMHANDLE_HPP


#include "GL/glew.h"


namespace Bite
	{

	//! OpenGL shader program management class.
	/*! This class holds a program id and disposes of it when it
	 *	goes out of scope. Assignment and copy will transfer 
	 *	ownership and make the old handle invalid.	*/
	class ProgramHandle
		{
		public:
			ProgramHandle( GLuint programName );
			ProgramHandle( const ProgramHandle& );
			ProgramHandle& operator = ( const ProgramHandle& );
			ProgramHandle& operator = ( GLuint );

			operator GLuint () const
				{ return program; }

			~ProgramHandle();
			void Unload();

			bool IsValid() const
				{ return valid; }

		private:
			void Assign( GLuint programName );
			GLuint program;
			mutable bool valid;
		};


	} // namespace Bite



#endif // BITE_PROGRAMHANDLE_HPP