#ifndef BITE_IMAGELOADBASE_HPP
#define BITE_IMAGELOADBASE_HPP



//The image load type is a functor object that is passed to the
//image loader to load the appropriate type of image file. The
//different load types inherits from the ImageLoadBase class

#include <istream>
#include "BiteSprite/biteimage.hpp"
#include "BiteSprite/bexception.hpp"

namespace Bite
	{


	class ImageLoadBase
		{
		protected:
		virtual ~ImageLoadBase() {};

		public:
		
		// Load into existing Image object.
		virtual void
		operator() (std::istream& stream, Image& target) const = 0;
		};


	class UnsupportedImageFormat : Bite::Exception
		{
		public:
			UnsupportedImageFormat( const std::string& format )
				{
				errstr = "BiteSprite cannot load images of format: ";
				errstr += format;
				}
		};
	} //namespace Bite

#endif // BITE_IMAGELOADBASE_HPP