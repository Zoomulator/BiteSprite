#ifndef BITE_TYPES_HPP
#define BITE_TYPES_HPP


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

	} // namespace Bite

#endif // BITE_TYPES_HPP