#ifndef BITE_ASSERT_HPP
#define BITE_ASSERT_HPP





#ifdef NDEBUG
#define BASSERT() 0
#else
#define BASSERT(x) { if(!(x)) __debugbreak(); }
#endif



#endif // BITE_ASSERT_HPP