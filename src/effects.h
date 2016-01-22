#ifndef EFFECTS_H
#define EFFECTS_H
#include <ctime>
#include <SFML/Graphics/Drawable.hpp>



class Effect : sf::Drawable
{
public:
	Effect(const char* spriteSheetFile, sf::IntRect spriteRect);

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::IntRect m_spriteRect;
	std::clock_t m_clock;
};




#endif // !EFFECTS_H
