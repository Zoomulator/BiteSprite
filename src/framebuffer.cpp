#include "BiteSprite/framebuffer.hpp"



namespace Bite
	{
	namespace Framebuffer
		{
		GLuint FBO = 0;
		GLuint colorBuffer = 0;

		void Init()
			{
			glGenFramebuffers( 1, &FBO ); 
			glBindFramebuffer( GL_DRAW_FRAMEBUFFER, FBO );

			// Create color buffer
			glGenRenderbuffers(1, &colorBuffer );
			glBindRenderbuffer( GL_RENDERBUFFER, colorBuffer );
			glRenderbufferStorage( GL_RENDERBUFFER, GL_RGB8, ResWidth(), ResHeight() );
			glFramebufferRenderbuffer( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
				GL_RENDERBUFFER, colorBuffer );

			AnalyseBufferStatus(
				glCheckFramebufferStatus( GL_DRAW_FRAMEBUFFER ) );

			CHECK_GL_ERRORS( "Init framebuffer" );
			}


		void Destroy()
			{
			if( FBO != 0 ) glDeleteFramebuffers( 1, &FBO );
			FBO = 0;
			}


		void Reload()
			{
			if( Bite::HasInit() ) 
				{
				Destroy();
				Init();
				}
			}


		void SetForDraw()
			{
			glViewport(0,0, ResWidth(), ResHeight() );
			glBindFramebuffer( GL_DRAW_FRAMEBUFFER, FBO );
			GLenum fboBuffs[] = { GL_COLOR_ATTACHMENT0 };
			glDrawBuffers( 1, fboBuffs );
			CHECK_GL_ERRORS( "Framebuffer draw" );
			}


		void SetForRead()
			{
			glBindFramebuffer( GL_READ_FRAMEBUFFER, FBO );
			glReadBuffer( GL_COLOR_ATTACHMENT0 );
			CHECK_GL_ERRORS( "Framebuffer read" );
			}


		void Flip()
			{
			glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );

			GLenum drawbuffs[] = { GL_FRONT_LEFT };
			glDrawBuffers( 1, drawbuffs );
			SetForRead();

			int dstWidth =  ResWidth() * PixSize();
			int dstHeight = ResHeight() * PixSize();
			int dstLeft = WindowWidth()/2 - dstWidth/2;
			int dstBottom = WindowHeight()/2 - dstHeight/2;
			int dstRight = dstLeft + dstWidth;
			int dstTop = dstBottom + dstHeight;

			glBlitFramebuffer( 0,0, ResWidth(), ResHeight(), 
				dstLeft, dstBottom, dstRight, dstTop,
				GL_COLOR_BUFFER_BIT, GL_NEAREST );
		
			SetForDraw();
			glClear( GL_COLOR_BUFFER_BIT );

			CHECK_GL_ERRORS( "Frambuffer blit" );
			}
		} // namespace Framebuffer
	} // namespace Bite