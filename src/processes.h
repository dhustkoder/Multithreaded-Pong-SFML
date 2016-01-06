#ifndef PROCESSES_H
#define PROCESSES_H

enum class GameMode
{
	SinglePlayer,
	MultiplayerLocal
};

void startGame(GameMode mode);

#endif
