#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Window/Keyboard.hpp>
#include "paddle.h"



class Player final : public Paddle
{
	constexpr static auto playerVelocity = 4.0F;
public:
	// uses DefaultPaddleSize
	Player() noexcept;

	// uses the given size
	Player(const float sizeX, const float sizeY) noexcept;
	//void tremble(int force);
	void setKeys(const sf::Keyboard::Key keyUp, const sf::Keyboard::Key keyDown);
	void update() noexcept override;
	bool isReady() noexcept override;
private:
	sf::Keyboard::Key m_kUp, m_kDown;

};




#endif // PLAYER_H
