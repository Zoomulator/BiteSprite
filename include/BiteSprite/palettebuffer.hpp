#ifndef BITE_PALETTEBUFFER_HPP
#define BITE_PALETTEBUFFER_HPP

#include "GL/glew.h"

#include "BiteSprite/idgenerator.hpp"
#include "BiteSprite/palette.hpp"
#include "BiteSprite/checkglerror.hpp"

namespace Bite
	{


	class PaletteBuffer
		{

		public:
		PaletteBuffer();
		~PaletteBuffer();

		ID Add( Palette );

		operator GLuint () const
			{ return glufferID; }

		private:
		void CreateBuffer();
		void DestroyBuffer();

		void UpdateBuffer();
		void ResizeBuffer();

		GLuint glufferID;
		GLuint elementSize; // Size of element in bytes
		GLuint elementWidth; // Variables per element
		GLuint elementCount; // Number of elements in buffer

		typedef std::vector<Palette> PaletteV;
		PaletteV palettes;
		};


	} // namespace Bite



#endif // BITE_PALETTEBUFFER_HPP