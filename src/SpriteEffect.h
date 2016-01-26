#ifndef EFFECTS_H
#define EFFECTS_H
#include <SFML/Graphics/Drawable.hpp>
#include "ParticleSystem/Particle.h"
#include "Exceptions.h"
#include "Timewrp.h"


class SpriteEffect : sf::Drawable
{
	static constexpr Seconds defaultFramesPerSec = 1 / 15;
public:
	SpriteEffect() noexcept;
	
	SpriteEffect(const char* spriteSheetFile, 
		const sf::Vector2i& spriteSize, const sf::Vector2i& maxLeftAndTop);

	void loadSpriteSheet(const char* spriteSheetFile, 
		const sf::Vector2i& spriteSize, const sf::Vector2i& maxLeftAndTop);

	bool isActive() const noexcept;
	void setActive() noexcept;
	void setFps(const unsigned fps) noexcept;
	void setPosition(const float x, const float y) noexcept;
	void setPosition(const sf::Vector2f& pos) noexcept;

	
	virtual void update() noexcept;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	void initialize();

	bool m_isActive;
	Chrono m_frameDelay;
	std::unique_ptr<sf::Texture> m_texture;
	std::unique_ptr<sf::Sprite> m_sprite;
	sf::IntRect m_textureRect;
	sf::Vector2i m_maxLeftAndTop;
	
};

inline void SpriteEffect::setActive() noexcept {
	m_isActive = !m_isActive;
}

inline bool SpriteEffect::isActive() const noexcept {
	return m_isActive;
}

inline void SpriteEffect::setFps(const unsigned fps) noexcept {
	m_frameDelay.setTime(Seconds(1) / fps);
}

inline void SpriteEffect::setPosition(const float x, const float y) noexcept {
	m_sprite->setPosition(x, y);
}

inline void SpriteEffect::setPosition(const sf::Vector2f& pos) noexcept {
	m_sprite->setPosition(pos);
}

inline void SpriteEffect::draw(sf::RenderTarget& target, const sf::RenderStates states) const {
		target.draw(*m_sprite, states);
}






#endif // EFFECTS_H
