#include "pch.h"
#include "effects.h"


constexpr unsigned SpriteEffect::defaultFramesPerSec;
SpriteEffect::SpriteEffect(const char* spriteSheetFile, const sf::Vector2i spriteSize, const sf::Vector2i leftAndTopMax) noexcept :
	m_isActive(false),
	m_textureRect(0, 0, spriteSize.x, spriteSize.y),
	m_frameDelay(Seconds(1) / defaultFramesPerSec ),
	m_maxLeftAndTop(leftAndTopMax)
{
	m_texture.loadFromFile(spriteSheetFile);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(m_textureRect);
	m_sprite.setOrigin(spriteSize.x * 0.5f, spriteSize.y * 0.5f);

}



void SpriteEffect::update() noexcept
{
	if (m_isActive)
	{
		if (m_frameDelay.finished())
		{
			Chrono::ChronoGuard cGuard(m_frameDelay);
			if (m_textureRect.left == m_maxLeftAndTop.x)
			{
				if (m_textureRect.top == m_maxLeftAndTop.y) {
					m_textureRect.left = m_textureRect.top = 0;
					m_isActive = false;
				}

				else {
					m_textureRect.left = 0;
					m_textureRect.top += m_textureRect.height;
				}
			}
			else
				m_textureRect.left += m_textureRect.width;
			
			m_sprite.setTextureRect(m_textureRect);
		}

		
	}
}
