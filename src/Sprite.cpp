#include "pch.h"
#include "Sprite.h"




Sprite::Sprite(const char* spriteSheetFile, 
	const sf::Vector2i& spriteSize) : 
	m_textureRect({0,0}, spriteSize)
{
	

	if (!m_texture.loadFromFile(spriteSheetFile))
		throw FileNotFoundException(std::string("file not found: ") + spriteSheetFile);

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(m_textureRect);
	m_sprite.setOrigin(spriteSize.x * 0.5f, spriteSize.y * 0.5f);
}


void Sprite::loadSpriteSheet(const char* spriteSheetFile, 
	const sf::Vector2i & spriteSize)
{
	if (!m_texture.loadFromFile(spriteSheetFile))
		throw FileNotFoundException(std::string("file not found: ") + spriteSheetFile);
	
	m_textureRect.width = spriteSize.x;
	m_textureRect.height = spriteSize.y;

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(m_textureRect);
	m_sprite.setOrigin(spriteSize.x * 0.5f, spriteSize.y * 0.5f);
}