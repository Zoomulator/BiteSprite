#include <SDL/SDL.h>
#include <BiteSprite/bite.hpp>
#include <GL/glew.h>


SDL_Surface* screen;
int width = 640;
int height = 480;


void LoadBite()
	{
	Bite::Init();
	Bite::Load::ImageFromFile( "test.bmp", "smile_yellow" );
	}


void Run()
	{
	try
		{
		SDL_Init( SDL_INIT_EVERYTHING );

		int sdlFlags = 0;
		sdlFlags |= SDL_OPENGL;

		screen = SDL_SetVideoMode( width, height, 32, sdlFlags );
		LoadBite();
		glClearColor( 0.2f, 0.8f, 0.2f, 1.0f );
		
		Bite::SpriteSheet sheet( "smile_yellow" ); // <- something here crashes with glslDevil
		Bite::Rect r = { 32,32,32,32 };
		sheet.CreateTemplate( "all", r );
	
		Bite::Sprite sprite = sheet.CreateSprite( "all" );
		sprite.Position( 0, 100 );
		sprite.ZIndex( 0 );
		sprite.Visible( true );

		Bite::SetResolution( width, height );

		glPointSize( 10.0f );
		glDisable( GL_CULL_FACE );
		const int queryCount = 2;
		GLuint glquery[queryCount];
		glGenQueries( queryCount, glquery );

		bool running = true;
		while( running )
			{
			SDL_Event event;
			while( SDL_PollEvent( &event ) )
				{
				if( event.type == SDL_QUIT )
					running = false;
				}

			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			glBeginQuery( GL_PRIMITIVES_GENERATED, glquery[0] );
			glBeginQuery( GL_SAMPLES_PASSED, glquery[1] );
			sheet.Synch();
			sheet.Render();

			glEndQuery( GL_PRIMITIVES_GENERATED );
			glEndQuery( GL_SAMPLES_PASSED );
			GLint result[queryCount];
			glGetQueryObjectiv( glquery[0], GL_QUERY_RESULT, &result[0] );
			glGetQueryObjectiv( glquery[1], GL_QUERY_RESULT, &result[1] );
			//std::cout << "Primitives passed: " << result[0] << std::endl;
			//std::cout << "Samples passed: " << result[1] << std::endl;

			SDL_GL_SwapBuffers();
			}

		glDeleteQueries( queryCount, glquery );
		}
	catch( std::exception& exc )
		{
		std::cerr << "Caught exception: " << std::endl;
		std::cerr << exc.what() << std::endl;
		}
	}


int main( int argc, char* argv[] )
	{
	Run();

	SDL_Quit();
	Bite::Quit();
	
	system( "PAUSE" );
	return 0;
	}