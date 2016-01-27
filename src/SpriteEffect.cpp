#include "pch.h"
#include "SpriteEffect.h"


constexpr Seconds SpriteEffect::defaultFramesPerSec;


SpriteEffect::SpriteEffect(const char* spriteSheetFile, 
	const sf::Vector2i& spriteSize, const sf::Vector2i& maxLeftAndTop) : 
	m_textureRect({0,0}, spriteSize),
	m_maxLeftAndTop(maxLeftAndTop)
{
	

	if (!m_texture.loadFromFile(spriteSheetFile))
		throw FileNotFoundException(std::string("file not found: ") + spriteSheetFile);

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(m_textureRect);
	m_sprite.setOrigin(spriteSize.x * 0.5f, spriteSize.y * 0.5f);
}


SpriteEffect::SpriteEffect(const SpriteEffect& rhs) :
	m_texture(rhs.m_texture),
	m_textureRect({0,0},{rhs.m_textureRect.width, rhs.m_textureRect.height}),
	m_maxLeftAndTop(rhs.m_maxLeftAndTop)
	
{
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(m_textureRect);
	m_sprite.setOrigin(rhs.m_sprite.getOrigin());
}


SpriteEffect::~SpriteEffect() {
	if(m_isActive)
		GameWindow::popSpriteEffect(*this);
}


void SpriteEffect::loadSpriteSheet(const char * spriteSheetFile, 
	const sf::Vector2i & spriteSize, const sf::Vector2i & leftAndTopMax)
{
	if (!m_texture.loadFromFile(spriteSheetFile))
		throw FileNotFoundException(std::string("file not found: ") + spriteSheetFile);
	
	m_textureRect.width = spriteSize.x;
	m_textureRect.height = spriteSize.y;
	
	m_maxLeftAndTop.x = leftAndTopMax.x;
	m_maxLeftAndTop.y = leftAndTopMax.y;

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(m_textureRect);
	m_sprite.setOrigin(spriteSize.x * 0.5f, spriteSize.y * 0.5f);
}



void SpriteEffect::setActive() {
	m_isActive = !m_isActive;
	if (m_isActive)
		GameWindow::pushSpriteEffect(*this);
	else
		GameWindow::popSpriteEffect(*this);
}


void SpriteEffect::update() 
{
	if ( m_isActive && m_frameDelay.finished() )
	{
		Chrono::Guard cGuard(m_frameDelay);
		if (m_textureRect.left == m_maxLeftAndTop.x)
		{
			if (m_textureRect.top == m_maxLeftAndTop.y) {
				GameWindow::popSpriteEffect(*this);
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
