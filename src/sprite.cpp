#include "BiteSprite\sprite.hpp"


#include "BiteSprite\spritesheet.hpp"



namespace Bite
	{


	Sprite::Sprite( ID id_, ID templateID, SpriteSheet* sheet_ ) : 
		id(id_), sheet(sheet_)	
		{
		sheet->spriteTemplateID.at(id) = templateID;
		Visible( true );
		UseColorKey( true );
		Scale( 1.0f );
		Rotation( 0.0f );
		}


	void
	Sprite::Visible( bool v )
		{
		SpriteSheet::BufferUint& flagBuf = sheet->spriteFlag;
		
		if( v ) 
			flagBuf.at(id) |= Shader::fVisible;
		else
			flagBuf.at(id) &= ~Shader::fVisible;

		sheet->UpdateSprite( id );
		}


	void
	Sprite::UseColorKey( bool b )
		{
		SpriteSheet::BufferUint& flagBuf = sheet->spriteFlag;

		if( b )
			flagBuf.at(id) |= Shader::fUseColorKey;
		else
			flagBuf.at(id) &= ~Shader::fUseColorKey;

		sheet->UpdateSprite( id );
		}


	void
	Sprite::Position( float x, float y, Anchor anchor )
		{
		switch(anchor)
			{
		case Center:
			break;
		case TopLeft:
				{
				Rect frame = sheet->templates[ sheet->spriteTemplateID.at(id) ].frame;
				x += std::ceil(frame.w/2.0f);
				y -= std::ceil(frame.h/2.0f);
				}
			}

		SpriteSheet::BufferFloat& posBuf = sheet->spritePosition;
		posBuf.at( id * 3 ) = x;
		posBuf.at( id * 3 + 1 ) = y;

		sheet->UpdateSprite( id );
		}


	void
	Sprite::ZIndex( float z )
		{
		sheet->spritePosition.at( id * 3 + 2 ) = z;

		sheet->UpdateSprite( id );
		}


	void
	Sprite::Rotation( float r )
		{
		SpriteSheet::BufferFloat& rotscaleBuf = sheet->spriteRotScale;

		rotscaleBuf.at( id * 2 ) = r;

		sheet->UpdateSprite( id );
		}


	void
	Sprite::Scale( float s )
		{
		SpriteSheet::BufferFloat& rotscaleBuf = sheet->spriteRotScale;

		rotscaleBuf.at( id * 2 + 1 ) = s;

		sheet->UpdateSprite( id );
		}


	} // namespace Bite