#include "BiteSprite/programhandle.hpp"


#include "BiteSprite/shaderhandle.hpp"



namespace Bite
	{

	ProgramHandle::ProgramHandle( GLuint programName ) :
		program( programName ),
		valid( true )
		{
		}


	ProgramHandle::ProgramHandle( const ProgramHandle& B )
		{
		Assign( B.program );
		B.valid = false;
		}


	ProgramHandle&
	ProgramHandle::operator = ( const ProgramHandle& B )
		{
		Assign( B.program );
		B.valid = false;
		return *this;
		}


	ProgramHandle&
	ProgramHandle::operator = ( GLuint programName )
		{
		Assign( programName );
		return *this;
		}


	ProgramHandle::~ProgramHandle()
		{
		Unload();
		}
	

	void
	ProgramHandle::Unload()
		{
		if( valid )
			{
			glDeleteProgram( program );
			valid = false;
			}
		}


	void
	ProgramHandle::Assign( GLuint programName )
		{
		Unload();
		program = programName;

		valid = glIsProgram( programName ) == GL_TRUE;			
		}


	} // namespace Bite