#ifndef BITE_TYPES_HPP
#define BITE_TYPES_HPP

#include <map>

namespace Bite
	{

	typedef char Uint8;
	typedef unsigned short Uint16;
	typedef unsigned int Uint32;
	typedef int Int32;


	struct Rect
		{
		Uint32 x,y,w,h;
		};

	struct Point
		{
		Point( Uint32 x_, Uint32 y_ ) : x(x_), y(y_) {}
		Point() : x(0), y(0) {}
		Uint32 x,y;
		};

	} // namespace Bite

#endif // BITE_TYPES_HPP