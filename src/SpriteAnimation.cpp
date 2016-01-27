#include "pch.h"
#include "SpriteAnimation.h"

static float getPercent(const float value, const float percentage);

SpriteAnimation::SpriteAnimation(const char* const spriteSheetFile,
	const sf::Vector2i& spriteSize,
	const sf::Vector2i& maxLeftAndTop,
	const sf::Vector2f& velocityRef)
	: Sprite(spriteSheetFile, spriteSize),
	m_velocityRef(velocityRef),
	m_maxLeftAndTop(maxLeftAndTop),
	m_directionUpdateFunc(nullptr)
{

}



void SpriteAnimation::setFps(const unsigned fps) {
	m_chrono.setTime(fps);
}

void SpriteAnimation::setDirection(const int direction) {
	m_textureRect.top = m_textureRect.height * direction;
	if (m_textureRect.top <= m_maxLeftAndTop.y)
		m_sprite.setTextureRect(m_textureRect);
}

void SpriteAnimation::setUpdateDirectionFunction(UpdateDirectionFunction funcPtr) {
	m_directionUpdateFunc = funcPtr;
}

void SpriteAnimation::updateDirection() {
	if (m_directionUpdateFunc)
		m_directionUpdateFunc(*this, m_velocityRef);
}



void SpriteAnimation::updateAnimationFrame()
{
	if (m_chrono.finished())
	{
		if (m_textureRect.left > m_maxLeftAndTop.x)
			m_textureRect.left = 0;
		
		else
			m_textureRect.left += m_textureRect.width;

		m_sprite.setTextureRect(m_textureRect);
		auto averageVel = std::abs(m_velocityRef.x) * std::abs(m_velocityRef.y);
		m_chrono.setTime(static_cast<unsigned>(averageVel));
		m_chrono.start();
	}
}




float getPercent(const float value, const float percentage)
{
	return (value * 0.01f) * percentage;
}
