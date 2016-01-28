#include "pch.h"
#include "SpriteEffect.h"
#include "GameWindow.h"

SFE_NAMESPACE
namespace effects {

constexpr Seconds SpriteEffect::defaultFramesPerSec;



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


void SpriteEffect::update() 
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




















}
NAMESPACE_END

