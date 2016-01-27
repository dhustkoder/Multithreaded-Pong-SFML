#ifndef BALL_H
#define BALL_H
#include <ctime>
#include <SFML/Graphics/Texture.hpp>
#include "Shape.h"
#include "SpriteAnimation.h"

class Ball final : public Shape
{
	static constexpr float defaultVelocity = 2.5;
	static constexpr float defaultRadius = 15;
	static constexpr int defaultTextureWidth = 64;
	static constexpr int defaultTextureHeight = 64;
	static constexpr const char* const defaultTextureFile = "../Resources/balltexture";
	static constexpr const char* const defaultExplosionFile = "../Resources/explosion";
public:
	// uses window size informed for class Shape
	Ball();
	
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void treatCollision() override;
	void update() override;
private:
	static void updateDirectionFunction(SpriteAnimation& sprite, const sf::Vector2f& velocity);
	SpriteAnimation m_sprite;

	
};












#endif // BALL_H
