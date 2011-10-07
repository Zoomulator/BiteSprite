
#include "GL/glew.h"


namespace Bite
	{
namespace Shader
	{

	extern const GLuint& glsProgSprite;
	extern const GLuint& unilocProjection;
	extern const GLuint& unilocView;
	extern const GLuint& unilocSpriteSheet;
	extern const GLuint& unilocSpriteFrame;
	extern const GLuint attriblocVertex;
	extern const GLuint attriblocTemplateID;
	extern const GLuint attriblocFlags;

	void Init();
	void Quit();

	enum Flag {
		fNone = 0,
		fVisible = 1
		};


	} // namespace Shader
	} // namespace Bite