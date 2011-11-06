
#include "GL/glew.h"
#include "BiteSprite/bexception.hpp"
#include "BiteSprite/checkglerror.hpp"
#include "BiteSprite/shaderloader.hpp"
#include "BiteSprite/shaderhandle.hpp"
#include "BiteSprite/programhandle.hpp"

namespace Bite
	{
	
	//! The Shader namespace works as a singleton for holding all the GL information about the SpriteSheet shaders.
	/*!	The const references acts as a read only interface for the user without
	 *	the use of Get functions, while still remaining non-const inside.
	 */
namespace Shader
	{

	extern const ProgramHandle& glsProgSprite;
	extern const GLint& unilocProjection;
	extern const GLint& unilocView;
	extern const GLint& unilocSpriteSheet;
	extern const GLint& unilocSpriteFrame;
	extern const GLint& unilocColorKey;
	extern const GLuint attriblocVertex;
	extern const GLuint attriblocTemplateID;
	extern const GLuint attriblocFlags;
	extern const GLuint attriblocRotScale;

	void Init();
	void Quit();

	enum Flag {
		fNone = 0,
		fVisible = 1,
		fUseColorKey = 2
		};


	

	} // namespace Shader
	} // namespace Bite