#ifndef GAMESCORE_H
#define GAMESCORE_H

class GameWindow;
class Ball;

namespace GameScore {

void update(const Ball& ball) noexcept;

void display() noexcept;


}

#endif // GAMESCORE_H