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
	void setCompensation(const float h, const float v) noexcept;
	void setPosition(const float x, const float y) noexcept;
	void setPosition(Position pos) noexcept;

	sf::Shape& getShape() { return *m_shape; }
	float getRight() const noexcept;
	float getLeft() const noexcept;
	float getTop() const noexcept;
	float getBottom() const noexcept;
	const sf::Vector2f &getVelocity() const noexcept;
	bool isIntersectedWith(Shape& second) noexcept;
	bool isIntersecting() const noexcept;
	bool collided(Shape& second) noexcept;


	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	virtual void update() noexcept = 0;

protected:
	void updateIntersectingShape() noexcept;
	bool collidedNoCheck(Shape& second) const noexcept;

protected:
	std::unique_ptr<sf::Shape> m_shape;
	std::unique_ptr<sf::Vector2f> m_velocity;
	Shape* m_intersectingShape;
	float m_horizontalCompensation, m_verticalCompensation;

};

enum class Shape::Position
{
	LeftSide,
	RightSide,
	Middle
};

inline float Shape::getRight() const noexcept {
	return m_shape->getPosition().x + m_horizontalCompensation;
}

inline float Shape::getLeft() const noexcept {
	return m_shape->getPosition().x - m_horizontalCompensation;
}


inline float Shape::getTop() const noexcept {
	return m_shape->getPosition().y - m_verticalCompensation;
}

inline float Shape::getBottom() const noexcept {
	return m_shape->getPosition().y + m_verticalCompensation;
}


inline const sf::Vector2f &Shape::getVelocity() const noexcept {
	return *m_velocity;
}



// returns true if (this) has collided with 
inline bool Shape::isIntersecting() const noexcept {
	return m_intersectingShape != nullptr;
}

// returns absolutely answer: if (this) m_intersectingShape is nullptr, then 
// this function execute and returns the result of 'collided' function,
// if m_intersectingShape is not null, then check if 'second' is the Shape pointed 
// by m_intersetingShape. If you do not wan't the result of function 'collided',
// check with 'Shape::isIntersecting' to be sure the Shape is intersecting with 
// some other Shape before calling 'Shape::isIntersectingWith'.
inline bool Shape::isIntersectedWith(Shape& second) noexcept {
	return (m_intersectingShape == nullptr) ? this->collidedNoCheck(second) : m_intersectingShape == &second;
}

inline void Shape::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(*m_shape, states);
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
