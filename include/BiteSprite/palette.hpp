#ifndef BITE_PALETTE_HPP
#define BITE_PALETTE_HPP

#include <vector>

#include "BiteSprite/types.hpp"

namespace Bite
	{
	class Image;


	class Palette
		{
		public:
		Palette();

		Uint32& operator[] ( size_t index );

		//! Makes a palette from the 256 first pixels in a true color image.
		static Palette
		FromTrueColor( const Image* );

		private:
		typedef std::vector<Uint32> Colormap;
		Colormap colormap;
		};


	} // namespace Bite



#endif // BITE_PALETTE_HPP