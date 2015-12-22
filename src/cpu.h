#ifndef CPU_H
#define CPU_H
#include <SFML/Graphics/RectangleShape.hpp>
#include "shape.h"

constexpr auto cpuVelocity = 4.0F;

class Cpu final : public Shape
{
public:
	Cpu(const unsigned winWidth, const unsigned winHeight, const float sizeX, const float sizeY, Shape &ball) noexcept;
	void update() noexcept override;
private:
	const Shape &m_ball;
	const unsigned m_up_screen_line;
	const unsigned m_down_screen_line;
};







#endif // CPU_H

