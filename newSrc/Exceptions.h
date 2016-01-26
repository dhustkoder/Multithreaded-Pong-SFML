#include <exception>
#include <string>



class FileNotFoundException : public std::runtime_error
{
public:
	FileNotFoundException(const char *const _Message) : 
		std::runtime_error(_Message)
	{
	
	}

	FileNotFoundException(const std::string& _Message) : 
		std::runtime_error(_Message.c_str())
	{

	}

	FileNotFoundException(const FileNotFoundException& rhs) : 
		std::runtime_error(rhs)
	{

	}
};