#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Window/Keyboard.hpp>
#include "shape.h"

constexpr auto playerVelocity = 4.0F;

class Player final: public Shape
{
public:
	// pass the window's resolution, and player size
	Player(const unsigned winWidth, const unsigned winHeight, 
	const float sizeX, const float sizeY) noexcept;
	void setKeys(sf::Keyboard::Key keyUp, sf::Keyboard::Key keyDown);
	
	void update() noexcept override;
private:
	sf::Keyboard::Key m_kUp, m_kDown;

	Player(const Player&) = delete;
	Player(Player&&) = delete;
	Player& operator=(const Player&) = delete;
	Player& operator=(Player&&) = delete;

};




#endif // PLAYER_H