#include "BiteSprite\sprite.hpp"


#include "BiteSprite\spritesheet.hpp"



namespace Bite
	{

	Sprite::Sprite( ID id_, SpriteSheet* sheet_ ) :
		id(id_), sheet(sheet_), alive(true)
		{
		}


	Sprite::Sprite( ID id_, const std::string& frameName, SpriteSheet* sheet_ ) : 
		id(id_), sheet(sheet_), alive(true)	
		{
		Frame( frameName );
		Visible( true );
		UseColorKey( true );
		Scale( 1.0f );
		Rotation( 0.0f );
		PaletteID( 0 );
		}


	void
	Sprite::Visible( bool v )
		{
		if( !alive ) return;

		VertexBuffer<GLuint>& flagBuf = *sheet->spriteFlag;
		
		if( v ) 
			flagBuf.Element(id) |= Shader::fVisible;
		else
			flagBuf.Element(id) &= ~Shader::fVisible;
		}


	void
	Sprite::Flip( bool x, bool y )
		{
		if( !alive ) return;

		VertexBuffer<GLuint>& flagBuf = *sheet->spriteFlag;

		if( x )
			flagBuf.Element(id) |= Shader::fFlipX;
		else
			flagBuf.Element(id) &= ~Shader::fFlipX;
		if( y )
			flagBuf.Element(id) |= Shader::fFlipY;
		else
			flagBuf.Element(id) &= ~Shader::fFlipY;
		}


	void
	Sprite::UseColorKey( bool b )
		{
		if( !alive ) return;

		VertexBuffer<GLuint>& flagBuf = *sheet->spriteFlag;

		if( b )
			flagBuf.Element(id) |= Shader::fUseColorKey;
		else
			flagBuf.Element(id) &= ~Shader::fUseColorKey;
		}


	void
	Sprite::Position( float x, float y )
		{
		if( !alive ) return;

		VertexBuffer<GLfloat>& posBuf = *sheet->spritePosition;
		posBuf.Element( id ) = x;
		posBuf.Element( id, 1 ) = y;
		}


	void
	Sprite::ZIndex( float z )
		{
		if( !alive ) return;

		sheet->spritePosition->Element( id, 2 ) = z;
		}


	void
	Sprite::Rotation( float r )
		{
		if( !alive ) return;

		VertexBuffer<GLfloat>& rotscaleBuf = *sheet->spriteRotScale;

		rotscaleBuf.Element( id ) = r;
		}


	void
	Sprite::Scale( float s )
		{
		if( !alive ) return;
		VertexBuffer<GLfloat>& rotscaleBuf = *sheet->spriteRotScale;

		rotscaleBuf.Element( id, 1 ) = s;
		}


	void
	Sprite::PaletteID( ID pal )
		{
		if( !alive ) return;
		VertexBuffer<GLuint>& paletteIDBuf = *sheet->spritePalette;

		paletteIDBuf.Element( id ) = pal;
		}


	void
	Sprite::Frame( const std::string& frameName )
		{
		if( frameName.empty() ){
			sheet->spriteTemplateID->Element(id) = 0;
			return;
			}
		// Check name validity.
		StringID::const_iterator frameIt = 
			sheet->nameToFrameID.find( frameName );

		if( frameIt == sheet->nameToFrameID.end() ) 
			throw BadFrameName( frameName );

		Uint32 tid = frameIt->second; 

		sheet->spriteTemplateID->Element(id) = tid;
		}


	void
	Sprite::Drop()
		{
		if( !alive ) return;
		Visible( false );
		sheet->idGenSprite.RecycleID( id );
		alive = false;
		}


	} // namespace Bite