#ifndef BALL_H
#define BALL_H
#include <memory>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>

constexpr float ballRadius = 7.0F;
constexpr float ballHorizontalCompensation = ballRadius / 2.0F;
constexpr float ballVerticalCompensation = ballRadius / 2.0F;
class Ball
{
public:
	// give window size.
	Ball(const int winWidth, const int winHeight);
	const sf::Vector2f& getPosition() const;
	const sf::Vector2f& getVelocity() const;
	void setPosition(const float x, const float y);
	float getTop();
	float getBottom();
	float getLeft();
	float getRight();
	virtual void update();
	operator sf::Drawable&();
	
private:
	const int m_maxBottom, m_maxRight;
	std::unique_ptr<sf::CircleShape> m_shape;
	std::unique_ptr<sf::Vector2f> m_velocity;


	Ball(const Ball&) = delete;
	Ball(Ball&&) = delete;
};












#endif