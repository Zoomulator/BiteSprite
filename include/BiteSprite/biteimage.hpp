#ifndef BITE_IMAGE_HPP
#define BITE_IMAGE_HPP


#include <memory>
#include "BiteSprite/types.hpp"
#include "BiteSprite/palette.hpp"


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

		bool usesPalette;
		Palette palette;

		Image() :
			textureID(0),
			width(0),
			height(0),
			usesPalette(false)
			{}
		};
	

	} // namespace Bite


#endif // BITE_IMAGE_HPP