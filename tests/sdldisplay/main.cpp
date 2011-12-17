#include <SDL/SDL.h>

#include <BiteSprite/bite.hpp>
#include <BiteSprite/animationsheet.hpp>

#include <GL/glew.h>


SDL_Surface* screen;
int width = 800;
int height = 600;
float marioRot = 0;
int marioPosX = 0;
int marioPosY = 0;
int palette = 0;
int pcount = 0;

int circX = 150;
int circY = 0;
int circR = 100;
float circRot = 0;
const float PI = 3.141592f;

void LoadBite()
	{
	Bite::WindowSize( width, height );
	Bite::SetResolution( width, height, 2 );
	Bite::Init();	
	Bite::Load::ImageFromFile( "paltest.tga", "palTest" );
	Bite::Load::ImageFromFile( "smb3sheet8bitPal.tga", "mario" );
	Bite::Load::ImageFromFile( "smb3sheet.tga", "marioTrue" );
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
		Bite::Palette pal = 
			Bite::Palette::FromTrueColor( Bite::Load::Image( "palTest" ) );
		sheet.AddPalette( pal );
		Bite::AnimationSheet sheet2( "marioTrue" );
		Bite::Rect r2 = { 11,5,13,15 };
		sheet.CreateFrame( "smallmario", r2 );
		sheet2.CreateFrame( "smallmario", r2 );
		Bite::Rect r4 = { 114, 4, 15, 16 };
		sheet2.CreateFrame( "smallmario2", r4 );
		Bite::Rect r5 = { 72, 4, 16, 16 };
		sheet2.CreateFrame( "smallmario3", r5 );
		Bite::Rect r = { 0,0,466,282 };
		sheet.CreateFrame( "all", r );
		Bite::Rect r3 = {11,26, 14,27};
		Bite::Point anchor( 14,27 );
		sheet.CreateFrame( "supermario", r3, anchor );

		Bite::AnimationFrames animFrames;
		animFrames.push_back( Bite::AnimationFrame( "smallmario3", 0.2f ) );
		animFrames.push_back( Bite::AnimationFrame( "smallmario2", 0.2f ) );
		animFrames.push_back( Bite::AnimationFrame( "smallmario", 0.2f ) );

		sheet2.CreateAnimationTemplate( "smallmariowalk", animFrames );
		Bite::Animation animMario = sheet2.CreateAnimation( "smallmariowalk" );
				
		Bite::Sprite sprite = sheet.CreateSprite( "all" );
		sprite.Position( 0, 100 );
		sprite.ZIndex( 0 );
		sprite.UseColorKey( false );

		Bite::Sprite sprite3 = sheet.CreateSprite( "supermario" );
		sprite3.Position( 0,0 );
		
		Bite::Sprite sprite2 = sheet2.CreateSprite( "smallmario" );
		sprite2.Position( 0, 0 );
		sprite2.Flip( false, false );
		sprite2.Visible(false);
		//sprite2.Scale( 2.0f );

		Bite::Rect r6 = { 342, 223, 16, 28 };
		sheet.CreateFrame( "stonemario", r6 );

		const int spriteCount = 50000;
		std::vector<Bite::Sprite> lottaSprites;

		//for( int i = 0; i < spriteCount; ++i )
		//	{
		//	lottaSprites.push_back( sheet.CreateSprite( "stonemario" ) );
		//	//lottaSprites[i].Position( (-300 + (i*10)%600), 200 - (i/60)*10 );
		//	}
		
		//lottaSprites[7].Drop();

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
				if( event.type == SDL_QUIT ||
					(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) )
					running = false;
				}
							
			/*for( int i = 0; i < spriteCount; ++i )
				{
				lottaSprites[i].Position(
					circX + cos( circRot + i * PI * 2 / (float)spriteCount ) * circR,
					circY + sin( circRot + i * PI * 2 / (float)spriteCount ) * circR );
				}*/
			
			Uint8* keystate = SDL_GetKeyState(NULL);
			if( keystate[SDLK_LEFT] ) marioPosX -= 1;
			if( keystate[SDLK_RIGHT] ) marioPosX += 1;
			if( keystate[SDLK_UP] ) marioPosY += 1;
			if( keystate[SDLK_DOWN] ) marioPosY -= 1;
			sprite2.Position( float(marioPosX), float(marioPosY) );
			animMario.Progress( 0.001f );

			++pcount;
			if( pcount > 10 )
				{
				palette = !palette;
				pcount = 0;
				sprite.PaletteID( palette );
				}

			circRot += fmod( PI * 2 / 1000.0f, PI*2);
			
			marioRot = fmod(marioRot+1.31f, 360);
			//sprite2.Rotation( marioRot );

			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			sheet.Synch();
			sheet.Render();

			sheet2.Synch();
			sheet2.Render();

			glFlush();

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