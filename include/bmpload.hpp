#ifndef BITE_BMPINFO_HPP
#define BITE_BMPINFO_HPP

#include <memory>

#include "imageloadbase.hpp"
#include "bassert.hpp"

namespace Bite
	{
	class BMP : public ImageLoadBase
		{
		enum Offsets
			{
			PixDataOffset = 10,
			PixWidth = 18,
			PixHeight = 22,
			BPP = 28,
			BitmaskR = 56, // Is 56 correct? Currently broken anyway
			BitmaskG = 58,
			BitmaskB = 62,
			BitmaskA = 66
			};

		public:
	

		// Loads a BMP file into the ImageData struct.
		virtual void
		operator() ( std::istream& stream, ImageData& target ) const;

		};
	} // namespace Bite

#endif // BITE_BMPINFO_HPP