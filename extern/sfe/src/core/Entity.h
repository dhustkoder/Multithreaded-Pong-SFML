#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include "Exceptions.h"
#include "GameWindow.h"
#include "Utility.h"
#include "sfe.h"

SFE_NAMESPACE
namespace entity {

using Shape = sf::Shape;
using Sprite = sf::Sprite;
using RectangleShape = sf::RectangleShape;
using CircleShape = sf::CircleShape;
using ConvexShape = sf::ConvexShape;

class Transformable;

static bool areInCollision(const Transformable& ent1, const Transformable& ent2);

class Transformable
{
public:
	Transformable(sf::Transformable& transformable,
		sf::Drawable& drawable)
		: m_tRef(transformable),
		m_dRef(drawable)
	{

	}

	~Transformable() {
		for (auto& ptr : m_intersectionVector)
			ptr->popIntersectionVector(*this);
		if(m_isOnScreen)
			GameWindow::popDrawable(m_dRef);
	}

	const sf::Vector2f getPosition() const {
		return m_tRef.getPosition();
	}

	float getRight() const {
		return m_tRef.getPosition().x + m_tRef.getOrigin().x;
	}


	float getLeft() const {
		return m_tRef.getPosition().x - m_tRef.getOrigin().x;
	}


	float getTop() const {
		return m_tRef.getPosition().y - m_tRef.getOrigin().y;
	}

	float getBottom() const {
		return m_tRef.getPosition().y + m_tRef.getOrigin().y;
	}


	bool updateIntersections(Transformable& second)
	{
		this->updateIntersectionVector();
		if (areInCollision(*this, second))
		{

			auto itr = std::find(m_intersectionVector.begin(), 
				m_intersectionVector.end(), (&second));

			if (itr == m_intersectionVector.end())
			{
				m_intersectionVector.push_back(&second);
				second.m_intersectionVector.push_back(this);
				this->onCollision();
				second.onCollision();
				return true;
			}
		}

		return false;
	}

	void updateIntersectionVector()
	{
		if (m_intersectionVector.size() == 0)
			return;

		for (auto itr = m_intersectionVector.begin(); itr != m_intersectionVector.end();
		++itr)
		{
			if (!areInCollision(*this, *(*itr)))
			{
				(*itr)->popIntersectionVector(*this);
				itr = m_intersectionVector.erase(itr);
				if (itr == m_intersectionVector.end())
					break;
			}
		}
	}

	void popIntersectionVector(Transformable& second)
	{
		auto itr = std::find(m_intersectionVector.begin(),
			m_intersectionVector.end(), (&second));

		if (itr != m_intersectionVector.end())
			m_intersectionVector.erase(itr);
	}

	bool isIntersectingWith(const Transformable& second) const {
		auto itr = std::find(m_intersectionVector.begin(), m_intersectionVector.end(), (&second));
		return itr != m_intersectionVector.end();
	}

	bool isOnScreenCheck() 
	{
		if (this->getRight() > 0
			|| this->getLeft() < GameWindow::Width
			|| this->getBottom() > 0
			|| this->getTop() < GameWindow::Height) {
			m_isOnScreen = true;
			return true;
		}
		
		m_isOnScreen = false;
		return false;
	}
	
	void update() 
	{ 
		onUpdate();
		if (m_controlGameWindow) 
		{
			if (m_isOnScreen) {
				if (!isOnScreenCheck())
					GameWindow::popDrawable(m_dRef);
			}
			else if (!m_isOnScreen) {
				if (isOnScreenCheck())
					GameWindow::pushDrawable(m_dRef);
			}
		}
	}

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
















bool areInCollision(const Transformable & ent1, const Transformable & ent2)
{
	return (ent1.getBottom() >= ent2.getTop()
		&& ent1.getTop() <= ent2.getBottom()
		&& ent1.getLeft() <= ent2.getRight()
		&& ent1.getRight() >= ent2.getLeft());

}





}
NAMESPACE_END
#endif // SHAPE_H
