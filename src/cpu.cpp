#include <chrono>
#include "cpu.h"
#include "gamewindow.h"
#include "utility.h"

Cpu::Cpu(Shape &ball) noexcept : 
	Shape(defaultPaddleSize.getOrigin(), new sf::RectangleShape(defaultPaddleSize)),
	m_ball(ball), m_up_screen_line(60), m_down_screen_line(GameWindow::height - 60)
{
	
}

Cpu::Cpu(const float sizeX, const float sizeY, Shape &ball) noexcept : 
	Shape({sizeX / 2, sizeY / 2}, new sf::RectangleShape({sizeX, sizeY})),
		m_ball(ball), m_up_screen_line(60), m_down_screen_line(GameWindow::height - 60)
{

}

void Cpu::update() noexcept
{
	//TODO: implement cpu player update
}
