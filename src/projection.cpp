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


	void SetResolution( int width, int height )
		{
		Projection::_matrix[0] = 1.0f / width;
		Projection::_matrix[5] = 1.0f / height;
		Projection::_matrix[10] = 1.0f / 1000.0f; // z depth of 1000
		}

	} // namespace Bite