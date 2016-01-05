#include "utility.h"
#include "shape.h"

float _DefaultPaddleSize::x = 15, _DefaultPaddleSize::y = 80;

unsigned Shape::m_windowWidth = 0, Shape::m_windowHeight = 0;


Shape::Shape(sf::Shape *const shape) noexcept : 
	m_shape(shape), m_velocity(new sf::Vector2f()),
	m_horizontalCompensation(DefaultPaddleSize.x / 2.f), m_verticalCompensation(DefaultPaddleSize.y / 2.f)
{

}

Shape::Shape(std::pair<float,float> origin, sf::Shape * const shape) noexcept :
	m_shape(shape), m_velocity(new sf::Vector2f()),
	m_horizontalCompensation(origin.first), m_verticalCompensation(origin.second)
{
	m_shape->setOrigin(origin.first, origin.second);
	m_velocity->x = 0;
	m_velocity->y = 0;
}



const sf::Vector2f &Shape::getVelocity() const noexcept
{
	return *m_velocity;
}

void Shape::setCompensation(const float h, const float v) noexcept
{
	m_horizontalCompensation = h;
	m_verticalCompensation = v;
}


void Shape::setPosition(const float x, const float y) noexcept
{
	m_shape->setPosition(x, y);
};



void Shape::setPosition(Position pos) noexcept
{
	if(pos == Position::RightCorner)
		m_shape->setPosition((float)m_windowWidth - m_horizontalCompensation, m_windowHeight / 2.f);	

	else
		m_shape->setPosition(m_horizontalCompensation,(float)m_windowHeight / 2.f);
}



void Shape::informWindowSize(const unsigned winWidth, const unsigned winHeight) noexcept
{
	m_windowWidth = winWidth;
	m_windowHeight = winHeight;
}