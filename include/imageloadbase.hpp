#ifndef BITE_IMAGELOADBASE_HPP
#define BITE_IMAGELOADBASE_HPP



//The image load type is a functor object that is passed to the
//image loader to load the appropriate type of image file. The
//different load types inherits from the ImageLoadBase class

#include <istream>
#include "imagedata.hpp"

namespace Bite
	{


	class ImageLoadBase
		{
		protected:
		ImageLoadBase();
		virtual ~ImageLoadBase();

		public:
		
		// Load into existing ImageData object.
		virtual void
		operator() (std::istream& stream, ImageData& target) const;

		// Creates a new heap ImageData object and load the file into it.
		// Merely a convinience.
		ImageData* 
		operator() (std::istream& stream) const
			{
			ImageData* data = new ImageData();
			(*this)( stream, *data );
			return data;
			}
		};

	} //namespace Bite

#endif // BITE_IMAGELOADBASE_HPP