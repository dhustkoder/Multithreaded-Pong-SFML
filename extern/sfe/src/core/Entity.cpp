#include "Exceptions.h"
#include "GameWindow.h"
#include "Entity.h"


SFE_NAMESPACE
ENTITY_NAMESPACE

static bool areInCollision(const Transformable& ent1, const Transformable& ent2);

Transformable::Transformable(sf::Transformable* transformable, 
	sf::Drawable* drawable)
	: m_tRef(*transformable),
	m_dRef(*drawable)
{

}

Transformable::~Transformable() {
	for (auto& ptr : m_intersectionVector)
		ptr->popIntersectionVector(*this);
	if (m_isOnScreen)
		GameWindow::popDrawable(m_dRef);
}

const sf::Vector2f Transformable::getPosition() const {
	return m_tRef.getPosition();
}

float Transformable::getRight() const {
	return m_tRef.getPosition().x + m_tRef.getOrigin().x;
}


float Transformable::getLeft() const {
	return m_tRef.getPosition().x - m_tRef.getOrigin().x;
}


float Transformable::getBottom() const {
	return m_tRef.getPosition().y + m_tRef.getOrigin().y;
}

float Transformable::getTop() const {
	return m_tRef.getPosition().y - m_tRef.getOrigin().y;
}




bool Transformable::updateIntersections(Transformable& second)
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




void Transformable::updateIntersectionVector()
{
	if (m_intersectionVector.size() == 0)
		return;

	for (auto itr = m_intersectionVector.begin(); 
	itr != m_intersectionVector.end(); ++itr)
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

void Transformable::popIntersectionVector(Transformable& second)
{
	auto itr = std::find(m_intersectionVector.begin(),
		m_intersectionVector.end(), (&second));

	if (itr != m_intersectionVector.end())
		m_intersectionVector.erase(itr);
}






bool Transformable::isIntersecting() const {
	return (m_intersectionVector.size() != 0);
}



bool Transformable::isIntersectingWith(const Transformable& second) const {
	auto itr = std::find(m_intersectionVector.begin(), m_intersectionVector.end(), (&second));
	return itr != m_intersectionVector.end();
}

bool Transformable::isOnScreenCheck()
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

void Transformable::update()
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





bool areInCollision(const Transformable & ent1, const Transformable & ent2)
{
	return (ent1.getBottom() >= ent2.getTop()
		&& ent1.getTop() <= ent2.getBottom()
		&& ent1.getLeft() <= ent2.getRight()
		&& ent1.getRight() >= ent2.getLeft());
}







NAMESPACE_END
NAMESPACE_END