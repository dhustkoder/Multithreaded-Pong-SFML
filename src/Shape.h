#ifndef SHAPE_H
#define SHAPE_H
#include <memory>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>

class Shape : public sf::Drawable
{
public:
	enum class Position
	{
		LeftSide,
		RightSide,
		Middle
	};

	enum class Type
	{
		Rectangle,
		Circle
	};


public:
	Shape(const Shape&) = delete;
	Shape& operator=(const Shape&) = delete;

	////////////////////////////////////////////////////////////
	/// \brief constructor
	/// you need to create a shape in the constructor
	/// and give a origin
	////////////////////////////////////////////////////////////
	Shape(const Type shapeType, const sf::Vector2f& size, const sf::Vector2f& origin);
	Shape(const Type shapeType, const float size, const sf::Vector2f& origin);
	virtual ~Shape();

	void setCompensation(const float h, const float v) noexcept;
	void setPosition(const float x, const float y) noexcept;
	void setPosition(const Position pos) noexcept;

	float getRight() const noexcept;
	float getLeft() const noexcept;
	float getTop() const noexcept;
	float getBottom() const noexcept;
	const sf::Vector2f& getPosition() const noexcept;
	const sf::Vector2f& getVelocity() const noexcept;
	


	////////////////////////////////////////////////////////////
	/// \brief isIntersecting
	/// returns true if (this) is still intersecting with some other Shape,
	/// keep in mind that to get the right answer the checkForCollision,
	/// must be called to update the status of the Shape.
	////////////////////////////////////////////////////////////
	bool isIntersecting() const noexcept;




	////////////////////////////////////////////////////////////
	/// \brief isIntersectingWith
	/// returns absolutely answer: if (this) is intersecting with the 
	/// 'second' Shape then returns true, else returns false.
	/// before calling this function, you need to update the Shape
	/// status calling 'checkForCollision'
	////////////////////////////////////////////////////////////
	bool isIntersectingWith(const Shape& second) const noexcept;



	////////////////////////////////////////////////////////////
	/// \brief checkForCollision
	/// will check for a new collision.
	/// if a new collision is found between the given Shapes
	/// ( between (this) and parameter (second) )
	/// the intersectingShape is set for both Shapes
	/// and then returns true. If this function is called again
	/// while those same Shapes are still in the same collision, then it will
	/// returns false. This function only returns true again,
	/// if the Shapes ended the first collision and collide again.
	/// To check if given Shapes are still in collision, just call
	/// 'Shape::isIntersectingWith(second)'.
	////////////////////////////////////////////////////////////
	bool checkForCollision(Shape& second) noexcept;


	////////////////////////////////////////////////////////////
	/// \brief treatCollision
	/// pure virtual function
	/// override this function to give the proper behaviour to 
	/// the shape when treating a collision
	/// you can have access to the collided object 
	///through the pointer m_intersectingShape
	////////////////////////////////////////////////////////////
	virtual void treatCollision() = 0;
	
	
	
	///////////////////////////////////////////////////////////
	/// \brief update
	/// pure virtual function
	/// override this function to write the 
	/// updates you want for your Shape object
	//////////////////////////////////////////////////////////
	virtual void update() = 0;

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
	////////////////////////////////////////////////////////////
	/// \brief updateIntersectingShape
	/// this function tests (this) and m_intersectingShape
	/// positions, to make sure they are still intersecting
	////////////////////////////////////////////////////////////
	bool updateIntersectingShape() noexcept;

protected:
	std::unique_ptr<sf::Shape> m_shape;
	std::unique_ptr<sf::Vector2f> m_velocity;
	Shape* m_intersectingShape;
	float m_horizontalCompensation, m_verticalCompensation;

};

inline void Shape::setCompensation(const float h, const float v) noexcept
{
	m_horizontalCompensation = h;
	m_verticalCompensation = v;
}



inline void Shape::setPosition(const float x, const float y) noexcept
{
	m_shape->setPosition(x, y);
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


inline const sf::Vector2f& Shape::getVelocity() const noexcept {
	return *m_velocity;
}

inline const sf::Vector2f& Shape::getPosition() const noexcept {
	return m_shape->getPosition();
}



inline bool Shape::isIntersecting() const noexcept {
	return m_intersectingShape != nullptr;
}


inline bool Shape::isIntersectingWith(const Shape& second) const noexcept {
	return m_intersectingShape == &second;
}

inline void Shape::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(*m_shape, states);
}


template<typename ...Ts>
constexpr static void updateObjects(Ts&& ...args)
{
	return (void) std::initializer_list<int>
	{
		(std::forward<Ts>(args).update(), 0)...
	};
}




#endif // SHAPE_H
