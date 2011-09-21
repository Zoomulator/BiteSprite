#ifndef BITE_IMAGELOADER_HPP
#define BITE_IMAGELOADER_HPP


#include <map>

#include "GL/glew.h"
#include "biteimage.hpp"



namespace Bite
	{

	void InitImageLoader();
	void QuitImageLoader();

namespace Unload
	{
	// Clears all loaded textures in OpenGL.
	void AllImages();

	// Unloads specific named image from OpenGL.
	void Image( std::string name );

	} // namespace Unload


namespace Load 
	{

	// Returns the loaded image and names it. Will not load the same image twice
	const Bite::Image
	ImageFromFile( std::string path, std::string name );

	const Bite::Image
	Image( std::stream imgData, std::string name );

	// Gets the image with this name.
	const Bite::Image
	Image( std::string name );

	} // namespace Load
	} // namespace Bite




#endif // BITE_IMAGELOADER_HPP