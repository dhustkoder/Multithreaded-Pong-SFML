#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include "Exceptions.h"
#include "Utility.h"
#include "sfe.h"

SFE_NAMESPACE
namespace entity {

using Shape = sf::Shape;
using Sprite = sf::Sprite;
using RectangleShape = sf::RectangleShape;
using CircleShape = sf::CircleShape;
using ConvexShape = sf::ConvexShape;




class Transformable
{
public:
	Transformable(sf::Transformable& transformable,  sf::Drawable& drawable);
	~Transformable();
	

	const sf::Vector2f getPosition() const;

	float getRight() const;

	float getLeft() const;

	float getBottom() const;

	float getTop() const;


	bool updateIntersections(Transformable& second);

	void updateIntersectionVector();

	void popIntersectionVector(Transformable& second);

	bool isIntersectingWith(const Transformable& second) const;

	bool isOnScreenCheck();
	
	void update();

	void pushInGameWindow();
	void popOutGameWindow();

protected:
	std::vector<Transformable*> m_intersectionVector;
	virtual void onCollision() = 0;
	virtual void onUpdate() = 0;
private:
	sf::Transformable& m_tRef;
	sf::Drawable& m_dRef;
	bool m_isOnScreen = false;
	bool m_controlGameWindow = false;

};



template<class T>
class Entity : public std::enable_if_t<utility::is_one_of<T, Sprite, Shape,
	RectangleShape, CircleShape, ConvexShape>::value, T>,
	public Transformable
{
public:
	using Transformable::update;
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

	Entity() : Transformable((sf::Transformable&)*this,
		(sf::Drawable&)*this) { };
	virtual ~Entity() = default;
	void setVelocity(const float x, const float y);
	void setVelocity(const sf::Vector2f& vel);

	
	const sf::Vector2f& getVelocity() const;
	bool isIntersecting() const;
	
protected:
	sf::Vector2f m_velocity;


};



// public:
template<typename T>
inline void Entity<T>::setVelocity(const float x, const float y) {
	m_velocity->x = x;
	m_velocity->y = y;
}

template<typename T>
inline void Entity<T>::setVelocity(const sf::Vector2f& vel) {
	*m_velocity = vel;
}


template<typename T>
const sf::Vector2f& Entity<T>::getVelocity() const {
	return m_velocity;
}


template<typename T>
bool Entity<T>::isIntersecting() const {
	return (m_intersectionVector.size() != 0);
}






















}
NAMESPACE_END
#endif // SHAPE_H
