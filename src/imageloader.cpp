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
		
		Bite::Image* NewImage( const std::string& name );
		bool Has( const std::string& name ) const;
		const Bite::Image* Get( const std::string& name ) const;
		void Remove( const std::string& name );

		typedef std::map<std::string, Image*> NameImageMap;
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
			delete it->second;
			}
		nameToImage.clear();
		}


	Bite::Image*
	ImageStorage::NewImage( const std::string& name )
		{
		// Note: should there be a name collision check?
		nameToImage[ name ] = new Bite::Image( name );
		Bite::Image* image = nameToImage[ name ];
		return image;
		}


	bool
	ImageStorage::Has( const std::string& name ) const
		{
		return nameToImage.find( name ) != nameToImage.end();
		}


	const Bite::Image*
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
	const Bite::Image*
	ImageFromFile( const std::string& path, const std::string& name ) 
		{
		BASSERT( imageStorage != 0 );
		
		// Load the file if the name isn't already loaded.
		std::fstream file( path, std::ios_base::binary | std::ios_base::in );

		if( !file.is_open() || !file.good() )
			{
			throw FileError( path );
			}

		if( path.find( ".tga" ) != std::string::npos )
			return Load::Image( file, name, TGA() );

		throw BadImageName( path );
		}


	// Interprets a data stream as the given image type and uploads it to OpenGL.
	const Bite::Image*
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

		Bite::Image* image = imageStorage->NewImage( name );
		loadType( imgData, *image ); // Feed the data into the Image class.

		image->UpdateTexture();

		return image;
		}


	const Bite::Image*
	Image( const std::string& name )
		{
		BASSERT( imageStorage != 0 );
		return imageStorage->Get( name );
		}

	} // namespace Load
	} // namespace Bite
