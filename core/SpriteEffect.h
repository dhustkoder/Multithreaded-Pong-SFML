#ifndef EFFECTS_H
#define EFFECTS_H
#include "Entity.h"
#include "Timewrp.h"
SFE_NAMESPACE
namespace effects {
using namespace sfe::clock;
using namespace sfe::entity;

class SpriteEffect : public Entity<Sprite>
{

	static constexpr Seconds defaultFramesPerSec = 1.f / 5.f;
public:
	SpriteEffect() = default;
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
	sf::IntRect m_textureRect;
	sf::Vector2i m_maxLeftAndTop;
	
};



inline bool SpriteEffect::isActive() const {
	return m_isActive;
}

inline void SpriteEffect::setFps(const unsigned fps) {
	m_frameDelay.setTime(Seconds(1) / fps);
}





}
NAMESPACE_END
#endif // EFFECTS_H
