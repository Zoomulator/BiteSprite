#ifndef BITE_IMAGELOADER_HPP
#define BITE_IMAGELOADER_HPP


#include <map>
#include <fstream>
#include <iostream>

#include "GL/glew.h"
#include "BiteSprite/biteimage.hpp"
#include "BiteSprite/imageloadbase.hpp"
#include "BiteSprite/tgaload.hpp"
#include "BiteSprite/bexception.hpp"
#include "BiteSprite/bassert.hpp"


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
	const Bite::Image*
	ImageFromFile( const std::string& path, const std::string& name );

	const Bite::Image*
	Image( std::istream& imgData, const std::string& name, ImageLoadBase& loadType  );

	// Gets the image with this name.
	const Bite::Image*
	Image( const std::string& name );

	} // namespace Load


	class BadImageName : public Exception
		{
		public:
		BadImageName( const std::string& name )
			{
			errstr =
				"Bad image name: " + name;
			}

		protected:
			BadImageName() {}
		};


	class ImageNameAlreadyInUse : public BadImageName
		{
		public:
		ImageNameAlreadyInUse( const std::string& name )
			{
			errstr = 
				"Image name already in use: " + name;
			}
		};


	class BadFileFormat : public Exception
		{
		public:
		BadFileFormat( const std::string& path )
			{
			errstr =
				path + " is not a supported format.";
			}
		};

	} // namespace Bite




#endif // BITE_IMAGELOADER_HPP