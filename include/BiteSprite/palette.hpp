#ifndef BITE_PALETTE_HPP
#define BITE_PALETTE_HPP

#include <vector>

#include "BiteSprite/types.hpp"


namespace Bite
	{


	class Palette
		{
		public:
		Palette();

		Uint32& operator[] ( size_t index );

		private:
		typedef std::vector<Uint32> Colormap;
		Colormap colormap;
		};


	} // namespace Bite



#endif // BITE_PALETTE_HPP