#ifndef SPRITE_H
#define SPRITE_H
#include <SFML/Graphics/Drawable.hpp>

class Sprite : public sf::Drawable
{
public:

	Sprite() = default;

	Sprite(const char* spriteSheetFile, 
		const sf::Vector2i& spriteSize);


	void loadSpriteSheet(const char* spriteSheetFile, 
		const sf::Vector2i& spriteSize);

	const sf::Vector2f& getPosition() const;

	void setTextureRect(const sf::IntRect& rect);
	void setPosition(const float x, const float y);
	void setPosition(const sf::Vector2f& pos);
protected:
	void draw() const override;

protected:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::IntRect m_textureRect;

};



inline 
const sf::Vector2f& getPosition() {
	return m_sprite.getPosition();
}


inline void Sprite::setTextureRect(const sf::IntRect& rect) {
	m_sprite.setTextureRect(rect);
}

inline void Sprite::setPosition(const float x, const float y) {
	m_sprite.setPosition(x, y);
}

inline void Sprite::setPosition(const sf::Vector2f& pos) {
	m_sprite.setPosition(pos);
}


inline void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const override {
	target.draw(m_sprite, states);

}










#endif // SPRITE_H