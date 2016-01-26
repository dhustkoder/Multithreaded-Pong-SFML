#include "pch.h"
#include "Shape.h"

bool areInCollision(const Shape& shp1, const Shape& shp2);

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
	{
		if (areInCollision(*this, second))
		{
			this->m_intersectingShape = &second;
			second.m_intersectingShape = this;
			return true;
		}
	}

	else
		return false;

}


bool Shape::updateIntersectingShape() noexcept
{
	// is not intersecting
	if (m_intersectingShape == nullptr)
		return false;
	

	else if (!areInCollision(*this, *m_intersectingShape))
	{
		// was intersecting but is no more
		m_intersectingShape->m_intersectingShape = nullptr;
		m_intersectingShape = nullptr;
		return false;
	}

	else
		return true; // continues intersecting
}






bool areInCollision(const Shape& shp1, const Shape& shp2) {
	return (shp1.getBottom() >= shp2.getTop()
		&& shp1.getTop() <= shp2.getBottom()
		&& shp1.getLeft() <= shp2.getRight()
		&& shp1.getRight() >= shp2.getLeft());

}