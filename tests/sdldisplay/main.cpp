#include <SDL/SDL.h>
#include <BiteSprite/bite.hpp>
#include <GL/glew.h>


SDL_Surface* screen;
int width = 800;
int height = 600;
float marioRot = 0;

void LoadBite()
	{
	Bite::WindowSize( width, height );
	Bite::SetResolution( width/3, height/3, 2 );
	Bite::Init();	
	Bite::Load::ImageFromFile( "smb3sheet.tga", "mario" );
	}


void Run()
	{
	try
		{
		SDL_Init( SDL_INIT_EVERYTHING );

		int sdlFlags = 0;
		sdlFlags |= SDL_OPENGL;

		screen = SDL_SetVideoMode( width, height, 32, sdlFlags );
		SDL_WM_SetCaption( "BiteSprite!", NULL );
		LoadBite();
		glClearColor( 0.2f, 0.8f, 0.2f, 1.0f );
		
		Bite::SpriteSheet sheet( "mario" );
		Bite::Rect r2 = { 11,5,13,15 };
		sheet.CreateTemplate( "smallmario", r2 );
		Bite::Rect r = { 0,0,466,282 };
		sheet.CreateTemplate( "all", r );
		Bite::Rect r3 = {11,26, 14,27};
		sheet.CreateTemplate( "supermario", r3 );
				
		Bite::Sprite sprite = sheet.CreateSprite( "all" );
		sprite.Position( 0, 100 );
		sprite.ZIndex( 0 );
		sprite.UseColorKey( false );

		Bite::Sprite sprite3 = sheet.CreateSprite( "supermario" );
		sprite3.Position( 0,-70, Bite::TopLeft );
		sprite3.Rotation( -50.0f );

		Bite::Sprite sprite2 = sheet.CreateSprite( "smallmario" );
		sprite2.Position( 0, 0, Bite::TopLeft );
		sprite2.Scale( 2.0f );

		Bite::Rect r4 = { 342, 223, 16, 28 };
		sheet.CreateTemplate( "stonemario", r4 );

		const int spriteCount = 1000;
		std::vector<Bite::Sprite> lottaSprites;

		for( int i = 0; i < spriteCount; ++i )
			{
			lottaSprites.push_back( sheet.CreateSprite( "stonemario" ) );
			lottaSprites[i].Position( (-300 + (i*10)%600), 200 - (i/60)*10 );
			}

		lottaSprites[7].Drop();

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

			
			marioRot = fmod(marioRot+1.31f, 360);
			sprite2.Rotation( marioRot );

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
			Bite::Framebuffer::Flip();
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