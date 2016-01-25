#include <exception>
#include <string>



class FileNotFoundException : public std::exception
{
public:
	FileNotFoundException(const char *const _Message) : 
		std::exception(_Message)
	{
	
	}

	FileNotFoundException(const std::string& _Message) : 
		std::exception(_Message.c_str())
	{

	}

	FileNotFoundException(const FileNotFoundException& rhs) : 
		std::exception(rhs)
	{

	}
};