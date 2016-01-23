#ifndef EFFECTS_H
#define EFFECTS_H
#include <SFML/Graphics/Drawable.hpp>
#include "timewrp.h"


class Effect : sf::Drawable
{
	constexpr static unsigned defaultFps = 0;
public:
	Effect(const char* spriteSheetFile, const sf::Vector2i spriteSize ,const sf::Vector2i leftAndTopMax);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	const sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::IntRect m_spriteRect;
	std::clock_t m_clock;
};




#endif // EFFECTS_H
