#ifndef PADDLE_H
#define PADDLE_H
#include <SFML/Graphics.hpp>


constexpr float paddleVelocity = 5.0;
class Paddle
{
	friend class Player;
public:
	Paddle(const float x, const float y, const float sizeX, const float sizeY);
	const sf::Vector2f& getPosition() const;
	const sf::Vector2f& getVelocity() const;
	void setPosition(const float x, const float y);
	void setVelocity(const float x, const float y);
	virtual void update() = 0;
	operator sf::Drawable&();
private:
	sf::RectangleShape m_shape;
	sf::Vector2f m_velocity;
	
};




#endif