#ifndef BITE_PROJECTION_HPP
#define BITE_PROJECTION_HPP


#include <GL/glew.h>


namespace Bite
	{


	void SetResolution( int width, int height, float pixSize=1.0f );
	void WindowSize( int width, int height );

	int ResWidth();
	int ResHeight();
	float PixSize();

	int WindowWidth();
	int WindowHeight();


namespace Projection
	{
	
	
	extern const GLfloat* matrix;
	

	} // namespace Projection
	} // namespace Bite


#endif // BITE_PROJECTION_HPP