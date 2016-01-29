
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "GameWindow.h"
#include "Entity.h"
#include "SpriteEffect.h"


using namespace sfe;


class Test1 : public entity::Entity<entity::RectangleShape>
{
public:
	Test1()
	{

	}

	virtual void onUpdate() override
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			m_velocity.y = -1;
		}

		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			m_velocity.y = +1;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			m_velocity.x = +1;
		}

		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			m_velocity.x = -1;
		}
		else
			m_velocity.y = m_velocity.x = 0;

		this->move(m_velocity);

	}

	virtual void onCollision() override {
		
	}

};


class Test2 : public entity::Entity<entity::Sprite>
{
public:
	Test2()
	{
		m_explosion.loadSpriteSheet("../Resources/explosion",
		{ 64,64 }, { 64 * 3, 64 * 3 });
		m_explosion.setOrigin(32.f, 32.f);
	}

	virtual void onUpdate() override
	{
		m_explosion.update();

	}

	virtual void onCollision() override 
	{
		if (!m_explosion.isActive()) {
			m_explosion.setPosition(m_intersectionVector.back()->getPosition());
			m_explosion.setActive();
		}

		std::cout << "Batero ni mim mo deus" << std::endl;
	}

private:
	effects::SpriteEffect m_explosion;
};


int main() 
{
	auto uniqueWin = GameWindow::makeUniqueWindow("tests");

	Test1 *test1 = new Test1;
	test1->setFillColor(sf::Color::Red);
	test1->setSize({10.f,10.f});
	test1->setOrigin({5.f, 5.f});
	test1->setOrigin(5.f, 5.f);

	sf::Texture texture;
	texture.loadFromFile("../Resources/balltexture");


	Test2 test2;
	test2.setTexture(texture);
	test2.setTextureRect({0,0,64,64});
	test2.setOrigin({32.f, 32.f});
	test2.setOrigin(32.f, 32.f);
	test2.setPosition(GameWindow::Width / 2.f, GameWindow::Height / 2.f);



	GameWindow::pushDrawable(*test1);
	GameWindow::pushDrawable(test2);
	while(uniqueWin->isOpen()) 
	{
		(*test1).update();
		test2.update();
		test1->updateIntersections(test2);
		uniqueWin->clear(sf::Color::Black);
		uniqueWin->updateWindowEvents();
		uniqueWin->drawAndDisplay();
	}

}
