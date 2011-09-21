#include <iostream>
#include "imagedata.hpp"


typedef Bite::ImageData::Uint32 Uint32;
typedef Bite::ImageData::Uint8 Uint8;



void PrintColor( Uint32 val, const Bite::ImageData& image )
	{
	std::cout << std::dec <<
		"R: "  << ((val & 0x00FF0000) >> 16 ) <<
		" G: " << ((val & 0x0000FF00) >> 8) <<
		" B: " << ((val & 0x000000FF)) << std::endl;
	}


int main()
	{
	Bite::ImageData image("Test.bmp");

	Uint32 pixVal;
	std::cout << "First pixel value:" << std::endl;
	
	pixVal = 0;
	image.PixAt( 0,0, &pixVal );
	std::cout << std::hex << pixVal << std::endl;
	PrintColor( pixVal, image );

	pixVal = 0;
	std::cout << "Second pixel:" << std::endl;
	image.PixAt( 1,0, &pixVal );
	std::cout << std::hex << pixVal << std::endl;
	PrintColor( pixVal, image );

	pixVal=0;
	std::cout << "Last pixel value:" << std::endl;
	image.PixAt(63,63, &pixVal );
	std::cout << std::hex << pixVal << std::endl;
	PrintColor( pixVal, image );

	system( "PAUSE" );
	}