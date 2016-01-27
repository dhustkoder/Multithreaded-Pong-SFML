#ifndef CPU_H
#define CPU_H
#include "Paddle.h"
#include "Timewrp.h"

class Cpu final : public Paddle
{
	static constexpr auto defaultVelocity = 4.5f;
	static constexpr Seconds defaultReactionDurationTime = 1.f;
	static constexpr Seconds defaultReactionDelayTime = 1.f;
public:
	// uses defaultPaddleSize
	Cpu(const Shape &ball);
	
	//uses the given size
	Cpu(const float sizeX, const float sizeY, const Shape &ball);
	void setReactionDuration(const Seconds reactionDuration);
	void setReactionDelay(const Seconds reactionDelay);
	void update() override;
	bool isReady() override;

private:
	const Shape &m_ball;
	Chrono m_reactionDuration = {defaultReactionDurationTime};
	Chrono m_reactionDelay = { defaultReactionDelayTime, true };
};



inline 
bool Cpu::isReady() {
	return true;
}


inline
void Cpu::setReactionDuration(const Seconds reactionDuration) {
	m_reactionDuration.setTime(reactionDuration);
};

inline
void Cpu::setReactionDelay(const Seconds reactionDelay) {
	m_reactionDelay.setTime(reactionDelay);
}


#endif // CPU_H

