#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Exceptions.h"
#include "Utility.h"
#include "sfe.h"

SFE_NAMESPACE
namespace entity {

using Shape = sf::Shape;
using Sprite = sf::Sprite;
using RectangleShape = sf::RectangleShape;


template<typename _T, typename T2>
static bool areInCollision(const _T& ent1, const T2& ent2)
{
	return (ent1.getBottom() >= ent2.getTop()
		&& ent1.getTop() <= ent2.getBottom()
		&& ent1.getLeft() <= ent2.getRight()
		&& ent1.getRight() >= ent2.getLeft());

}


template<class T>
class Entity : public std::enable_if_t<utility::is_one_of<T, Sprite, RectangleShape>::value, T>  
{
	
public:
	enum class Position
	{
		LeftSide,
		RightSide,
		Middle
	};

public:
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;
	
	Entity() { this->initialize(); };
	virtual ~Entity() { this->dispose(); };


	void setCompensation(const float h, const float v);
	void setVelocity(const float x, const float y);
	void setVelocity(const sf::Vector2f& vel);

	float getRight() const;
	float getLeft() const;
	float getTop() const;
	float getBottom() const;
	const sf::Vector2f& getVelocity() const;
	bool isIntersecting() const;


	bool isIntersectingWith(const sf::Transformable& second) const {
		auto itr = std::find(m_intersectionVector.begin(), m_intersectionVector.end(), (&second));
		return itr != m_intersectionVector.end();
	}


	template<typename T2>
	bool updateIntersections(T2& second)
	{
		this->updateIntersectionVector<T2>();
		if(areInCollision(*this, second)) 
		{
			
			auto itr = std::find(m_intersectionVector.begin(), m_intersectionVector.end(), 
				static_cast<sf::Transformable*>(&second));
			
			if(itr == m_intersectionVector.end()) {
				m_intersectionVector.push_back(static_cast<sf::Transformable*>(&second));
				second.treatCollision();
				this->treatCollision();
				return true;
			}
		}

		return false;
	}
	
	template<typename T2>
	void updateIntersectionVector()
	{
		if(m_intersectionVector.size() == 0)
			return;

		for ( auto itr = m_intersectionVector.begin(); itr != m_intersectionVector.end();
			++itr )
		{
			
			if(!areInCollision(*this, static_cast<T2&>(*(*itr))))
			{
				static_cast<T2*>(*itr)->popIntersectionVector(*this);
				itr = m_intersectionVector.erase(itr);
				if(itr == m_intersectionVector.end())
					break;
			}
		}
	}


	void popIntersectionVector(sf::Transformable& second) 
	{
		auto itr = std::find(m_intersectionVector.begin(), 
			m_intersectionVector.end(), (&second));

		if(itr != m_intersectionVector.end())
			m_intersectionVector.erase(itr);
	}



	virtual void treatCollision() = 0;
	
	

	virtual void update() = 0;
protected:
	std::unique_ptr<sf::Vector2f> m_velocity;
	std::vector<sf::Transformable*> m_intersectionVector;
	float m_horizontalCompensation, m_verticalCompensation;


private:
	void initialize() 
	{
		try
		{
			m_velocity = std::make_unique<sf::Vector2f>();
		}
		catch(std::bad_alloc& err) {
			printException(err, "Entity<T>::Entity", true);
		}
	}
	void dispose() noexcept {
	for(auto& transfPtr : m_intersectionVector)
		static_cast<Entity<T>*>(transfPtr)->popIntersectionVector(*this);	
	}



};

template<typename T>
inline void Entity<T>::setCompensation(const float h, const float v) {
	m_horizontalCompensation = h;
	m_verticalCompensation = v;
}

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
inline float Entity<T>::getRight() const {
	return this->getPosition().x + m_horizontalCompensation;
}

template<typename T>
inline float Entity<T>::getLeft() const {
	return this->getPosition().x - m_horizontalCompensation;
}

template<typename T>
inline float Entity<T>::getTop() const {
	return this->getPosition().y - m_verticalCompensation;
}


template<typename T>
inline float Entity<T>::getBottom() const {
	return this->getPosition().y + m_verticalCompensation;	
}


template<typename T>
inline const sf::Vector2f& Entity<T>::getVelocity() const {
	return m_velocity;
}


template<typename T>
inline bool Entity<T>::isIntersecting() const {
	return ( m_intersectionVector.size() != 0 );
}















}
NAMESPACE_END
#endif // SHAPE_H
