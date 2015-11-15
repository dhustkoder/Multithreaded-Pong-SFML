#ifndef BALL_H
#define BALL_H
#include <memory>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>


class Ball
{
public:
	Ball(const float x, const float y, const float radius);
	const sf::Vector2f& getPosition() const;
	const sf::Vector2f& getVelocity() const;
	void setPosition(const float x, const float y);
	void setVelocity(const float x, const float y);
	virtual void update();
	operator sf::Drawable& ();
private:
	std::unique_ptr<sf::CircleShape> m_shape;
	std::unique_ptr<sf::Vector2f> m_velocity;
};












#endif