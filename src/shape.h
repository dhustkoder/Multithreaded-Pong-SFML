#ifndef SHAPE_H
#define SHAPE_H
#include <memory>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>

class Shape : public sf::Drawable
{
public:
	enum class Position;

public:
	// give the origin
	Shape(sf::Vector2f &&origin, std::unique_ptr<sf::Shape>&& shape) noexcept;
	Shape(const Shape&) = delete;
	Shape& operator=(const Shape&) = delete;

	virtual ~Shape(){}
	float getRight() const noexcept;
	float getLeft() const noexcept;
	float getTop() const noexcept;
	float getBottom() const noexcept;
	const sf::Vector2f &getVelocity() const noexcept;
	void setCompensation(const float h, const float v) noexcept;
	void setPosition(const float x, const float y) noexcept;
	void setPosition(Position pos) noexcept;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	virtual void update() noexcept = 0;

protected:
	std::unique_ptr<sf::Shape> m_shape;
	std::unique_ptr<sf::Vector2f> m_velocity;
	float m_horizontalCompensation, m_verticalCompensation;	
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


inline const sf::Vector2f &Shape::getVelocity() const noexcept
{
	return *m_velocity;
}


inline void Shape::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(*m_shape, states);
}

enum class Shape::Position
{
    LeftSide,
    RightSide,
    Middle
};




inline bool isColliding(const Shape &first, const Shape &second) noexcept
{
	return  first.getBottom() >= second.getTop() && first.getTop() <= second.getBottom()
		&& first.getLeft() <= second.getRight() && first.getRight() >= second.getLeft();

}

template<typename ...Ts>
static void updateObjects(Ts&& ...args) noexcept 
{
	return (void)std::initializer_list<int>
	{
		(std::forward<Ts>(args).update(), 0)...
	};
}




#endif // SHAPE_H
