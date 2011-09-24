#include "imageloader.hpp"



namespace Bite
	{
	// Singleton to hold all GL information about images and is destroyed on app exit.
	// Hidden declaration. Interface is given in the namespace GL::Load.
	// Only visible in this file.
	class ImageStorage
		{
		public:
		~ImageStorage();
		void Clear();

		typedef std::map<std::string, Image> NameImageMap;
		NameImageMap nameToImage;
		};


//--ImageStorage implementation:

	ImageStorage::~ImageStorage()
		{
		Clear();
		}


	void
	ImageStorage::Clear()
		{
		//---
		}


	ImageStorage* imageStorage = 0; // The singleton.


	void
	InitImageLoader()
		{
		imageStorage = new ImageStorage();
		}


	void
	QuitImageLoader()
		{
		delete imageStorage;
		imageStorage = 0;
		}
	

namespace Unload
	{
	void
	AllImages()
		{
		Bite::imageStorage->Clear();
		}


	void
	Image()
		{
		//---
		}
	} // namespace Unload


namespace Load
	{
	const Bite::Image
	ImageFromFile( const std::string& path, const std::string& name ) 
		{
		std::ifstream file( path, std::ios_base::binary | std::ios_base::in );

		if( !file.good() )
			{
			// TODO: Throw exception here.
			std::cout << "Could not open file: " << path << std::endl;
			return Bite::Image();
			}

		// TODO: Determine load type from suffix.
		Bite::Image image = Load::Image( file, name, BMP() );

		return image;
		}


	const Bite::Image
	Image( std::istream& imgData, const std::string& name, ImageLoadBase& loadType )
		{
		//---
		}


	const Bite::Image
	Image( std::string name );
		//---

	} // namespace Load
	} // namespace Bite
