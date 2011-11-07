#ifndef BITE_FRAMEBUFFER_HPP
#define BITE_FRAMEBUFFER_HPP


#include "GL/glew.h"
#include "Bitesprite/bite.hpp"
#include "BiteSprite/projection.hpp"
#include "BiteSprite/checkglerror.hpp"

namespace Bite
	{
	namespace Framebuffer
		{

		//! Sets up the framebuffer with the configured resolution.
		/*! Glew must be initialized ahead of this call.
		 *	Access violations will result if it's not.
		 *	Bite::Init() will call this and the user would
		 *	probably not need to call it.*/
		void Init();
		void Destroy();
		//! Destroys and sets up the framebuffer again with any new values.
		void Reload();

		//! Prepares framebuffer for draw operations.
		void SetForDraw();
		//! Prepares framebuffer for read operations.
		void SetForRead();

		//! Draw the BiteSprite framebuffer to the window.
		/*! Calling flip will draw the framebuffer with it's
		 *	configured resolution to the window. Smaller than
		 *	window resolutions will leave a black border
		 *	around the BiteSprite viewport. The framebuffer
		 *	is automatically cleared when flipped. */
		void Flip();


		} // namespace Framebuffer
	} // namespace Bite

#endif // BITE_FRAMEBUFFER_HPP