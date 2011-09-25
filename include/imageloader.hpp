#ifndef BITE_IMAGELOADER_HPP
#define BITE_IMAGELOADER_HPP


#include <map>
#include <fstream>
#include <iostream>

#include "GL/glew.h"
#include "biteimage.hpp"
#include "imageloadbase.hpp"
#include "bmpload.hpp"
#include "bassert.hpp"


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

	// Returns the loaded image and names it.
	// If the name already exist, that is returned. It will
	// duplicate paths with different names however.
	const Bite::Image
	ImageFromFile( const std::string& path, const std::string& name );

	const Bite::Image
	Image( std::istream& imgData, const std::string& name, ImageLoadBase& loadType  );

	// Gets the image with this name.
	const Bite::Image
	Image( const std::string& name );

	} // namespace Load
	} // namespace Bite




#endif // BITE_IMAGELOADER_HPP