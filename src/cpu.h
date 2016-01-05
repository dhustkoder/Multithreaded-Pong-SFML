#ifndef CPU_H
#define CPU_H
#include <SFML/Graphics/RectangleShape.hpp>
#include "shape.h"

constexpr auto cpuVelocity = 4.0F;

class Cpu final : public Shape
{
public:
	// uses defaultPaddleSize
	Cpu(Shape &ball) noexcept;
	
	//uses the given size
	Cpu(const float sizeX, const float sizeY, Shape &ball) noexcept;
	void update() noexcept override;
private:
	const Shape &m_ball;
	const unsigned m_up_screen_line;
	const unsigned m_down_screen_line;
};







#endif // CPU_H

