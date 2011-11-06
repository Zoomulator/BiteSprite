#include "BiteSprite/shaderhandle.hpp"



namespace Bite
	{

	ShaderHandle::ShaderHandle( GLuint shaderName ) :
		shader( shaderName ),
		valid( true )
		{
		}


	ShaderHandle::ShaderHandle( const ShaderHandle& B )
		{
		Assign( B.shader );
		B.valid = false;
		}


	ShaderHandle&
	ShaderHandle::operator = ( const ShaderHandle& B )
		{
		Assign( B.shader );
		B.valid = false;
		return *this;
		}


	ShaderHandle&
	ShaderHandle::operator = ( GLuint shaderName )
		{
		Assign( shaderName );
		return *this;
		}


	ShaderHandle::~ShaderHandle()
		{
		Unload();
		}
	

	void
	ShaderHandle::Unload()
		{
		if( valid )
			{
			glDeleteShader( shader );
			valid = false;
			}
		}


	void
	ShaderHandle::Assign( GLuint shaderName )
		{
		Unload();
		shader = shaderName;
		
		valid = glIsShader( shaderName ) == GL_TRUE;

		}


	} // namespace Bite