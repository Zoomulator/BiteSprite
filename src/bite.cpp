#include "BiteSprite\bite.hpp"


namespace Bite
	{
	bool hasInit = false;


	void Init()
		{
		GLenum err = glewInit();
		if (GLEW_OK != err)
			{
			/* Problem: glewInit failed, something is seriously wrong. */
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
			}
		fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

		InitImageLoader();
		Framebuffer::Init();
		Shader::Init();
		hasInit = true;
		}


	void Quit()
		{
		QuitImageLoader();
		Shader::Quit();
		hasInit = false;
		}


	bool HasInit()
		{
		return hasInit;
		}
	}