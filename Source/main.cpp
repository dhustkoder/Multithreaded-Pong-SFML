#include <iostream>



int main() {

	#if (defined(__PONGCPP_DEBUG__) && defined(DEBUG))
	std::cout << "HELLO DEBUG!\n"; 
	#elif (defined(__PONGCPP_RELEASE__) && defined(NDEBUG))
	std::cout << "HELLO RELEASE!\n";
	#else
	std::cout << "HELLO UNKNOWN!\n";
	#endif

	return 0;
}











