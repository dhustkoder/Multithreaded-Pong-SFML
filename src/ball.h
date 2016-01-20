#ifndef BALL_H
#define BALL_H
#include <ctime>
#include <SFML/Graphics/Texture.hpp>
#include "shape.h"

class Ball final : public Shape
{
	
	constexpr static float ballVelocity = 2.5;
	constexpr static float ballRadius = 15;
	constexpr static int ballTextureX = 64;
	constexpr static int ballTextureY = 64;
	enum class BallTextureDirection {
		Left, UpLeft, Up, UpRight, Right, DownRight, Down, DownLeft
	};
public:
	// uses window size informed for class Shape
	Ball() noexcept;
	void treatCollision() noexcept;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void update() noexcept override;
	void setDebugControll() { m_debugControll = !m_debugControll; }
private:
	void updateTextureDirectionFrame() noexcept;
	void updateTextureAnimationFrame() noexcept;
	void debugControll() noexcept;
	sf::IntRect m_textureRect;
	sf::Texture m_texture;
	std::clock_t m_clock;
	bool m_debugControll;

};












#endif // BALL_H
