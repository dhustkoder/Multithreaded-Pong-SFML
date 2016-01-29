#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>
#include <stdexcept>
#include "sfe.h"
SFE_NAMESPACE



void printException(const std::exception& exception,
	const char* const function, bool terminate = false);


void printException(const std::exception& exception,
	const char* const function, const char *const additionalMsg, bool terminate = false);


class FileNotFoundException : public std::runtime_error
{
public:
	explicit FileNotFoundException(const char *const what_arg) : 
		std::runtime_error(what_arg)
	{
	
	}

	explicit FileNotFoundException(const std::string& what_arg) : 
		std::runtime_error(what_arg.c_str())
	{

	}

	FileNotFoundException(const FileNotFoundException& rhs) : 
		std::runtime_error(rhs)
	{

	}
};






NAMESPACE_END
#endif
