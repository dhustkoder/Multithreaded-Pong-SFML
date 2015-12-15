#include <chrono>
#include "cpu.h"
#include "utility.h"

Cpu::Cpu(const unsigned winWidth, const unsigned winHeight, const float sizeX, const float sizeY, Shape &ball) noexcept : 
	Shape(winWidth, winHeight, sizeX / 2, sizeY / 2, new sf::RectangleShape(sf::Vector2f(sizeX, sizeY))),
	m_ball(ball), m_up_screen_line(60), m_down_screen_line(winHeight - 60) 
{
	
}


void Cpu::update() noexcept
{
	//TODO: implement cpu player update
	
	

}
