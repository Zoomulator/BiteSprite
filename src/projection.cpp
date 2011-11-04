#include "BiteSprite\projection.hpp"




namespace Bite
	{
namespace Projection
	{
	GLfloat _matrix[16] = {
		1,	0,	0,	0,
		0,	1,	0,	0,
		0,	0,	1,	0,
		0,	0,	0,	1
		};

	const GLfloat* matrix = _matrix;

	
	} // namespace Projection

	int width = 0;
	int height = 0;
	float pixSize = 0;

	void SetResolution( int w, int h, float ps )		
		{
		width = w;
		height = h;
		pixSize = ps;
		Projection::_matrix[0] = 2.0f / width;
		Projection::_matrix[5] = 2.0f / height;
		Projection::_matrix[10] = 1.0f / 1000.0f; // z depth of 1000
		}


	int ResWidth()
		{
		return width;
		}


	int ResHeight()
		{
		return height;
		}


	float PixSize()
		{
		return pixSize;
		}

	} // namespace Bite