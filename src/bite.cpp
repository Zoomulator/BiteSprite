#include "BiteSprite\bite.hpp"


namespace Bite
	{
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
		Shader::Init();
		}


	void Quit()
		{
		QuitImageLoader();
		Shader::Quit();
		}
	}