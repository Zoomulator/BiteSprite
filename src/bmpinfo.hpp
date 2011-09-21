#ifndef BITE_BMPINFO_HPP
#define BITE_BMPINFO_HPP



namespace Bite
	{
namespace BMP
	{
	
	enum Offsets
		{
		PixDataOffset = 10,
		PixWidth = 18,
		PixHeight = 22,
		BPP = 28,
		BitmaskR = 56,
		BitmaskG = 58,
		BitmaskB = 62,
		BitmaskA = 66
		};

	} // namespace BMP
	} // namespace Bite

#endif // BITE_BMPINFO_HPP