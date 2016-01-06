#include "shape.h"
#include "gamewindow.h"
#include "utility.h"


Shape::Shape(sf::Vector2f &&origin, std::unique_ptr<sf::Shape>&& shape) noexcept :
	m_shape(std::move(shape)), m_velocity(new sf::Vector2f()),
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
		m_shape->setPosition((float)GameWindow::width - m_horizontalCompensation, GameWindow::height / 2.f);

    else if(pos == Position::LeftSide)
		m_shape->setPosition(m_horizontalCompensation,(float)GameWindow::height / 2.f);

    else
		m_shape->setPosition(GameWindow::width / 2.f, GameWindow::height / 2.f);
}
