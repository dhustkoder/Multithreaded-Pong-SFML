#ifndef SHAPE_H
#define SHAPE_H


#include <memory>
#include <SFML/Graphics/Shape.hpp>


static struct _DefaultPaddleSize
{
	static float x;
	static float y;
	
	auto operator / (const float div) {
		return std::make_pair(x / div, y / div);
	}

	operator sf::Vector2f(){
		return { x, y };
	}

}DefaultPaddleSize;



class Shape
{
public:
	enum class Position;

	// give the origin
	Shape(std::pair<float,float> origin, sf::Shape * const shape) noexcept;

	// use  default origin ( DefaulPaddleSize / 2.f )
	Shape(sf::Shape * const shape) noexcept;

	virtual ~Shape(){}
	float getRight() const noexcept;
	float getLeft() const noexcept;
	float getTop() const noexcept;
	float getBottom() const noexcept;
	const sf::Vector2f &getVelocity() const noexcept;
	void setCompensation(const float h, const float v) noexcept;
	void setPosition(const float x, const float y) noexcept;
	void setPosition(Position pos) noexcept;
	inline operator const sf::Drawable& () const noexcept;

	static void informWindowSize(const unsigned winWidth, const unsigned winHeight) noexcept;
	virtual void update() noexcept = 0;

protected:
	std::unique_ptr<sf::Shape> m_shape;
	std::unique_ptr<sf::Vector2f> m_velocity;
	float m_horizontalCompensation, m_verticalCompensation;
	static unsigned  m_windowWidth, m_windowHeight;
	
	// deleted functions
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


enum class Shape::Position
{
	LeftCorner,
	RightCorner
};


inline bool isColliding(const Shape &first, const Shape &second) noexcept
{
	return  first.getBottom() >= second.getTop() && first.getTop() <= second.getBottom()
		&& first.getLeft() <= second.getRight() && first.getRight() >= second.getLeft();

}


#endif // SHAPE_H
