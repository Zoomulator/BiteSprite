#ifndef BITE_TGALOAD_HPP
#define BITE_TGALOAD_HPP

#include <cstring>

#include "BiteSprite/imageloadbase.hpp"
#include "BiteSprite/bassert.hpp"


namespace Bite
	{
	class TGA : public ImageLoadBase
		{
		struct Header
			{
			Uint8 idLength;
			Uint8 colorMapType;
			Uint8 imageType;

			struct ColorMapSpec
				{
				Uint16 firstEntryIndex;
				Uint16 colorMapLength;
				Uint8 colorMapEntrySize;
				} colorMapSpec;

			struct ImageSpec
				{
				Uint16 xOrigin;
				Uint16 yOrigin;
				Uint16 width;
				Uint16 height;
				Uint8 pixelDepth;
				Uint8 imageDescriptor;
				} imageSpec;

			};


		public:
		// Loads a TGA file into the ImageData struct.
		virtual void
		operator() ( std::istream& stream, ImageData& target ) const;

		};

	} // namespace Bite


#endif // BITE_TGALOAD_HPP