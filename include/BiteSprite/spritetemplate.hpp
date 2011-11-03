#ifndef BITE_SPRITETEMPLATE_HPP
#define BITE_SPRITETEMPLATE_HPP

#include <string>

#include "BiteSprite/types.hpp"


namespace Bite
	{


	class SpriteTemplate
		{
		public:
		Uint32 id;
		std::string name;
		Rect frame;
		bool active;
		};


	} // namespace Bite


#endif // BITE_SPRITETEMPLATE_HPP