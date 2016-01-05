#include "shape.h"
#include "utility.h"

unsigned Shape::m_windowWidth = 0, Shape::m_windowHeight = 0;


Shape::Shape(sf::Vector2f &&origin, sf::Shape * const shape) noexcept :
	m_shape(shape), m_velocity(new sf::Vector2f()),
	m_horizontalCompensation(origin.x), m_verticalCompensation(origin.y)
{
	m_shape->setOrigin(origin.x, origin.y);
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
    if(pos == Position::RightSide)
		m_shape->setPosition((float)m_windowWidth - m_horizontalCompensation, m_windowHeight / 2.f);	

    else if(pos == Position::LeftSide)
		m_shape->setPosition(m_horizontalCompensation,(float)m_windowHeight / 2.f);

    else
        m_shape->setPosition(m_windowWidth / 2.f, m_windowHeight / 2.f);
}
