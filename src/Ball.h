#ifndef BALL_H
#define BALL_H
#include <ctime>
#include <SFML/Graphics/Texture.hpp>
#include "Shape.h"
#include "SpriteEffect.h"

class Ball final : public Shape
{
	static constexpr float defaultVelocity = 2.5;
	static constexpr float defaultRadius = 15;
	static constexpr int defaultTextureWidth = 64;
	static constexpr int defaultTextureHeight = 64;
	static constexpr const char* const defaultTextureFile = "../Resources/balltexture";
	static constexpr const char* const defaultExplosionFile = "../Resources/explosion";

	enum class BallTextureDirection {
		Left, UpLeft, Up, UpRight, Right, DownRight, Down, DownLeft
	};
public:
	// uses window size informed for class Shape
	Ball();
	
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void treatCollision() override;
	void update() override;
private:
	void updateTextureDirectionFrame();
	void updateTextureAnimationFrame();

private:
	std::clock_t m_clock;
	sf::IntRect m_textureRect;
	sf::Texture m_texture;
	SpriteEffect m_explosionEffect;

};












#endif // BALL_H
