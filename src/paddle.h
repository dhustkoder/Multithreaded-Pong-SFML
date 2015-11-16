#ifndef PADDLE_H
#define PADDLE_H

#include <memory>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>


constexpr float paddleVelocity = 4.0F;
class Paddle
{
	friend class Player;
public:
	Paddle(const float x, const float y, const float sizeX, const float sizeY);

	const sf::Vector2f& getPosition() const;
	const sf::Vector2f& getVelocity() const;
	float getRight();
	float getLeft();
	float getTop();
	float getBottom();
	void setPosition(const float x, const float y);
	void setVelocity(const float x, const float y);
	virtual void update() = 0;
	operator sf::Drawable& ();
private:
	std::unique_ptr<sf::RectangleShape> m_shape;
	std::unique_ptr<sf::Vector2f> m_velocity;
	float m_horizontalCompensation, m_verticalCompensation;

	Paddle(const Paddle&) = delete;
	Paddle(Paddle&&) = delete;
	
};







inline float Paddle::getRight()
{
	return m_shape->getPosition().x + m_horizontalCompensation;
}

inline float Paddle::getLeft()
{
	return m_shape->getPosition().x - m_horizontalCompensation;
}



inline float Paddle::getTop()
{
	return m_shape->getPosition().y - m_verticalCompensation;
}

inline float Paddle::getBottom()
{
	return m_shape->getPosition().y + m_verticalCompensation;
}



#endif