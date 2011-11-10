#ifndef BITE_IMAGE_HPP
#define BITE_IMAGE_HPP


#include "GL/glew.h"
#include <memory>
#include "BiteSprite/types.hpp"
#include "BiteSprite/palette.hpp"
#include "BiteSprite/colormask.hpp"


namespace Bite
	{
	const ColorMask internalMask( 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000 );

	//! Holds information about a texture loaded to GL
	class Image
		{
		public:
		enum Format { none, pal8bit, true32bit };

		Image( const std::string& name );
		~Image();

		//! Pointer to internal pixelmap.
		const Uint32* Pixels() const;
				
		void CopyPixels( Uint32* pix, Uint32 w, Uint32 h, Palette* pal=NULL );
		//! Take ownership of a pixelmap
		void AdoptPixels( Uint32* pix, Uint32 w, Uint32 h, Palette* pal=NULL );
		//! Uploads the texture to GL memory.
		void UpdateTexture();

		operator Palette() const { return palette; }
		operator GLuint() const { return textureID; }

		bool UsesPalette() const { return format == pal8bit; }
		
		private:
		Image( const Image& copy );

		GLuint textureID;
		std::string name;

		Uint32 width;
		Uint32 height;

		Format format;
		Palette palette;

		Uint32* pixels;
		};
	

	} // namespace Bite


#endif // BITE_IMAGE_HPP