#ifndef BALL_H
#define BALL_H
#include <ctime>
#include <SFML/Graphics/Texture.hpp>
#include "shape.h"
#include "effects.h"

class Ball final : public Shape
{
	
	static constexpr float defaultVelocity = 2.5;
	static constexpr float defaultRadius = 15;
	static constexpr int defaultTextureWidth = 64;
	static constexpr int defaultTextureHeight = 64;
	enum class BallTextureDirection {
		Left, UpLeft, Up, UpRight, Right, DownRight, Down, DownLeft
	};
public:
	// uses window size informed for class Shape
	Ball() throw(std::bad_alloc, FileNotFoundException);
	
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void treatCollision() override;
	void update() override;
private:
	void updateTextureDirectionFrame() noexcept;
	void updateTextureAnimationFrame() noexcept;

private:
	std::clock_t m_clock;
	sf::IntRect m_textureRect;
	sf::Texture m_texture;
	SpriteEffect m_explosionEffect;

};












#endif // BALL_H
