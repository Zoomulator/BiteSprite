#include "BiteSprite\imageloader.hpp"



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
		NameImageMap::const_iterator it = nameToImage.find( name );

		if( it == nameToImage.end() ) throw BadImageName( name );
		else return it->second;
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
		BASSERT( imageStorage == 0 );
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
		BASSERT( imageStorage != 0 );
		
		// Load the file if the name isn't already loaded.
		std::fstream file( path, std::ios_base::binary | std::ios_base::in );

		if( !file.is_open() || !file.good() )
			{
			throw FileError( path );
			}

		// TODO: Determine image type from suffix.
		return Load::Image( file, name, BMP() );
		}


	// Interprets a data stream as the given image type and uploads it to OpenGL.
	const Bite::Image
	Image( std::istream& imgData, const std::string& name, ImageLoadBase& loadType )
		{
		BASSERT( imageStorage != 0 );

		// Do not allow duplicates.
		if( imageStorage->Has( name ) )
			{
			// Throw exception because user could have tried to load different
			// files to the same name, so returning the image could lead to bugs.
			throw ImageNameAlreadyInUse( name );
			}

		ImageData data;
		loadType( imgData, data ); // Feed the data into the ImageData class.

		// Now it's ready to upload the image to OpenGL as a texture.
		Bite::Image image;
		glGenTextures( 1, &image.textureID );
		glBindTexture( GL_TEXTURE_2D, image.textureID );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, data.width, data.height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, data.pixels );

		image.name = name;
		image.width = data.width;
		image.height = data.height;

		imageStorage->Add( image );

		return image;
		}


	const Bite::Image
	Image( const std::string& name )
		{
		BASSERT( imageStorage != 0 );
		return imageStorage->Get( name );
		}

	} // namespace Load
	} // namespace Bite
