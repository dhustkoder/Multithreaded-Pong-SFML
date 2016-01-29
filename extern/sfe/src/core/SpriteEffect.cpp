#include "pch.h"
#include "SpriteEffect.h"
#include "GameWindow.h"

SFE_NAMESPACE
EFFECT_NAMESPACE

constexpr Seconds SpriteEffect::defaultFramesPerSec;




void SpriteEffect::loadSpriteSheet(const char* spriteSheetFile,
	const sf::Vector2i& spriteSize, const sf::Vector2i& maxLeftAndTop)
	
{
	m_textureRect = {0, 0, spriteSize.x, spriteSize.y};
	m_maxLeftAndTop = maxLeftAndTop;
	m_texture.loadFromFile(spriteSheetFile);
	this->setTexture(m_texture);
	this->setTextureRect({ 0, 0, spriteSize.x, spriteSize.y});
	this->setOrigin(static_cast<float>(spriteSize.x) * 0.5f,
		static_cast<float>(spriteSize.y) * 0.5f);
}




void SpriteEffect::setFps(const unsigned fps) {
	m_frameDelay.setTime(Seconds(1) / fps);
}


SpriteEffect::~SpriteEffect() {
	if(m_isActive)
		GameWindow::popDrawable(*this);
}



void SpriteEffect::setActive() 
{
	m_isActive = !m_isActive;
	if (m_isActive)
		GameWindow::pushDrawable(*this);
	else
		GameWindow::popDrawable(*this);
}


void SpriteEffect::onUpdate() 
{
	if ( m_isActive && m_frameDelay.finished() )
	{
		Chrono::Guard cGuard(m_frameDelay);
		if (m_textureRect.left == m_maxLeftAndTop.x)
		{
			if (m_textureRect.top == m_maxLeftAndTop.y) {
				m_textureRect.left = m_textureRect.top = 0;
				this->setActive();
			}

			else {
				m_textureRect.left = 0;
				m_textureRect.top += m_textureRect.height;
			}
		}

		else
			m_textureRect.left += m_textureRect.width;
		
		this->setTextureRect(m_textureRect);
	}

}




















NAMESPACE_END
NAMESPACE_END

