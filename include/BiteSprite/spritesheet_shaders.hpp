
#include "GL/glew.h"
#include "BiteSprite/bexception.hpp"
#include "BiteSprite/checkglerror.hpp"

namespace Bite
	{
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

	void Init();
	void Quit();

	enum Flag {
		fNone = 0,
		fVisible = 1,
		fUseColorKey = 2
		};


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