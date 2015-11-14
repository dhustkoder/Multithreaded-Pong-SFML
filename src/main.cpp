
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Paddle.h"
#include "player.h"


int main()
{

	sf::RenderWindow win({ 800,600 }, "sfml");
	win.clear(sf::Color::Black);
	Player player(800,600);
	while (win.isOpen())
	{
		win.draw(player);
		win.display();
	}
}