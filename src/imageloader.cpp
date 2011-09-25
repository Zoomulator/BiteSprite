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
		
		void Add( Bite::Image& image );
		bool Has( const std::string& name ) const;
		const Bite::Image Get( const std::string& name ) const;
		void Remove( const std::string& name );

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
		for( NameImageMap::iterator it = nameToImage.begin();
			it != nameToImage.end();
			++it )
			{
			glDeleteTextures( 1, &it->second.textureID );
			}

		nameToImage.clear();
		}


	void
	ImageStorage::Add( Bite::Image& image )
		{
		nameToImage[ image.name ] = image;
		}


	bool
	ImageStorage::Has( const std::string& name ) const
		{
		return nameToImage.find( name ) != nameToImage.end();
		}


	const Bite::Image
	ImageStorage::Get( const std::string& name ) const
		{
		return nameToImage[ name ];
		}


	void
	ImageStorage::Remove( const std::string& name )
		{
		nameToImage.erase( name );
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
	// Loads an image from file and uploads it to OpenGL.
	const Bite::Image
	ImageFromFile( const std::string& path, const std::string& name ) 
		{
		B_ASSERT( imageStorage != 0 );

		if( imageStorage->Has( name ) )
			{
			return imageStorage->Get( name );
			}
		// Load the file if the name isn't already loaded.
		std::ifstream file( path, std::ios_base::binary | std::ios_base::in );

		if( !file.good() )
			{
			// TODO: Throw exception here.
			std::cout << "Could not open file: " << path << std::endl;
			return Bite::Image();
			}

		// TODO: Determine image type from suffix.
		return Load::Image( file, name, BMP() );
		}


	// Note: Yes, both the function above and the one below does the name check,
	// but it's not a very expensive check for a function that's not called much.
	// I think it's better to call it twice than opening the file each time
	// ImageToFile is called with the same name only to return what's already loaded.


	// Interprets a data stream as the given image type and uploads it to OpenGL.
	const Bite::Image
	Image( std::istream& imgData, const std::string& name, ImageLoadBase& loadType )
		{
		B_ASSERT( imageStorage != 0 );

		if( imageStorage->Has( name ) )
			{
			return imageStorage->Get( name );
			}

		ImageData data;
		loadType( imgData, data ); // Feed the data into the ImageData class.

		// Now it's ready to upload the image to OpenGL as a texture.
		Bite::Image image;
		glGenTextures( 1, &image.textureID );
		glBindTexture( GL_TEXTURE_2D, image.textureID );

		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, data.width, data.height, 0,
			GL_RGBA, GL_UNSIGNED_INT, data.pixels );

		image.name = name;
		image.width = data.width;
		image.height = data.height;

		return image;
		}


	const Bite::Image
	Image( const std::string& name )
		{
		B_ASSERT( imageStorage != 0 );
		return imageStorage->Get( name );
		}

	} // namespace Load
	} // namespace Bite
