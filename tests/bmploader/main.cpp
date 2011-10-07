#include <iostream>
#include <fstream>
#include "imagedata.hpp"
#include "bmpload.hpp"


void PrintColor( Bite::Uint32 val, const Bite::ImageData& image )
	{
	std::cout << std::dec <<
		"R: "  << ((val & 0x000000FF) ) <<
		" G: " << ((val & 0x0000FF00) >> 8) <<
		" B: " << ((val & 0x00FF0000) >> 16 ) << std::endl;
	}


int main()
	{
	std::fstream file( "Test.bmp", std::ios::binary | std::ios::in );
	if( !file.good() )
		{
		std::cout << "Failed to open file.";
		return 1;
		}
	
	Bite::ImageData image;
	Bite::BMP()( file, image );

	Bite::Uint32 pixVal;
	std::cout << "First pixel value:" << std::endl;
	
	pixVal = 0;
	pixVal = image.PixAt( 0,0 );
	std::cout << std::hex << pixVal << std::endl;
	PrintColor( pixVal, image );

	pixVal = image.PixAt( 1,0 );
	std::cout << "Second pixel:" << std::endl;
	std::cout << std::hex << pixVal << std::endl;
	PrintColor( pixVal, image );

	pixVal=image.PixAt(63,63);
	std::cout << "Last pixel value:" << std::endl;
	std::cout << std::hex << pixVal << std::endl;
	PrintColor( pixVal, image );

	system( "PAUSE" );
	}