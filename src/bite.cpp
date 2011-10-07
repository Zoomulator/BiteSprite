#include "bite.hpp"


namespace Bite
	{
	void Init()
		{
		InitImageLoader();
		Shader::Init();
		}


	void Quit()
		{
		QuitImageLoader();
		Shader::Quit();
		}
	}