#ifndef CPU_H
#define CPU_H
#include "paddle.h"



class Cpu final : public Paddle
{
	constexpr static auto cpuVelocity = 4.0F;
public:
	// uses defaultPaddleSize
	Cpu(Shape &ball) noexcept;
	
	//uses the given size
	Cpu(const float sizeX, const float sizeY, Shape &ball) noexcept;
	void update() noexcept override;
	bool isReady() noexcept override;
private:
	const Shape &m_ball;
	const unsigned m_up_screen_line;
	const unsigned m_down_screen_line;
};



inline bool Cpu::isReady() noexcept {
	return true;
}




#endif // CPU_H

