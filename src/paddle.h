#ifndef PADDLE_H
#define PADDLE_H
#include <SFML/Graphics.hpp>


class Paddle
{
public:
	Paddle(float x, float y, float sizeX, float sizeY);
	float getX() const;
	float getY() const;
	void setPosition(float x, float y);
	void setVelocity(float x, float y);
	const sf::Vector2f& getVelocity() const;
	operator sf::Drawable&();
private:
	int x, y;
	sf::RectangleShape m_shape;
	sf::Vector2f m_velocity;
	
};



Paddle::Paddle(float x, float y, float sizeX, float sizeY)
{
	m_shape.setPosition(x, y);
	m_shape.setFillColor(sf::Color::White);
	m_shape.setSize({ sizeX,sizeY });
	
}


float Paddle::getX() const
{
	return m_shape.getPosition().x;
}



float Paddle::getY() const
{
	return m_shape.getPosition().y;
}


void Paddle::setPosition(float x, float y)
{
	m_shape.setPosition( x,y );
}

void Paddle::setVelocity(float x, float y)
{
	m_velocity.x = x;
	m_velocity.y = y;
}

const sf::Vector2f& Paddle::getVelocity() const
{
	return m_velocity;
}


inline Paddle::operator sf::Drawable&()
{
	return m_shape;
}

#endif