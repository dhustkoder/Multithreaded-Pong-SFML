#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H
#include <vector>
#include "Sprite.h"
#include "Timewrp.h"

class SpriteAnimation : public Sprite
{
	using UpdateDirectionFunction = void(*)(SpriteAnimation&, const sf::Vector2f&);
	static constexpr Seconds defaultFps = 1.f / 15.f;
public:
	SpriteAnimation(const char* const spriteSheetFile,
		const sf::Vector2i& spriteSize,
		const sf::Vector2i& maxLeftAndTop,
		const sf::Vector2f& velocityReference);



	void setFps(const unsigned fps);
	void setDirection(const int direction);
	void setUpdateDirectionFunction(UpdateDirectionFunction funcPtr);


	void updateDirection();
	void updateAnimationFrame();
private:
	Chrono m_chrono = defaultFps;
	sf::Vector2i m_maxLeftAndTop;
	const sf::Vector2f& m_velocityRef;
	UpdateDirectionFunction m_directionUpdateFunc;
	
	
};






















#endif // SPRITEANIMATION_H