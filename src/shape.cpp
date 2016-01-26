#include "pch.h"
#include "Shape.h"


Shape::Shape(const sf::Vector2f& origin, std::unique_ptr<sf::Shape>&& shape) :
	m_shape(std::move(shape)), 
	m_velocity(new sf::Vector2f()),
	m_intersectingShape(nullptr),
	m_horizontalCompensation(origin.x), 
	m_verticalCompensation(origin.y)
{
	if (m_shape == nullptr)
		throw std::invalid_argument("parameter 'std::unique_ptr<sf::Shape>&& shape' is a nullptr.");

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



void Shape::setPosition(const Position pos) noexcept
{
	switch (pos)
	{
		case Position::LeftSide:
			m_shape->setPosition(m_horizontalCompensation, (float)GameWindow::Height / 2.f);
			break;

		case Position::RightSide:
			m_shape->setPosition((float)GameWindow::Width - m_horizontalCompensation, GameWindow::Height / 2.f);
			break;

		case Position::Middle:
			m_shape->setPosition(GameWindow::Width * 0.50f, GameWindow::Height * 0.50f);
			break;
	}
}


bool Shape::checkForCollision(Shape &second) noexcept
{
	
	if (!updateIntersectingShape())
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


bool Shape::updateIntersectingShape() noexcept
{
	if (m_intersectingShape == nullptr)
		return true;


	else if (!(this->getBottom() >= m_intersectingShape->getTop())
		|| !(this->getTop() <= m_intersectingShape->getBottom())
		|| !(this->getLeft() <= m_intersectingShape->getRight())
		|| !(this->getRight() >= m_intersectingShape->getLeft()))
	{
		// is no more colliding	
		m_intersectingShape->m_intersectingShape = nullptr;
		m_intersectingShape = nullptr;
		return false;
	}

	else
		return true;
}
