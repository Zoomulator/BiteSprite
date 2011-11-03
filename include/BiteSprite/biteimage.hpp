#ifndef BITE_IMAGE_HPP
#define BITE_IMAGE_HPP



#include "BiteSprite/types.hpp"


namespace Bite
	{

	//! Holds information about a texture loaded to GL
	class Image
		{
		public:
		GLuint textureID;
		std::string name;

		Uint32 width;
		Uint32 height;
		};
	

	} // namespace Bite


#endif // BITE_IMAGE_HPP