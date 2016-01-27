#ifndef EFFECTS_H
#define EFFECTS_H
#include <SFML/Graphics/Drawable.hpp>
#include "ParticleSystem/Particle.h"
#include "Exceptions.h"
#include "Timewrp.h"


class SpriteEffect : public sf::Drawable
{
	static constexpr Seconds defaultFramesPerSec = 1;
public:
	SpriteEffect() = default;
	
	SpriteEffect(const char* spriteSheetFile, 
		const sf::Vector2i& spriteSize, const sf::Vector2i& maxLeftAndTop);
	
	~SpriteEffect();

	void loadSpriteSheet(const char* spriteSheetFile, 
		const sf::Vector2i& spriteSize, const sf::Vector2i& maxLeftAndTop);

	bool isActive() const;
	void setActive();
	void setFps(const unsigned fps);
	void setPosition(const float x, const float y);
	void setPosition(const sf::Vector2f& pos);

	
	virtual void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:

	bool m_isActive = false;
	Chrono m_frameDelay = defaultFramesPerSec;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::IntRect m_textureRect;
	sf::Vector2i m_maxLeftAndTop;
	
};



inline bool SpriteEffect::isActive() const {
	return m_isActive;
}

inline void SpriteEffect::setFps(const unsigned fps) {
	m_frameDelay.setTime(Seconds(1) / fps);
}

inline void SpriteEffect::setPosition(const float x, const float y) {
	m_sprite.setPosition(x, y);
}

inline void SpriteEffect::setPosition(const sf::Vector2f& pos) {
	m_sprite.setPosition(pos);
}

inline void SpriteEffect::draw(sf::RenderTarget& target, const sf::RenderStates states) const {
		target.draw(m_sprite, states);
}






#endif // EFFECTS_H
