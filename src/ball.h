#ifndef BALL_H
#define BALL_H
#include <ctime>
#include <SFML/Graphics/Texture.hpp>
#include "shape.h"

class Ball final : public Shape
{
	
	constexpr static float defaultVelocity = 2.5;
	constexpr static float defaultRadius = 15;
	constexpr static int defaultTextureWidth = 64;
	constexpr static int defaultTextureHeight = 64;
	enum class BallTextureDirection {
		Left, UpLeft, Up, UpRight, Right, DownRight, Down, DownLeft
	};
public:
	// uses window size informed for class Shape
	Ball() noexcept;
	
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void treatCollision() noexcept override;
	void update() noexcept override;
private:
	void updateTextureDirectionFrame() noexcept;
	void updateTextureAnimationFrame() noexcept;
	void debugControll() noexcept;
	sf::IntRect m_textureRect;
	sf::Texture m_texture;
	sf::Texture m_explosionTexture;
	sf::Sprite m_explosionSprite;
	std::clock_t m_clock;

#ifdef P_DEBUG
	bool m_debugControll;
public:
	void setDebugControll() { m_debugControll = !m_debugControll; }
#endif
};












#endif // BALL_H
