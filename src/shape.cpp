#include "shape.h"
#include "gamewindow.h"
#include "utility.h"


Shape::Shape(sf::Vector2f &&origin, std::unique_ptr<sf::Shape>&& shape) noexcept :
	m_shape(std::move(shape)), 
	m_velocity(new sf::Vector2f()),
	m_intersectingShape(nullptr),
	m_horizontalCompensation(origin.x), 
	m_verticalCompensation(origin.y)
{
	m_shape->setOrigin(origin.x, origin.y);
	m_velocity->x = 0;
	m_velocity->y = 0;
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
		m_shape->setPosition((float)GameWindow::Width - m_horizontalCompensation, GameWindow::Height / 2.f);

    else if(pos == Position::LeftSide)
		m_shape->setPosition(m_horizontalCompensation,(float)GameWindow::Height / 2.f);

    else
		m_shape->setPosition(GameWindow::Width / 2.f, GameWindow::Height / 2.f);
}


bool Shape::checkForCollision(Shape &second) noexcept
{
	if (m_intersectingShape != nullptr)
		updateIntersectingShape();

	if (m_intersectingShape == nullptr)
		if (this->getBottom() >= second.getTop()
			&& this->getTop() <= second.getBottom()
			&& this->getLeft() <= second.getRight()
			&& this->getRight() >= second.getLeft())
		{
			this->m_intersectingShape = &second;
			second.m_intersectingShape = this;
			return true;
		}

	return false;

}


void Shape::updateIntersectingShape() noexcept
{
	if (! (this->getBottom() >= m_intersectingShape->getTop())
		|| ! (this->getTop() <= m_intersectingShape->getBottom())
		|| ! (this->getLeft() <= m_intersectingShape->getRight())
		|| ! (this->getRight() >= m_intersectingShape->getLeft()))
	{
		// is no more colliding	
		m_intersectingShape->m_intersectingShape = nullptr;
		m_intersectingShape = nullptr; 
	}
	
}