#include "pch.h"

int main()
{

#ifdef __linux__
	XInitThreads(); // prevent X11 threads error
#endif


	// single player and multiplayer test
	startGame(GameMode::SinglePlayer);
	
	startGame(GameMode::MultiplayerLocal);

}

