#ifndef ENTITY_H
#define ENTITY_H
#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "Utility.h"
#include "sfe.h"
SFE_NAMESPACE
ENTITY_NAMESPACE

using Shape = sf::Shape;
using Sprite = sf::Sprite;
using RectangleShape = sf::RectangleShape;
using CircleShape = sf::CircleShape;
using ConvexShape = sf::ConvexShape;




class Transformable
{
public:
	Transformable(sf::Transformable* transformable,  sf::Drawable* drawable);
	virtual ~Transformable();
	

	const sf::Vector2f& getPosition() const;

	float getRight() const;

	float getLeft() const;

	float getBottom() const;

	float getTop() const;


	bool updateIntersections(Transformable& second);

	void updateIntersectionVector();

	void popIntersectionVector(Transformable& second);

	bool isIntersecting() const;

	bool isIntersectingWith(const Transformable& second) const;

	bool isOnScreenCheck();
	
	void update();

	void pushInGameWindow();
	void popOutGameWindow();

protected:
	virtual void onCollision() = 0;
	virtual void onUpdate() = 0;

protected:
	sf::Vector2f m_velocity;
	std::vector<Transformable*> m_intersectionVector;

private:
	sf::Transformable& m_tRef;
	sf::Drawable& m_dRef;
	bool m_isOnScreen = false;
	bool m_controlGameWindow = false;

};



template<class T>
class Entity : public Transformable, 
	public std::enable_if_t<utility::is_one_of<T, Sprite, Shape,
	RectangleShape, CircleShape, ConvexShape>::value, T>
{
public:
	using Transformable::update;



	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;
	Entity() : Transformable(this,this) { };
	virtual ~Entity() = default;

	
};



NAMESPACE_END
NAMESPACE_END
#endif // SHAPE_H
