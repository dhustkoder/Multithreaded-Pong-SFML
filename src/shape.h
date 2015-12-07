#ifndef SHAPE_H
#define SHAPE_H

#include <memory>
#include <SFML/Graphics/Shape.hpp>

class Shape
{
public:
	Shape(const float originX, const float originY, sf::Shape *shapeType);
	float getRight() const;
	float getLeft() const;
	float getTop() const;
	float getBottom() const;
	const sf::Vector2f &getVelocity() const;
	void setCompensation(const float h, const float v);
	void setPosition(const float x, const float y);
	static bool isColliding(const Shape &first, const Shape &second);
	virtual void update() = 0;
	inline operator sf::Drawable& ();
protected:
	std::unique_ptr<sf::Shape> m_shape;
	std::unique_ptr<sf::Vector2f> m_velocity;
	float m_horizontalCompensation, m_verticalCompensation;

	Shape(const Shape&) = delete;
	Shape(Shape&&) = delete;
	
};

inline float Shape::getRight() const
{
	return m_shape->getPosition().x + m_horizontalCompensation;
}

inline float Shape::getLeft() const
{
	return m_shape->getPosition().x - m_horizontalCompensation;
}


inline float Shape::getTop() const
{
	return m_shape->getPosition().y - m_verticalCompensation;
}

inline float Shape::getBottom() const
{
	return m_shape->getPosition().y + m_verticalCompensation;
}


inline Shape::operator sf::Drawable&()
{
	return *m_shape;
}




#endif
