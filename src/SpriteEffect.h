#ifndef EFFECTS_H
#define EFFECTS_H
#include <SFML/Graphics/Drawable.hpp>
#include "ParticleSystem/Particle.h"
#include "Timewrp.h"
#include "Sprite.h"


class SpriteEffect : public Sprite
{
	static constexpr Seconds defaultFramesPerSec = 1.f / 5.f;
public:
	SpriteEffect() = default;
	
	SpriteEffect(const char* spriteSheetFile, 
		const sf::Vector2i& spriteSize, const sf::Vector2i& maxLeftAndTop);

	SpriteEffect(const SpriteEffect& rhs);
	
	~SpriteEffect();

	void loadSpriteSheet(const char* spriteSheetFile, 
		const sf::Vector2i& spriteSize, const sf::Vector2i& maxLeftAndTop);

	bool isActive() const;
	void setActive();
	void setFps(const unsigned fps);


	virtual void update();
private:
	bool m_isActive = false;
	Chrono m_frameDelay = defaultFramesPerSec;
	sf::Vector2i m_maxLeftAndTop;
	
};



inline bool SpriteEffect::isActive() const {
	return m_isActive;
}

inline void SpriteEffect::setFps(const unsigned fps) {
	m_frameDelay.setTime(Seconds(1) / fps);
}






#endif // EFFECTS_H
