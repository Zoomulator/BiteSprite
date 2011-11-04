#ifndef BITE_FRAMEBUFFER_HPP
#define BITE_FRAMEBUFFER_HPP


#include "GL/glew.h"
#include "BiteSprite/projection.hpp"
#include "BiteSprite/checkglerror.hpp"

namespace Bite
	{

	void InitFramebuffer();

	void DestroyFramebuffer();

	void SetFramebufferForDraw();
	void SetFramebufferForRead();

	//! Draw the BiteSprite framebuffer to the window
	void FlipFramebuffer();

	} // namespace Bite

#endif // BITE_FRAMEBUFFER_HPP