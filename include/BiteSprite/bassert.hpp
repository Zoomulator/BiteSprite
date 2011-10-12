#ifndef BITE_ASSERT_HPP
#define BITE_ASSERT_HPP


#include <iostream>


#ifdef NDEBUG
#define BASSERT() 0
#else
#define BASSERT(x) { \
	if(!(x)) { \
		std::cout << "BiteSprite assertion failed in " << __FILE__ << " on line: " << __LINE__ << std::flush; \
		__debugbreak(); } }
#endif



#endif // BITE_ASSERT_HPP