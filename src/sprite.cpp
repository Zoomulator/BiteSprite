#include "BiteSprite\sprite.hpp"


#include "BiteSprite\spritesheet.hpp"



namespace Bite
	{


	Sprite::Sprite( ID id_, ID templateID, SpriteSheet* sheet_ ) : 
		id(id_), sheet(sheet_)	
		{
		sheet->spriteTemplateID.at(id) = templateID;
		Visible( true );
		}


	void
	Sprite::Visible( bool v )
		{
		SpriteSheet::BufferUint& flagBuf = sheet->spriteFlag;
		
		if( v ) 
			flagBuf.at(id) |= Shader::fVisible;
		else
			flagBuf.at(id) &= Shader::fVisible;
		}


	void
	Sprite::Position( float x, float y )
		{
		SpriteSheet::BufferFloat& posBuf = sheet->spritePosition;
		posBuf.at( id * 3 ) = x;
		posBuf.at( id * 3 + 1 ) = y;
		}


	void
	Sprite::ZIndex( float z )
		{
		sheet->spritePosition.at( id * 3 + 2 ) = z;
		}


	} // namespace Bite