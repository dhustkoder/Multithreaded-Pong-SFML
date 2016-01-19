#ifndef CPU_H
#define CPU_H
#include <ctime>
#include "paddle.h"



class Cpu final : public Paddle
{
	using seconds = float;
	constexpr static auto defaultCpuVelocity = 4.5f;
	constexpr static seconds defaultReactionDurationTime = 0.5f; // seconds
	constexpr static seconds defaultReactionDelayTime = 0.3f;
public:
	// uses defaultPaddleSize
	Cpu(const Shape &ball) noexcept;
	
	//uses the given size
	Cpu(const float sizeX, const float sizeY, const Shape &ball) noexcept;
	void setReactionDuration(seconds reactionTime);
	void setReactionDelay(seconds reactionDelay);
	void update() noexcept override;
	bool isReady() noexcept override;

private:
	void initializer();
private:
	const Shape &m_ball;
	std::clock_t m_reactionDurationClock;
	std::clock_t m_reactionDelayClock;
	seconds m_reactionDurationTime;
	seconds m_reactionDelayTime;
};



inline bool Cpu::isReady() noexcept {
	return true;
}




#endif // CPU_H

