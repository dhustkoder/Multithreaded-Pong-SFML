#ifndef BALL_H
#define BALL_H
#include <ctime>
#include <SFML/Graphics/Texture.hpp>
#include "shape.h"



class Ball final : public Shape
{
	constexpr static float ballVelocity = 1.5;
	constexpr static float ballRadius = 38.0;
	constexpr static int ballTextureX = 64;
	constexpr static int ballTextureY = 64;
	enum class BallTextureDirection {
		Left, UpLeft, Up, UpRight, Right, DownRight, Down, DownLeft
	};
public:
	// uses window size informed for class Shape
	Ball() noexcept;
	void treatCollisionWith(const Shape &collidedShape) noexcept;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void update() noexcept override;
private:
	void updateTextureDirectionFrame() noexcept;
	void updateTextureAnimationFrame() noexcept;
	sf::IntRect m_textureRect;
	sf::Texture m_texture;
	std::clock_t m_clock;

};












#endif // BALL_H
