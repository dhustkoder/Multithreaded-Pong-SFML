#ifndef CPU_H
#define CPU_H
#include "paddle.h"
#include "timewrp.h"

class Cpu final : public Paddle
{
	constexpr static auto defaultVelocity = 4.5f;
	constexpr static Seconds defaultReactionDurationTime = 1.f;
	constexpr static Seconds defaultReactionDelayTime = 1.f;
public:
	// uses defaultPaddleSize
	Cpu(const Shape &ball) noexcept;
	
	//uses the given size
	Cpu(const float sizeX, const float sizeY, const Shape &ball) noexcept;
	void setReactionDuration(const Seconds reactionDuration) noexcept;
	void setReactionDelay(const Seconds reactionDelay) noexcept;
	void update() noexcept override;
	bool isReady() noexcept override;

private:
	const Shape &m_ball;
	Chrono m_reactionDuration = {defaultReactionDurationTime};
	Chrono m_reactionDelay = { defaultReactionDelayTime, true };
};



inline 
bool Cpu::isReady() noexcept {
	return true;
}

inline
void Cpu::setReactionDuration(const Seconds reactionDuration) noexcept {
	m_reactionDuration.setTime(reactionDuration);
};

inline
void Cpu::setReactionDelay(const Seconds reactionDelay) noexcept {
	m_reactionDelay.setTime(reactionDelay);
}


#endif // CPU_H

