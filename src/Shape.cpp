#include "pch.h"
#include "Shape.h"

static std::unique_ptr<sf::Shape> createShape(Shape::Type type, const sf::Vector2f& size);
static bool areInCollision(const Shape& shp1, const Shape& shp2);


Shape::Shape(const Type shapeType, const sf::Vector2f& size, const sf::Vector2f& origin) :
	m_velocity(new sf::Vector2f()),
	m_intersectingShape(nullptr),
	m_horizontalCompensation(origin.x), 
	m_verticalCompensation(origin.y)
{
	m_shape = createShape(shapeType, size);
	m_shape->setOrigin(origin.x, origin.y);
	m_velocity->x = 0;
	m_velocity->y = 0;
	GameWindow::pushShape(*this);
}

Shape::Shape(const Type shapeType, const float size, const sf::Vector2f& origin) :
	m_velocity(new sf::Vector2f()),
	m_intersectingShape(nullptr),
	m_horizontalCompensation(origin.x),
	m_verticalCompensation(origin.y)
{
	m_shape = createShape(shapeType, { size, size });
	m_shape->setOrigin(origin.x, origin.y);
	m_velocity->x = 0;
	m_velocity->y = 0;
	GameWindow::pushShape(*this);
}


Shape::~Shape() {
	GameWindow::popShape(*this);
}



void Shape::setPosition(const Position pos)
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


bool Shape::checkForCollision(Shape &second)
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

	return false;
}


bool Shape::updateIntersectingShape()
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






std::unique_ptr<sf::Shape> createShape(Shape::Type type, const sf::Vector2f& size) 
{
	
	try
	{
		switch (type)
		{
			case Shape::Type::Rectangle:
				return std::make_unique<sf::RectangleShape>(size);
			case Shape::Type::Circle:
				return std::make_unique<sf::CircleShape>((size.x + size.y) / 2.f);
			default:
				break;
		}
	}
	catch (std::bad_alloc& err) {
		printException(err, "createShape", true);
	}
	

	return nullptr;

}



bool areInCollision(const Shape& shp1, const Shape& shp2) 
{
	return (shp1.getBottom() >= shp2.getTop()
		&& shp1.getTop() <= shp2.getBottom()
		&& shp1.getLeft() <= shp2.getRight()
		&& shp1.getRight() >= shp2.getLeft());

}
