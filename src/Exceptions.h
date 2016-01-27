#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>


void printException(const std::exception& exception,
	const char* const function, bool terminate = false);


void printException(const std::exception& exception,
	const char* const function, const char *const additionalMsg, bool terminate = false);




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







#endif
