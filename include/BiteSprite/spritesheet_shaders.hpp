
#include "GL/glew.h"
#include "BiteSprite/bexception.hpp"
#include "BiteSprite/checkglerror.hpp"

namespace Bite
	{
	
	//! The Shader namespace works as a singleton for holding all the GL information about the SpriteSheet shaders.
	/*!	The const references acts as a read only interface for the user without
	 *	the use of Get functions, while still remaining non-const inside.
	 */
namespace Shader
	{

	extern const GLint& glsProgSprite;
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


	//! Base class for errors arising when setting up OpenGL shaders.
	class ShaderError : public Exception
		{
		};


 	class ShaderCompileError : public ShaderError
		{
		public:
		ShaderCompileError( const std::string& errorLog )
			{
			errstr = "Shader returned following compile error:\n";
			errstr += errorLog;
			}
		};

	class ShaderLinkError : public ShaderError
		{
		public:
		ShaderLinkError( const std::string& errorLog )
			{
			errstr = "Shader returned follow linking error:\n";
			errstr += errorLog;
			}
		};

	} // namespace Shader
	} // namespace Bite