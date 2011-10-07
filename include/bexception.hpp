#ifndef BITE_EXCEPTION_HPP
#define BITE_EXCEPTION_HPP



#include <exception>
#include <string>


namespace Bite
	{

	class Exception : public std::exception
		{
		std::string errstr;

		public:
		Exception( const std::string& str )
			{
			errstr = str;
			}

		const char* what() const throw()
			{
			return errstr.c_str();
			}
		};

	
	class FileError : public Exception
		{
		public:
		FileError( const std::string& filepath )
			{
			errstr =
				"Error reading/writing to: " + filepath;
			}
		};

	} // namespace Bite



#endif // BITE_EXCEPTION_HPP