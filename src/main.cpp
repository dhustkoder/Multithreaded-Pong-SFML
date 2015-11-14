#include "Paddle.h"
#include "player.h"
#include <SFML/Graphics.hpp>

int main()
{

	sf::RenderWindow win({ 800,600 }, "sfml");
	Player player(800,600);
	sf::Event winEvent;
	while (win.isOpen())
	{
		if (win.pollEvent(winEvent))
			if (winEvent.type == winEvent.Closed)
				win.close();
		

		win.clear(sf::Color::Black);
		player.update();
		win.draw(player);
		win.display();
	}
}