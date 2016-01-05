#ifndef PROCESSES_H
#define PROCESSES_H
class Shape;
class Ball;

enum class GameMode : int
{
	SinglePlayer,
	MultiplayerLocal
};

void startGame(GameMode mode);

#endif
