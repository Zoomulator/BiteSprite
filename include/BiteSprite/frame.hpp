#ifndef BITE_SPRITETEMPLATE_HPP
#define BITE_SPRITETEMPLATE_HPP

#include <string>

#include "BiteSprite/types.hpp"


namespace Bite
	{

	class Frame
		{
		public:
		Uint32 id;
		std::string name;

		Rect rect;
		Point anchor;

		//! In use or not. Made false when dropped
		bool active; 
		};


	} // namespace Bite


#endif // BITE_SPRITETEMPLATE_HPP