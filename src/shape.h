#ifndef PADDLE_H
#define PADDLE_H

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
	void setCompensation(const float h, const float v);
	void setPosition(const float x, const float y);
	virtual void update() = 0;
	inline operator sf::Drawable& ();
protected:
	sf::Shape *const getShape();
	sf::Vector2f *const getVelocity();
private:
	std::unique_ptr<sf::Shape> m_shape;
	std::unique_ptr<sf::Vector2f> m_velocity;
	float m_horizontalCompensation, m_verticalCompensation;

	Shape(const Shape&) = delete;
	Shape(Shape&&) = delete;
	
};



inline Shape::operator sf::Drawable&()
{
	return *m_shape;
}




#endif