#ifndef SHAPE_H
#define SHAPE_H

#include <memory>
#include <SFML/Graphics/Shape.hpp>

class Shape
{
public:
	Shape(const unsigned winWidth, const unsigned winHeight, 
	const float originX, const float originY, sf::Shape *shape) noexcept;
	
	virtual ~Shape(){}
	float getRight() const noexcept;
	float getLeft() const noexcept;
	float getTop() const noexcept;
	float getBottom() const noexcept;
	const sf::Vector2f &getVelocity() const noexcept;
	void setCompensation(const float h, const float v) noexcept;
	void setPosition(const float x, const float y) noexcept;
	inline operator const sf::Drawable& () const noexcept;
	
	virtual void update() noexcept = 0;

protected:
	std::unique_ptr<sf::Shape> m_shape;
	std::unique_ptr<sf::Vector2f> m_velocity;
	float m_horizontalCompensation, m_verticalCompensation;
	const unsigned  m_windowWidth, m_windowHeight;
	Shape(const Shape&) = delete;
	Shape(Shape&&) = delete;
	Shape& operator=(const Shape&) = delete;
	Shape& operator=(Shape&&) = delete;
	
};

inline float Shape::getRight() const noexcept
{
	return m_shape->getPosition().x + m_horizontalCompensation;
}

inline float Shape::getLeft() const noexcept
{
	return m_shape->getPosition().x - m_horizontalCompensation;
}


inline float Shape::getTop() const noexcept
{
	return m_shape->getPosition().y - m_verticalCompensation;
}

inline float Shape::getBottom() const noexcept
{
	return m_shape->getPosition().y + m_verticalCompensation;
}


inline Shape::operator const sf::Drawable&() const noexcept
{
	return *m_shape;
}


inline bool isColliding(const Shape &first, const Shape &second) noexcept
{
	return  first.getBottom() >= second.getTop() && first.getTop() <= second.getBottom()
		&& first.getLeft() <= second.getRight() && first.getRight() >= second.getLeft();

}


#endif // SHAPE_H
