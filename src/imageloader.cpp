#include "imageloader.hpp"



namespace Bite
	{
	// Singleton to hold all GL information about images and is destroyed on app exit.
	// Hidden declaration. Interface is given in the namespace GL::Load.
	// Only visible in this file.
	class ImageStorage
		{
		public:
		~ImageStorage;
		void Clear();

		typedef std::map<std::string, Image> NameImageMap;
		NameImageMap nameToImage;
		};


----// ImageStorage implementation:

	ImageStorage::~ImageStorage()
		{
		Clear();
		}


	void
	ImageStorage::Clear()
		//---


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
		GL::imageStorage.Clear();
		}


	void
	Image()
		//---
	} // namespace Unload


namespace Load
	{
	const Bite::Image
	ImageFromFile( std::string path, std::string name ) 
		//---


	const Bite::Image
	Image( std::stream imgData, std::string name )
		//---


	const Bite::Image
	Image( std::string name );
		//---

	} // namespace Load
	} // namespace Bite
