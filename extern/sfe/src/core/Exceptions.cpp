#include <string>
#include "Exceptions.h"
#include "Utility.h"
SFE_NAMESPACE



void printException(const std::exception& exception,
	const char* const function, bool terminate)
{
	LOGerr("Exception caught in %s. Message: %s",
		function, exception.what());
	if (terminate) {
		CONSOLE_PAUSE("the program will terminate");
		std::exit(0);
	}
}

void printException(const std::exception& exception,
	const char* const function, const char *const additionalMsg, bool terminate)
{
	LOGerr("Exception caught in %s. \nException Message: %s",
		function, exception.what());
	LOGerr("OBS: %s", additionalMsg);

	if (terminate) {
		CONSOLE_PAUSE("the program will terminate.");
		std::exit(0);
	}
}

















NAMESPACE_END
