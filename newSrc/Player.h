#ifndef PLAYER_H
#define PLAYER_H
#include "Paddle.h"

class Player final : public Paddle
{
	static constexpr auto defaultVelocity = 4.0F;
public:
	// uses DefaultPaddleSize
	Player();

	// uses the given size
	Player(const float sizeX, const float sizeY);
	void setKeys(const sf::Keyboard::Key keyUp, const sf::Keyboard::Key keyDown) noexcept;
	void update() override;
	bool isReady() override;
private:
	sf::Keyboard::Key m_kUp, m_kDown;

};




#endif // PLAYER_H
